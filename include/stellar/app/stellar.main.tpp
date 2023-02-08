// ==========================================================================
//                    STELLAR - SwifT Exact LocaL AligneR
//                   http://www.seqan.de/projects/stellar/
// ==========================================================================
// Copyright (C) 2010-2012 by Birte Kehr
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your options) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ==========================================================================
// Author: Birte Kehr <birte.kehr@fu-berlin.de>
// ==========================================================================

#pragma once

#include <variant>

#include <stellar/app/stellar.main.hpp>

#include <seqan/seq_io.h>

#include <seqan3/core/debug_stream.hpp>

#include <stellar/stellar.hpp>
#include <stellar/stellar_index.hpp>
#include <stellar/stellar_output.hpp>
#include <stellar/stellar_database_segment.hpp>
#include <stellar/database_id_map.hpp>
#include <stellar/query_id_map.hpp>
#include <stellar/utils/stellar_app_runtime.hpp>

#include <stellar/app/stellar.diagnostics.hpp>

#include <stellar/app/stellar.diagnostics.tpp>

namespace stellar
{
using namespace seqan;
} // namespace stellar

//////////////////////////////////////////////////////////////////////////////
namespace seqan {

template <>
struct FunctorComplement<AminoAcid>:
    public::std::function<AminoAcid(AminoAcid)>
{
    inline AminoAcid operator()(AminoAcid x) const
    {
        return x;
    }

};

} // namespace seqan

namespace stellar
{

namespace app
{

template <typename TAlphabet, typename TId>
bool _shouldWriteOutputFile(bool const databaseStrand, StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > const & matches)
{
    // if databaseStrand == true always outputs
    // if databaseStrand == false only outputs if TAlphabet == Dna5 or TAlphabet == Rna5
    return databaseStrand || IsSameType<TAlphabet, Dna5>::VALUE || IsSameType<TAlphabet, Rna5>::VALUE;
}

template <typename TAlphabet, typename TId>
void _postproccessQueryMatches(bool const databaseStrand, uint64_t const & refLen,
                               StellarOptions const & options,
                               StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > & matches,
                               std::vector<size_t> & disabledQueryIDs)
{
    using TSequence = String<TAlphabet>;

    for (size_t queryID = 0; queryID < length(matches); ++queryID)
    {
        QueryMatches<StellarMatch<TSequence const, TId>> & queryMatches = value(matches, queryID);

        queryMatches.removeOverlapsAndCompactMatches(options.disableThresh,
                                                     /*compactThresh*/ 0,
                                                     options.minLength,
                                                     options.numMatches);

        if (queryMatches.disabled)
            disabledQueryIDs.push_back(queryID);
    }

    // adjust length for each matches of a single query (only for dna5 and rna5)
    // TODO: WHY? This seems like an arbitrary restriction
    if (_shouldWriteOutputFile(databaseStrand, matches))
        _postproccessLengthAdjustment(refLen, matches);
}

template <typename TAlphabet, typename TId = CharString>
struct StellarApp
{
    template <typename visitor_fn_t>
    static constexpr StellarComputeStatistics _verificationMethodVisit(
        StellarVerificationMethod verificationMethod,
        visitor_fn_t && visitor_fn
    )
    {
        if (verificationMethod == StellarVerificationMethod{AllLocal{}})
            return visitor_fn(AllLocal());
        else if (verificationMethod == StellarVerificationMethod{BestLocal{}})
            return visitor_fn(BestLocal());
        else if (verificationMethod == StellarVerificationMethod{BandedGlobal{}})
            return visitor_fn(BandedGlobal());
        else if (verificationMethod == StellarVerificationMethod{BandedGlobalExtend{}})
            return visitor_fn(BandedGlobalExtend());
        return StellarComputeStatistics{};
    }

    static StellarComputeStatistics
    search_and_verify(
        StellarDatabaseSegment<TAlphabet> const databaseSegment,
        TId const & databaseID,
        QueryIDMap<TAlphabet> const & queryIDMap,
        bool const databaseStrand,
        StellarOptions & localOptions, // localOptions.compactThresh is out-param
        StellarSwiftPattern<TAlphabet> & localSwiftPattern,
        stellar::stellar_kernel_runtime & strand_runtime,
        StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > & localMatches
    )
    {
        using TSequence = String<TAlphabet>;

        auto getQueryMatches = [&](auto const & pattern) -> QueryMatches<StellarMatch<TSequence const, TId> > &
        {
            // Note: Index is normally build over all queries [query0, query1, query2, ...],
            // but in LocalQueryPrefilter case it can just be build over [query0].
            // We need to translate that position to a "record" ID
            //!TODO: this shouldn't be necessary
            // each Stellar instance should be given a set of bin query, all of which should be indexed
            size_t const queryRecordID = queryIDMap.recordID(pattern);
            return value(localMatches, queryRecordID);
        };

        auto isPatternDisabled = [&](StellarSwiftPattern<TAlphabet> & pattern) -> bool {
            QueryMatches<StellarMatch<TSequence const, TId> > & queryMatches = getQueryMatches(pattern);
            return queryMatches.disabled;
        };

        auto onAlignmentResult = [&](auto & alignment) -> bool {
            QueryMatches<StellarMatch<TSequence const, TId> > & queryMatches = getQueryMatches(localSwiftPattern);

            StellarMatch<TSequence const, TId> match(alignment, databaseID, databaseStrand);
            length(match);  // DEBUG: Contains assertion on clipping.

            // success
            return _insertMatch(
                queryMatches,
                match,
                localOptions.minLength,
                localOptions.disableThresh,
                // compactThresh is basically an output-parameter; will be updated in kernel and propagated back
                // outside of this function, the reason why StellarOptions can't be passed as const to this function.
                // TODO: We might want to make this tied to the QueryMatches itself, as it should know then to consolidate
                // the matches
                localOptions.compactThresh,
                localOptions.numMatches
            );
        };

        // finder
        StellarSwiftFinder<TAlphabet> swiftFinder(databaseSegment.asInfixSegment(), localOptions.minRepeatLength, localOptions.maxRepeatPeriod);

        StellarComputeStatistics statistics = _verificationMethodVisit(
            localOptions.verificationMethod,
            [&](auto tag) -> StellarComputeStatistics
            {
                using TTag = decltype(tag);
                SwiftHitVerifier<TTag> swiftVerifier
                {
                    STELLAR_DESIGNATED_INITIALIZER(.eps_match_options = , localOptions),
                    STELLAR_DESIGNATED_INITIALIZER(.verifier_options = , localOptions),
                };

                return _stellarKernel(swiftFinder, localSwiftPattern, swiftVerifier, isPatternDisabled, onAlignmentResult, strand_runtime);
            });

        return statistics;
    }
};

///////////////////////////////////////////////////////////////////////////////
// Creates database segments and calls search_and_verify on each of them
template <typename TAlphabet, typename TId>
inline bool
_stellarMain(
    StringSet<String<TAlphabet>> & databases,
    StringSet<TId> const & databaseIDs,
    uint64_t const & refLen,
    StringSet<String<TAlphabet>> const & queries,
    StringSet<TId> const & queryIDs,
    StellarOptions const & options,
    std::ofstream & outputFile,
    std::ofstream & disabledQueriesFile,
    stellar_app_runtime & stellar_runtime)
{
    // pattern
    auto current_time = stellar_runtime.swift_index_construction_time.now();
    StellarIndex<TAlphabet> stellarIndex{queries, options};
    StellarSwiftPattern<TAlphabet> swiftPattern = stellarIndex.createSwiftPattern();

    if (options.verbose)
        swiftPattern.params.printDots = true;

    // Construct index of the queries
    std::cout << "Constructing index..." << std::endl;
    stellarIndex.construct();
    std::cout << std::endl;
    stellar_runtime.swift_index_construction_time.manual_timing(current_time);

    std::cout << "Aligning all query sequences to database sequence..." << std::endl;

    std::vector<size_t> disabledQueryIDs{};

    // compute and print output statistics
    StellarOutputStatistics outputStatistics{};

    using TDatabaseSegment = stellar::StellarDatabaseSegment<TAlphabet>;
    using TStorage = std::vector<TDatabaseSegment>;

    // positive database strand
    if (options.forward)
    {
        TStorage databaseSegments = _getDatabaseSegments<TAlphabet, TStorage>(databases, options);
        stellar_runtime.forward_strand_stellar_time.measure_time([&]()
        {
            // container for eps-matches
            StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > forwardMatches;
            resize(forwardMatches, length(queries));

            constexpr bool databaseStrand = true;

            DatabaseIDMap<TAlphabet> databaseIDMap{databases, databaseIDs};
            QueryIDMap<TAlphabet> queryIDMap{queries};

            StellarComputeStatisticsCollection computeStatistics;

            //!TODO: the local stuff is not necessary when working on one thread/segment
            StellarOptions localOptions = options;

            for (StellarDatabaseSegment<TAlphabet> const & databaseSegment : databaseSegments)
            {
                size_t const databaseRecordID = databaseIDMap.recordID(databaseSegment);
                TId const & databaseID = databaseIDMap.databaseID(databaseRecordID);

                StellarComputeStatistics statistics = StellarApp<TAlphabet>::search_and_verify
                (
                    databaseSegment,
                    databaseID,
                    queryIDMap,
                    databaseStrand,
                    localOptions,
                    swiftPattern,
                    stellar_runtime.forward_strand_stellar_time.prefiltered_stellar_time,
                    forwardMatches
                );

                computeStatistics.addStatistics(statistics);
            }

            _printStellarStatistics(options.verbose, databaseStrand, databaseIDs, computeStatistics);

            stellar_runtime.forward_strand_stellar_time.post_process_eps_matches_time.measure_time([&]()
            {
                // forwardMatches is an in-out parameter
                // this is the match consolidation
                _postproccessQueryMatches(databaseStrand, refLen, options, forwardMatches, disabledQueryIDs);
            }); // measure_time

            if (_shouldWriteOutputFile(databaseStrand, forwardMatches))
            {
                stellar_runtime.forward_strand_stellar_time.output_eps_matches_time.measure_time([&]()
                {
                    // output forwardMatches on positive database strand
                    _writeAllQueryMatchesToFile(forwardMatches, queryIDs, databaseStrand, options.outputFormat, outputFile);
                }); // measure_time
            }

            outputStatistics = _computeOutputStatistics(forwardMatches);
        }); // measure_time
    }

    // negative (reverse complemented) database strand
    bool const reverse = options.reverse && options.alphabet != "protein" && options.alphabet != "char";
    if (reverse)
    {
        TStorage databaseSegments{};
        stellar_runtime.reverse_complement_database_time.measure_time([&]()
        {
            databaseSegments = _getDatabaseSegments<TAlphabet, TStorage>(databases, options, reverse);
        }); // measure_time

        stellar_runtime.reverse_strand_stellar_time.measure_time([&]()
        {
            // container for eps-matches
            StringSet<QueryMatches<StellarMatch<String<TAlphabet> const, TId> > > reverseMatches;
            resize(reverseMatches, length(queries));

            constexpr bool databaseStrand = false;

            DatabaseIDMap<TAlphabet> databaseIDMap{databases, databaseIDs};
            QueryIDMap<TAlphabet> queryIDMap{queries};

            StellarComputeStatisticsCollection computeStatistics;

            //!TODO: the local stuff is not necessary when working on one thread/segment
            StellarOptions localOptions = options;

            for (StellarDatabaseSegment<TAlphabet> const & databaseSegment : databaseSegments)
            {
                size_t const databaseRecordID = databaseIDMap.recordID(databaseSegment);
                TId const & databaseID = databaseIDMap.databaseID(databaseRecordID);

                StellarComputeStatistics statistics = StellarApp<TAlphabet>::search_and_verify
                (
                    databaseSegment,
                    databaseID,
                    queryIDMap,
                    databaseStrand,
                    localOptions,
                    swiftPattern,
                    stellar_runtime.reverse_strand_stellar_time.prefiltered_stellar_time,
                    reverseMatches
                );

                computeStatistics.addStatistics(statistics);
            }

            _printStellarStatistics(options.verbose, databaseStrand, databaseIDs, computeStatistics);

            stellar_runtime.reverse_strand_stellar_time.post_process_eps_matches_time.measure_time([&]()
            {
                _postproccessQueryMatches(databaseStrand, refLen, options, reverseMatches, disabledQueryIDs);
            }); // measure_time

            if (_shouldWriteOutputFile(databaseStrand, reverseMatches))
            {
                stellar_runtime.reverse_strand_stellar_time.output_eps_matches_time.measure_time([&]()
                {
                    // output reverseMatches on negative database strand
                    _writeAllQueryMatchesToFile(reverseMatches, queryIDs, databaseStrand, options.outputFormat, outputFile);
                }); // measure_time
            }

            outputStatistics.mergeIn(_computeOutputStatistics(reverseMatches));
        }); // measure_time
    }
    std::cout << std::endl;

    // Writes disabled query sequences to disabledFile.
    if (disabledQueriesFile.is_open())
    {
        stellar_runtime.output_disabled_queries_time.measure_time([&]()
        {
            // write disabled query file
            _writeDisabledQueriesToFastaFile(disabledQueryIDs, queryIDs, queries, disabledQueriesFile);
        }); // measure_time
    }

    _writeOutputStatistics(outputStatistics, options.verbose, disabledQueriesFile.is_open());

    return true;
}

template <typename TId>
inline bool
_checkUniqueId(std::set<TId> & uniqueIds, TId const & id)
{
    TId shortId;
    typedef typename Iterator<TId const>::Type TIterator;

    TIterator it = begin(id);
    TIterator itEnd = end(id);

    // (cut at first whitespace)
    while (it != itEnd && *it > ' ')
    {
        appendValue(shortId, *it);
        ++it;
    }

    if (uniqueIds.count(shortId) == 0)
    {
        uniqueIds.insert(shortId);
        return 1;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Imports sequences from a file,
//  stores them in the StringSet seqs and their identifiers in the StringSet ids
template <typename TSequence, typename TId, typename TSize>
inline bool
_importSequences(CharString const & fileName,
                 CharString const & name,
                 StringSet<TSequence> & seqs,
                 StringSet<TId> & ids,
                 TSize & seqLen)
{
    SeqFileIn inSeqs;
    if (!open(inSeqs, (toCString(fileName))))
    {
        std::cerr << "Failed to open " << name << " file." << std::endl;
        return false;
    }

    std::set<TId> uniqueIds; // set of short IDs (cut at first whitespace)
    bool idsUnique = true;

    TSequence seq;
    TId id;
    unsigned seqCount = 0;
    for (; !atEnd(inSeqs); ++seqCount)
    {
        readRecord(id, seq, inSeqs);

        if (name == "database")
            seqLen += length(seq);

        idsUnique &= _checkUniqueId(uniqueIds, id);

        appendValue(seqs, seq, Generous());
        appendValue(ids, id, Generous());
    }

    std::cout << "Loaded " << seqCount << " " << name << " sequence" << ((seqCount > 1) ? "s." : ".") << std::endl;
    if (!idsUnique)
        std::cerr << "WARNING: Non-unique " << name << " ids. Output can be ambiguous.\n";
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Imports the sequence of interest from a file,
// stores it in the StringSet seqs and their identifiers in the StringSet ids
template <typename TSequence, typename TId, typename TSize>
inline bool
_importSequenceOfInterest(CharString const & fileName,
                          unsigned const & sequenceIndex,
                          StringSet<TSequence> & seqs,
                          StringSet<TId> & ids,
                          TSize & seqLen)
{
    SeqFileIn inSeqs;
    if (!open(inSeqs, (toCString(fileName))))
    {
        std::cerr << "Failed to open database file.\n";
        return false;
    }

    TSequence seq;
    TId id;
    unsigned seqCount = 0;
    bool foundSeqOfInterest(false);
    for (; !atEnd(inSeqs); ++seqCount)
    {
        readRecord(id, seq, inSeqs);
        seqLen += length(seq);

        if (seqCount == sequenceIndex)
        {
            appendValue(seqs, seq, Generous());
            appendValue(ids, id, Generous());
            foundSeqOfInterest = true;
            std::cout << "Loaded sequence " << id << ".\n";
        }
    }

    if (foundSeqOfInterest)
        return true;

    std::cerr << "ERROR: Sequence index " << sequenceIndex << " out of range.\n";
    return false;
}


///////////////////////////////////////////////////////////////////////////////
// Parses and outputs parameters, calls _stellarMain().
template <typename TAlphabet>
int mainWithOptions(StellarOptions & options, String<TAlphabet>)
{
    typedef String<TAlphabet> TSequence;

    stellar_app_runtime stellar_time{};
    auto current_time = stellar_time.now();

    // set threads
    omp_set_num_threads(options.threadCount);

    // output file names
    stellar::app::_writeFileNames(options);

    // output parameters
    stellar::app::_writeSpecifiedParams(options);
    stellar::app::_writeCalculatedParams(options);

    // import query sequences
    StringSet<TSequence> queries;
    StringSet<CharString> queryIDs;

    using TSize = decltype(length(queries[0]));
    TSize queryLen{0};   // does not get populated currently
    //!TODO: split query sequence
    bool const queriesSuccess = stellar_time.input_queries_time.measure_time([&]()
    {
        return _importSequences(options.queryFile, "query", queries, queryIDs, queryLen);
    });
    if (!queriesSuccess)
        return 1;

    // import database sequence
    StringSet<TSequence> databases;
    StringSet<CharString> databaseIDs;

    TSize refLen{0};
    bool const databasesSuccess = stellar_time.input_databases_time.measure_time([&]()
    {
        if (!options.prefilteredSearch)
            return _importSequences(options.databaseFile, "database", databases, databaseIDs, refLen);
        else
            return _importSequenceOfInterest(options.databaseFile, options.sequenceOfInterest, databases, databaseIDs, refLen);
    });
    if (!databasesSuccess)
        return 1;

    std::cout << std::endl;
    stellar::app::_writeMoreCalculatedParams(options, refLen, queries);

    // open output files
    std::ofstream outputFile(toCString(options.outputFile), ::std::ios_base::out | ::std::ios_base::app);
    if (!outputFile.is_open())
    {
        std::cerr << "Could not open output file." << std::endl;
        return 1;
    }

    std::ofstream disabledQueriesFile;
    if (options.disableThresh != std::numeric_limits<unsigned>::max())
    {
        disabledQueriesFile.open(toCString(options.disabledQueriesFile), ::std::ios_base::out | ::std::ios_base::app);
        if (!disabledQueriesFile.is_open())
        {
            std::cerr << "Could not open file for disabled queries." << std::endl;
            return 1;
        }
    }

    // stellar on all databases and queries writing results to file
    if (!_stellarMain(databases, databaseIDs, refLen, queries, queryIDs, options, outputFile, disabledQueriesFile, stellar_time))
        return 1;

    if (options.verbose && options.noRT == false)
    {
        stellar_time.manual_timing(current_time);

        auto _print_stellar_strand_time = [](stellar_strand_time const & strand_runtime, std::string strandDirection)
        {
            stellar_kernel_runtime const & prefiltered_stellar_time
                = strand_runtime.prefiltered_stellar_time;
            stellar_verification_time const & verification_time
                = strand_runtime.prefiltered_stellar_time.verification_time;
            stellar_extension_time const & extension_time
                = verification_time.extension_time;
            stellar_best_extension_time const & best_extension_time
                = extension_time.best_extension_time;

            std::cout << "       + Prefiltered Stellar Time (" << strandDirection << "): " << prefiltered_stellar_time.milliseconds() << "ms" << std::endl;
            std::cout << "          + Swift Filter Time (" << strandDirection << "): " << prefiltered_stellar_time.swift_filter_time.milliseconds() << "ms" << std::endl;
            std::cout << "          + Seed Verification Time (" << strandDirection << "): " << verification_time.milliseconds() << "ms" << std::endl;
            std::cout << "             + Find Next Local Alignment Time (" << strandDirection << "): " << verification_time.next_local_alignment_time.milliseconds() << "ms" << std::endl;
            std::cout << "             + Split At X-Drops Time (" << strandDirection << "): " << verification_time.split_at_x_drops_time.milliseconds() << "ms" << std::endl;
            std::cout << "             + Extension Time (" << strandDirection << "): " << extension_time.milliseconds() << "ms" << std::endl;
            std::cout << "                + Extend Seed Time (" << strandDirection << "): " << extension_time.extend_seed_time.milliseconds() << "ms" << std::endl;
            std::cout << "                + Best Extension Time (" << strandDirection << "): " << best_extension_time.milliseconds() << "ms" << std::endl;
            std::cout << "                   + Banded Needleman-Wunsch Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_time.milliseconds() << "ms" << std::endl;
            std::cout << "                      + Banded Needleman-Wunsch (Left Extension) Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_left_time.milliseconds() << "ms" << std::endl;
            std::cout << "                      + Banded Needleman-Wunsch (Right Extension) Time (" << strandDirection << "): " << best_extension_time.banded_needleman_wunsch_right_time.milliseconds() << "ms" << std::endl;
            std::cout << "                   + Longest EPS Match Time (" << strandDirection << "): " << best_extension_time.longest_eps_match_time.milliseconds() << "ms" << std::endl;
            std::cout << "                   + Construct Alignment Time (" << strandDirection << "): " << best_extension_time.construct_seed_alignment_time.milliseconds() << "ms" << std::endl;
            std::cout << "                   = total time: " << best_extension_time.total_time().milliseconds() << "ms" << std::endl;
            std::cout << "                = total time: " << extension_time.total_time().milliseconds() << "ms" << std::endl;
            std::cout << "             = total time: " << verification_time.total_time().milliseconds() << "ms" << std::endl;
            std::cout << "          = total time: " << prefiltered_stellar_time.total_time().milliseconds() << "ms" << std::endl;
            std::cout << "       + Post-Process Eps-Matches Time (" << strandDirection << "): " << strand_runtime.post_process_eps_matches_time.milliseconds() << "ms" << std::endl;
            std::cout << "       + File Output Eps-Matches Time (" << strandDirection << "): " << strand_runtime.output_eps_matches_time.milliseconds() << "ms" << std::endl;
            std::cout << "       = total time: " << strand_runtime.total_time().milliseconds() << "ms" << std::endl;
        };

        std::cout << "Running time: " << stellar_time.milliseconds() << "ms" << std::endl;
        std::cout << " * Stellar Application Time: " << stellar_time.milliseconds() << "ms" << std::endl;
        std::cout << "    + File Input Queries Time: " << stellar_time.input_queries_time.milliseconds() << "ms" << std::endl;
        std::cout << "    + File Input Databases Time: " << stellar_time.input_databases_time.milliseconds() << "ms" << std::endl;
        std::cout << "    + SwiftFilter Construction Time: " << stellar_time.swift_index_construction_time.milliseconds() << "ms" << std::endl;
        std::cout << "    + Stellar Forward Strand Time: " << stellar_time.forward_strand_stellar_time.milliseconds() << "ms" << std::endl;
        _print_stellar_strand_time(stellar_time.forward_strand_stellar_time, "Forward");
        std::cout << "    + Database Reverse Complement Time: " << stellar_time.reverse_complement_database_time.milliseconds() << "ms" << std::endl;
        std::cout << "    + Stellar Reverse Strand Time: " << stellar_time.reverse_strand_stellar_time.milliseconds() << "ms" << std::endl;
        _print_stellar_strand_time(stellar_time.reverse_strand_stellar_time, "Reverse");
        std::cout << "    + File Output Disabled Queries Time: " << stellar_time.output_disabled_queries_time.milliseconds() << "ms" << std::endl;
        std::cout << "    = total time: " << stellar_time.total_time().milliseconds() << "ms" << std::endl;
    }

    return 0;
}

} // namespace stellar::app

} // namespace stellar

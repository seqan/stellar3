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

#include <stellar/database_id_map.hpp>
#include <stellar/io/import_sequence.hpp>
#include <stellar/stellar.hpp>
#include <stellar/stellar_database_segment.hpp>
#include <stellar/stellar_index.hpp>
#include <stellar/stellar_launcher.hpp>
#include <stellar/stellar_output.hpp>
#include <stellar/utils/stellar_app_runtime.hpp>

#include <stellar/diagnostics/print.tpp>

namespace stellar
{
using namespace seqan2;
} // namespace stellar

//////////////////////////////////////////////////////////////////////////////
namespace seqan2 {

template <>
struct FunctorComplement<AminoAcid>:
    public::std::function<AminoAcid(AminoAcid)>
{
    inline AminoAcid operator()(AminoAcid x) const
    {
        return x;
    }

};

} // namespace seqan2

namespace stellar
{

namespace app
{

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

            StellarOptions localOptions = options;
            for (StellarDatabaseSegment<TAlphabet> const & databaseSegment : databaseSegments)
            {
                size_t const databaseRecordID = databaseIDMap.recordID(databaseSegment);
                TId const & databaseID = databaseIDMap.databaseID(databaseRecordID);

                StellarComputeStatistics statistics = StellarLauncher<TAlphabet>::search_and_verify
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

            StellarOptions localOptions = options;
            for (StellarDatabaseSegment<TAlphabet> const & databaseSegment : databaseSegments)
            {
                size_t const databaseRecordID = databaseIDMap.recordID(databaseSegment);
                TId const & databaseID = databaseIDMap.databaseID(databaseRecordID);

                StellarComputeStatistics statistics = StellarLauncher<TAlphabet>::search_and_verify
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

///////////////////////////////////////////////////////////////////////////////
// Parses and outputs parameters, calls _stellarMain().
template <typename TAlphabet>
int mainWithOptions(StellarOptions & options, String<TAlphabet>)
{
    typedef String<TAlphabet> TSequence;

    stellar_app_runtime stellar_time{};
    auto current_time = stellar_time.now();

    // output file names
    stellar::_writeFileNames(options);

    // output parameters
    stellar::_writeSpecifiedParams(options);
    stellar::_writeCalculatedParams(options);

    // import query sequences
    StringSet<TSequence> queries;
    StringSet<CharString> queryIDs;

    using TSize = decltype(length(queries[0]));
    TSize queryLen{0};   // does not get populated currently
    //!TODO: split query sequence
    bool const queriesSuccess = stellar_time.input_queries_time.measure_time([&]()
    {
        return _importAllSequences(options.queryFile.c_str(), "query", queries, queryIDs, queryLen);
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
            return _importAllSequences(options.databaseFile.c_str(), "database", databases, databaseIDs, refLen);
        else
        {
            if (options.referenceLength > 0)
            {
                refLen = options.referenceLength;
                return _importSequencesOfInterest(options.databaseFile.c_str(), options.binSequences, databases, databaseIDs);
            }
            else
            {
                return _importSequencesOfInterest(options.databaseFile.c_str(), options.binSequences, databases, databaseIDs, refLen);
            }
        }
    });
    if (!databasesSuccess)
        return 1;

    std::cout << std::endl;
    stellar::_writeMoreCalculatedParams(options, refLen, queries);

    // open output files
    std::ofstream outputFile(options.outputFile.c_str(), ::std::ios_base::out | ::std::ios_base::app);
    if (!outputFile.is_open())
    {
        std::cerr << "Could not open output file." << std::endl;
        return 1;
    }

    std::ofstream disabledQueriesFile;
    if (options.disableThresh != std::numeric_limits<size_t>::max())
    {
        disabledQueriesFile.open(options.disabledQueriesFile.c_str(), ::std::ios_base::out | ::std::ios_base::app);
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


#pragma once

#include <seqan/seq_io.h>

#include <stellar/stellar_sequence_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

template <typename TAlphabet>
struct StellarDatabaseSegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TInfixSegment;
    using TNestedFinderSegment = seqan::Segment<TInfixSegment, seqan::InfixSegment>;

    using TBase::TBase; // import constructor

    static StellarDatabaseSegment<TAlphabet> fromFinderMatch(TInfixSegment const & finderMatch)
    {
        seqan::String<TAlphabet> const & underlyingDatabase = host(finderMatch);
        return {underlyingDatabase, seqan::beginPosition(finderMatch), seqan::endPosition(finderMatch)};
    }

    seqan::String<TAlphabet> const & underlyingDatabase() const &
    {
        return this->underlyingSequence();
    }

    TNestedFinderSegment asFinderSegment() const
    {
        seqan::String<TAlphabet> const & _database = underlyingDatabase();
        auto finderInfix = this->asInfixSegment();

        TInfixSegment const finderInfixSeq = infix(_database, 0, length(_database));
        TNestedFinderSegment finderSegment(finderInfixSeq,
            seqan::beginPosition(finderInfix) - seqan::beginPosition(_database),
            seqan::endPosition(finderInfix) - seqan::beginPosition(_database));
        return finderSegment;
    }
};

template <typename TAlphabet, typename TStorage>
TStorage _getDatabaseSegments(StringSet<String<TAlphabet>> & databases, StellarOptions const & options, bool const reverse = false)
{
    TStorage databaseSegments{};
    if (options.prefilteredSearch)
    {
        if (length(databases[0]) < options.segmentEnd)
            throw std::runtime_error{"Segment end out of range"};

        if (options.segmentEnd <= options.segmentBegin)
            throw std::runtime_error{"Incorrect segment definition"};

        if (options.segmentEnd < options.minLength + options.segmentBegin)
            throw std::runtime_error{"Segment shorter than minimum match length"};

        if (reverse)
        {
            reverseComplement(databases[0]);
            databaseSegments.emplace_back(databases[0], length(databases[0]) - options.segmentEnd, length(databases[0]) - options.segmentBegin);
        }
        else
            databaseSegments.emplace_back(databases[0], options.segmentBegin, options.segmentEnd);
    }
    else
        for (auto & database : databases)
        {
            if (reverse)
                reverseComplement(database);

            if (length(database) >= options.minLength)
                databaseSegments.emplace_back(database, 0u, length(database));
        }

    return databaseSegments;
}

} // namespace stellar

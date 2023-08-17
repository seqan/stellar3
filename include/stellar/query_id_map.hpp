
#pragma once

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

/**
 * !\brief Abstract base struct.
 */
template <typename TAlphabet>
struct QueryIDMap
{
    virtual ~QueryIDMap() = 0;
};

template <typename TAlphabet>
QueryIDMap<TAlphabet>::~QueryIDMap() {}

/**
 * !\brief Struct that exposes the numerical index of a query sequence in the list of queries.
 */
template <typename TAlphabet>
struct QuerySequenceIDMap : public QueryIDMap<TAlphabet>
{
    StringSet<String<TAlphabet>> const & sequences;

    QuerySequenceIDMap(StringSet<String<TAlphabet>> const & seq) : sequences(seq) {};

    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment.underlyingQuery());
    }

    size_t recordID(String<TAlphabet> const & query) const
    {
        String<TAlphabet> const * begin = &sequences[0];
        String<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }
};

/**
 * !\brief Struct that exposes the numerical index of a query segment in the list of queries.
 */
template <typename TAlphabet>
struct QuerySegmentIDMap : public QueryIDMap<TAlphabet>
{
    StringSet<StellarQuerySegment<TAlphabet>> const & segments;

    QuerySegmentIDMap(StringSet<StellarQuerySegment<TAlphabet>> const & seg) : segments(seg) {}

    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment);
    }

    size_t recordID(StellarQuerySegment<TAlphabet> const & segment) const
    {
        StellarQuerySegment<TAlphabet> const * begin = &segments[0];
        StellarQuerySegment<TAlphabet> const * current = std::addressof(segment);
        return current - begin;
    }
};

} // namespace stellar

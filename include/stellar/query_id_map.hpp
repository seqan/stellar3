
#pragma once

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

/**
 * !\brief Struct that exposes the numerical index of a query sequence in the list of queries.
 */
template <typename TAlphabet>
struct QueryIDMap
{
    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment.underlyingQuery());
    }

    size_t recordID(String<TAlphabet> const & query) const
    {
        String<TAlphabet> const * begin = &queries[0];
        String<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }

    StringSet<String<TAlphabet>> const & queries;
};

/**
 * !\brief Struct that exposes the numerical index of a query segment in the list of queries.
 */
template <typename TAlphabet>
struct QuerySegmentIDMap : public QueryIDMap<TAlphabet>
{
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

    StringSet<StellarQuerySegment<TAlphabet>> const & segments;
};

} // namespace stellar

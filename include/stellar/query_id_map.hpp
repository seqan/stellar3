
#pragma once

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

/**
 * !\brief Struct that exposes the numerical index of a query sequences in the list of queries.
 */
template <typename TAlphabet>
struct QueryIDMap
{
    StringSet<StellarQuerySegment<TAlphabet>> const & queries;

    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment);
    }

    size_t recordID(StellarQuerySegment<TAlphabet> const & query) const
    {
        StellarQuerySegment<TAlphabet> const * begin = &queries[0];
        StellarQuerySegment<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }
};

}

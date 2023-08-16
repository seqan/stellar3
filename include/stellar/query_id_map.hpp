
#pragma once

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

template <typename TAlphabet>
struct QueryIDMap
{
    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment);
    }

    size_t recordID(StellarQuerySegment<TAlphabet> const & segment) const
    {
        StellarQuerySegment<TAlphabet> const * begin = &queries[0];
        StellarQuerySegment<TAlphabet> const * current = std::addressof(segment);
        return current - begin;
    }

    StringSet<StellarQuerySegment<TAlphabet>> const & queries;
};

} // namespace stellar

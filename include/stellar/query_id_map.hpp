
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
    using TQuery = seqan2::Segment<seqan2::String<TAlphabet> const, seqan2::InfixSegment>;
    StringSet<TQuery> const & queries;

    size_t recordID(StellarSwiftPattern<TAlphabet> const & pattern) const
    {
        StellarQuerySegment<TAlphabet> querySegment
            = StellarQuerySegment<TAlphabet>::fromPatternMatch(pattern);
        return recordID(querySegment.asInfixSegment());
    }

    size_t recordID(TQuery const & query) const
    {
        TQuery const * begin = &queries[0];
        TQuery const * current = std::addressof(query);
        return current - begin;
    }
};

}

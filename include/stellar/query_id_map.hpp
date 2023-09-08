
#pragma once

#include <stellar/stellar_index.hpp>
#include <stellar/stellar_query_segment.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

template <typename TAlphabet, typename TId = CharString>
struct QueryIDMap
{
    size_t recordID(String<TAlphabet> const & query) const
    {
        String<TAlphabet> const * begin = &queries[0];
        String<TAlphabet> const * current = std::addressof(query);
        return current - begin;
    }

    StringSet<String<TAlphabet> > const & queries;
};

} // namespace stellar


#pragma once

#include <stellar/stellar_database_segment.hpp>

namespace stellar
{

template <typename TAlphabet, typename TId = seqan::CharString>
struct DatabaseIDMap
{
    size_t recordID(seqan::String<TAlphabet> const & database) const
    {
        seqan::String<TAlphabet> const * begin = &databases[0];
        seqan::String<TAlphabet> const * current = std::addressof(database);
        return current - begin;
    }

    TId const & databaseID(seqan::String<TAlphabet> const & database) const
    {
        return databaseIDs[recordID(database)];
    }

    seqan::StringSet<seqan::String<TAlphabet> > const & databases;
    seqan::StringSet<TId> const & databaseIDs;
};

} // namespace stellar

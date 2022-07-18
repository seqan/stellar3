
#pragma once

#include <seqan3/std/span>
#include <stellar/stellar_database_segment.hpp>
#include <stellar/stellar_index.hpp>

namespace stellar
{

template <typename TAlphabet_>
struct prefilter_agent
{
    using TAlphabet = TAlphabet_;

    using TDatabaseSegment = stellar::StellarDatabaseSegment<TAlphabet>;
    using TDatabaseSegments = std::span<TDatabaseSegment const>;
    using TQueryFilter = stellar::StellarSwiftPattern<TAlphabet_>;
    using TPrefilterCallback = std::function<void (TDatabaseSegments, TQueryFilter &)>;

    virtual ~prefilter_agent() = default;

    virtual void prefilter(TPrefilterCallback) = 0;
};

} // namespace stellar

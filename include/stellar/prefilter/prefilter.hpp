
#pragma once

#include <stellar/options/eps_match_options.hpp>
#include <stellar/prefilter/prefilter_agents.hpp>

namespace stellar
{

template <typename TAlphabet_>
struct prefilter
{
    using TAlphabet = TAlphabet_;

    virtual ~prefilter() = default;

    virtual stellar::prefilter_agents<TAlphabet> agents(size_t const agentCount, stellar::EPSMatchOptions const epsMatchOptions) = 0;
};

} // namespace stellar

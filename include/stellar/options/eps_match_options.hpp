
#pragma once

#include <stellar/utils/fraction.hpp>

namespace stellar
{

struct EPSMatchOptions
{
    stellar::utils::fraction epsilon{5, 100}; // maximal error rate
    double numEpsilon{0.05};
    size_t minLength{100}; // minimal length of an epsilon-match
};

} // namespace stellar

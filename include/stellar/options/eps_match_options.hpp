
#pragma once

#include <stellar/utils/fraction.hpp>

namespace stellar
{

struct EPSMatchOptions
{
    stellar::utils::fraction epsilon{5, 100}; // maximal error rate
    int minLength{100}; // minimal length of an epsilon-match
};

} // namespace stellar

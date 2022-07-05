
#pragma once

#include <limits>

namespace stellar
{

struct IndexOptions
{
    unsigned qGram{std::numeric_limits<unsigned>::max()}; // length of the q-grams
    double qgramAbundanceCut{1};
};

} // namespace stellar

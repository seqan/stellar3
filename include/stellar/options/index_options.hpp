
#pragma once

#include <limits>

namespace stellar
{

struct IndexOptions
{
    size_t qGram{std::numeric_limits<size_t>::max()}; // length of the q-grams
    double qgramAbundanceCut{1};
};

} // namespace stellar

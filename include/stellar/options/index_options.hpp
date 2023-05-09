
#pragma once

#include <limits>

namespace stellar
{

struct IndexOptions
{
    size_t qGram{7}; // length of the q-grams
    double qgramAbundanceCut{1};
};

} // namespace stellar

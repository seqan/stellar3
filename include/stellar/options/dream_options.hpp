
#pragma once

namespace stellar
{

struct DREAMOptions
{
    // Whether only a part of the reference should be searched.
    bool prefilteredSearch{false};

    // Specify the segment (and sequence) of interest.
    unsigned sequenceOfInterest;
    uint64_t segmentBegin;
    uint64_t segmentEnd;
};

} // namespace stellar

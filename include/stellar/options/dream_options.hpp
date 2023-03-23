
#pragma once

namespace stellar
{

struct DREAMOptions
{
    // Whether only a part of the reference should be searched.
    bool prefilteredSearch{false};
    uint64_t referenceLength;

    // Specify the segment (and sequence) of interest.
    unsigned sequenceOfInterest;
    unsigned segmentBegin;
    unsigned segmentEnd;
};

} // namespace stellar

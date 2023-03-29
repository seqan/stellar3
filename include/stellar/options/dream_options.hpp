
#pragma once

namespace stellar
{

struct DREAMOptions
{
    // Whether only a part of the reference should be searched.
    bool prefilteredSearch{false};
    uint64_t referenceLength{0};

    // Specify the segment (and sequence) of interest.
    size_t sequenceOfInterest;
    uint32_t segmentBegin;
    uint32_t segmentEnd;
};

} // namespace stellar

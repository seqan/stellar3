
#pragma once

#include <stellar/stellar_types.hpp>

namespace stellar {

template <typename TVerifierTag>
struct SwiftHitVerifier
{
    using TSize = int;
    using TDrop = double;

    double const epsilon;
    TSize const minLength;
    TDrop const xDrop;

    template <typename TSequence, typename TDelta, typename TOnAlignmentResultFn>
    void verify(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & finderSegment,
                Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & patternSegment,
                TDelta const delta,
                TOnAlignmentResultFn && onAlignmentResult)
    {
        verifySwiftHit(finderSegment, patternSegment, epsilon, minLength, xDrop,
                       delta, onAlignmentResult, TVerifierTag{});
    }
};

} // namespace stellar

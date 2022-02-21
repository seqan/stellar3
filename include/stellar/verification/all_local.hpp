
#pragma once

#include <stellar/verification/detail/all_or_best_local.hpp>

namespace stellar
{

///////////////////////////////////////////////////////////////////////////////
// Conducts banded local alignment on swift hit (= computes eps-cores),
//  splits eps-cores at X-drops, and calls _extendAndExtract for extension of eps-cores
template<typename TSequence, typename TEpsilon, typename TSize, typename TDrop, typename TDelta,
         typename TOnAlignmentResultFn>
void
verifySwiftHit(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infH,
               Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infV,
               TEpsilon const eps,
               TSize const minLength,
               TDrop const xDrop,
               TDelta const delta,
               TOnAlignmentResultFn && onAlignmentResult,
               AllLocal) {

    // false == all local matches
    allOrBestLocal(infH, infV, eps, minLength, xDrop, delta, onAlignmentResult, std::false_type{});
}

} // namespace stellar


#pragma once

#include <stellar/verification/detail/all_or_best_local.hpp>

namespace stellar
{

///////////////////////////////////////////////////////////////////////////////
// Conducts banded local alignment on swift hit (= computes eps-cores),
//  splits eps-cores at X-drops, and calls _extendAndExtract for extension of eps-cores
template<typename TSequence, typename TEpsilon, typename TSize, typename TDelta, typename TDrop,
         typename TSize1, typename TId, typename TSource>
void
verifySwiftHit(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infH,
               Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & infV,
               TEpsilon const eps,
               TSize const minLength,
               TDrop const xDrop,
               TDelta const delta,
               TSize1 const disableThresh,
               TSize1 & compactThresh,
               TSize1 const numMatches,
               TId const & databaseId,
               bool const dbStrand,
               QueryMatches<StellarMatch<TSource const, TId> > & matches,
               BestLocal) {
    allOrBestLocal(
        infH,
        infV,
        eps,
        minLength,
        xDrop,
        delta,
        disableThresh,
        compactThresh,
        numMatches,
        databaseId,
        dbStrand,
        matches,
        std::true_type{} // true == best local match
    );
}

} // namespace stellar

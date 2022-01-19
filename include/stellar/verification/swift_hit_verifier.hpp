
#pragma once

#include <stellar/stellar_types.hpp>

namespace stellar {

template <typename TVerifierTag>
struct SwiftHitVerifier
{
    using TSize = int;
    using TDrop = double;
    using TSize1 = unsigned;
    using TId = CharString;

    double const epsilon;
    TSize const minLength;
    TDrop const xDrop;
    TSize1 const disableThresh;
    TSize1 & compactThresh; // will be updated in _insertMatch
    TSize1 const numMatches;
    TId const & databaseID;
    bool const databaseStrand;

    template <typename TSequence, typename TDelta, typename TSource, typename TId>
    void verify(Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & finderSegment,
                Segment<Segment<TSequence const, InfixSegment>, InfixSegment> const & patternSegment,
                TDelta const delta,
                QueryMatches<StellarMatch<TSource const, TId> > & queryMatches)
    {
        verifySwiftHit(finderSegment, patternSegment, epsilon, minLength, xDrop,
                       delta, disableThresh, compactThresh,
                       numMatches, databaseID, databaseStrand, queryMatches, TVerifierTag{});
    }
};

} // namespace stellar

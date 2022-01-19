
#pragma once

#include <stellar/stellar_extension.hpp>
#include <stellar/stellar_types.hpp>

namespace stellar
{

///////////////////////////////////////////////////////////////////////////////
// Conducts banded alignment on swift hit, extends alignment, and extracts longest contained eps-match.
template<typename TSequence, typename TEpsilon, typename TSize, typename TDelta,
         typename TDrop, typename TSize1, typename TSource, typename TId>
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
               BandedGlobalExtend) {
    using TInfix = Segment<TSequence const, InfixSegment>;
    typedef Segment<TInfix, InfixSegment> TSegment;
    typedef typename StellarMatch<TSource const, TId>::TAlign TAlign;

    // define a scoring scheme
    typedef int TScore;
    TScore match = 1;
    TScore mismatchIndel = (TScore)_max((TScore) ceil(-1/eps) + 1, -(TScore)length(host(infH)));
    Score<TScore> scoreMatrix(match, mismatchIndel, mismatchIndel);
    TScore scoreDropOff = (TScore) _max((TScore) xDrop * (-mismatchIndel), MinValue<TScore>::VALUE + 1);

    // diagonals for banded alignment
    int64_t upperDiag = 0;
    int64_t lowerDiag = endPosition(infH) - (int64_t)endPosition(infV) - beginPosition(infH) + beginPosition(infV);
    if (beginPosition(infV) == 0) upperDiag = lowerDiag + delta;
    if (endPosition(infV) == endPosition(host(infV))) lowerDiag = -(int64_t)delta;

    // banded alignment on parallelogram
    Align<TSegment> bandedAlign;
    resize(rows(bandedAlign), 2);
    assignSource(row(bandedAlign, 0), infH);
    assignSource(row(bandedAlign, 1), infV);
    globalAlignment(bandedAlign, scoreMatrix, lowerDiag, upperDiag, NeedlemanWunsch());

    // create alignment object for the complete sequences
    TAlign align;
    resize(rows(align), 2);
    setSource(row(align, 0), host(host(infH)));
    setSource(row(align, 1), host(host(infV)));

    // extend alignment and obtain longest contained eps-match
    // TODO: something is wrong here, e.g. extract around seed, but also something else
    if (!_extendAndExtract(bandedAlign, scoreDropOff, scoreMatrix, infH, infV, EXTEND_BOTH, minLength, eps, align))
        return;

    // insert eps-match in matches string
    StellarMatch<TSource const, TId> m(align, databaseId, dbStrand);
    _insertMatch(matches, m, minLength, disableThresh, compactThresh, numMatches);
}

} // namespace stellar

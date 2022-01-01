
#pragma once

#include <stellar/stellar_sequence_segment.hpp>

namespace stellar
{

template <typename TAlphabet>
struct StellarQuerySegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TInfixSegment;
    using TNestedPatternSegment = seqan::Segment<TInfixSegment, seqan::InfixSegment>;

    using TBase::TBase; // import constructor

    template <typename TSwiftPattern>
    static StellarQuerySegment<TAlphabet> fromPatternMatch(TSwiftPattern const & swiftPattern);

    seqan::String<TAlphabet> const & underlyingQuery() const &
    {
        return this->underlyingSequence();
    }

    TNestedPatternSegment asPatternSegment() const
    {
        seqan::String<TAlphabet> const & _query = underlyingQuery();
        auto patternInfix = this->asInfixSegment();

        TInfixSegment const patternInfixSeq = infix(_query, 0, length(_query));
        return {
            patternInfixSeq,
            seqan::beginPosition(patternInfix) - seqan::beginPosition(patternInfixSeq),
            seqan::endPosition(patternInfix) - seqan::beginPosition(patternInfixSeq)
        };
    }
};

} // namespace stellar

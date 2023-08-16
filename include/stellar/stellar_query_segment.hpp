
#pragma once

#include <valik/search/query_record.hpp>

#include <stellar/stellar_sequence_segment.hpp>

namespace stellar
{

template <typename TAlphabet>
struct StellarQuerySegment : public StellarSequenceSegment<TAlphabet>
{
    using TBase = StellarSequenceSegment<TAlphabet>;

    using typename TBase::TString;
    using typename TBase::TInfixSegment;
    using TNestedPatternSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    using TBase::TBase; // import constructor

    template <typename TSwiftPattern>
    static StellarQuerySegment<TAlphabet> fromPatternMatch(TSwiftPattern const & swiftPattern);

    seqan2::String<TAlphabet> const & underlyingQuery() const &
    {
        return this->underlyingSequence();
    }

    TNestedPatternSegment asPatternSegment() const
    {
        seqan2::String<TAlphabet> const & _query = underlyingQuery();
        auto patternInfix = this->asInfixSegment();

        TInfixSegment const patternInfixSeq = infix(_query, 0, length(_query));
        return {
            patternInfixSeq,
            seqan2::beginPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq),
            seqan2::endPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq)
        };
    }

    TString asString() const
    {
        TString const & _query = underlyingQuery();
        //!TODO: get the infix string
        return _query;
    }
};

} // namespace stellar

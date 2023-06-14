
#pragma once

#include <seqan/sequence.h>

namespace stellar
{

template <typename TAlphabet>
struct StellarSequenceSegment
{
    using TString = seqan2::String<TAlphabet>;
    using TInfixSegment = seqan2::Segment<TString const, seqan2::InfixSegment>;

    StellarSequenceSegment() = default;

    template <typename TOtherString, typename = std::enable_if_t< std::is_same_v<TString, TOtherString> > >
    StellarSequenceSegment(
        TOtherString const & sequence,
        size_t const beginPosition,
        size_t const endPosition)
        : _sequenceSegment{sequence, beginPosition, endPosition}
    {}

    seqan2::String<TAlphabet> const & underlyingSequence() const &
    {
        return host(_sequenceSegment);
    }

    size_t beginPosition() const
    {
        return seqan2::beginPosition(_sequenceSegment);
    }

    size_t endPosition() const
    {
        return seqan2::endPosition(_sequenceSegment);
    }

    std::pair<size_t, size_t> interval() const
    {
        return {beginPosition(), endPosition()};
    }

    size_t size() const
    {
        assert(endPosition() >= beginPosition());
        return endPosition() - beginPosition();
    }

    TInfixSegment asInfixSegment() const
    {
        return _sequenceSegment;
    }

    friend bool operator<(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) < 0; }
    friend bool operator<=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) <= 0; }
    friend bool operator==(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) == 0; }
    friend bool operator!=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) != 0; }
    friend bool operator>(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) > 0; }
    friend bool operator>=(StellarSequenceSegment const & s1, StellarSequenceSegment const & s2) { return s1.compare_three_way(s2) >= 0; }

private:

    std::ptrdiff_t compare_three_way(StellarSequenceSegment const & otherSegment) const
    {
        std::ptrdiff_t diff = std::addressof(this->underlyingSequence())
                            - std::addressof(otherSegment.underlyingSequence());

        if (diff != 0)
            return diff;

        diff = static_cast<std::ptrdiff_t>(this->beginPosition()) - static_cast<std::ptrdiff_t>(otherSegment.beginPosition());

        if (diff != 0)
            return diff;

        diff = static_cast<std::ptrdiff_t>(this->endPosition()) - static_cast<std::ptrdiff_t>(otherSegment.endPosition());
        return diff;
    }

    TInfixSegment _sequenceSegment;
};

} // namespace stellar

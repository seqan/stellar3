
#pragma once

#include <stellar/stellar_sequence_segment.hpp>

namespace stellar
{

template <typename TAlphabet>
struct StellarQuerySegment
{
    using TString = seqan2::String<TAlphabet>;
    using TInfixSegment = seqan2::Segment<TString const, seqan2::InfixSegment>;
    using TNestedPatternSegment = seqan2::Segment<TInfixSegment, seqan2::InfixSegment>;

    size_t const beginPosition;
    size_t const endPosition;

    template <typename TOtherString, typename = std::enable_if_t< std::is_same_v<TString, TOtherString> > >
    StellarQuerySegment(
        TOtherString const & sequence,
        size_t const begin,
        size_t const end)
        : _underlyingSequence{sequence}, beginPosition(begin), endPosition(end)
    {}

    std::pair<size_t, size_t> interval() const
    {
        return {beginPosition, endPosition};
    }

    size_t size() const
    {
        assert(endPosition >= beginPosition);
        return endPosition - beginPosition;
    }

    template <typename TSwiftPattern>
    static StellarQuerySegment<TAlphabet> fromPatternMatch(TSwiftPattern const & swiftPattern);

    TString const & underlyingQuery() const &
    {
        return _underlyingSequence;
    }

    TInfixSegment asInfixSegment() const
    {
        return {_underlyingSequence, beginPosition, endPosition};
    }

    TNestedPatternSegment asPatternSegment() const
    {
        TString const & _query = underlyingQuery();
        auto patternInfix = this->asInfixSegment();

        TInfixSegment const patternInfixSeq = infix(_query, 0, length(_query));
        return {
            patternInfixSeq,
            seqan2::beginPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq),
            seqan2::endPosition(patternInfix) - seqan2::beginPosition(patternInfixSeq)
        };
    }

    friend bool operator<(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) < 0; }
    friend bool operator<=(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) <= 0; }
    friend bool operator==(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) == 0; }
    friend bool operator!=(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) != 0; }
    friend bool operator>(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) > 0; }
    friend bool operator>=(StellarQuerySegment const & s1, StellarQuerySegment const & s2) { return s1.compare_three_way(s2) >= 0; }

    private:
        TString const & _underlyingSequence;

        std::ptrdiff_t compare_three_way(StellarQuerySegment const & otherSegment) const
        {
            std::ptrdiff_t diff = std::addressof(this->underlyingQuery())
                                - std::addressof(otherSegment.underlyingQuery());

            if (diff != 0)
                return diff;

            diff = static_cast<std::ptrdiff_t>(this->beginPosition) - static_cast<std::ptrdiff_t>(otherSegment.beginPosition);

            if (diff != 0)
                return diff;

            diff = static_cast<std::ptrdiff_t>(this->endPosition) - static_cast<std::ptrdiff_t>(otherSegment.endPosition);
            return diff;
        }
};

template <typename TAlphabet>
std::ostream& operator<<(std::ostream& os, StellarQuerySegment<TAlphabet> const & segment)
{
    os << segment.asInfixSegment() << '\n';
    return os;
}

} // namespace stellar


#pragma once

// can we replace this include by some forwards?
// needed for seqan::indexText, seqan::needle
#include <seqan/index.h>

#include <stellar/stellar_sequence_segment.hpp>

namespace stellar
{

template <typename TAlphabet>
template <typename TSwiftPattern>
StellarQuerySegment<TAlphabet>
StellarQuerySegment<TAlphabet>::fromPatternMatch(TSwiftPattern const & swiftPattern)
{
    size_t const queryID = swiftPattern.curSeqNo;
    auto const & queryInfix = seqan::getSequenceByNo(queryID, seqan::indexText(seqan::needle(swiftPattern)));
    static_assert(std::is_same_v<decltype(queryInfix), TInfixSegment const &>);
    auto const & underlyingQuery = host(queryInfix);
    static_assert(std::is_same_v<decltype(underlyingQuery), seqan::String<TAlphabet> const &>);
    auto const queryInfixInfix = seqan::infix(swiftPattern, queryInfix);

    return {underlyingQuery, seqan::beginPosition(queryInfixInfix), seqan::endPosition(queryInfixInfix)};
}

} // namespace stellar


#pragma once

// can we replace this include by some forwards?
// needed for seqan2::indexText, seqan2::needle
#include <seqan/index.h>

#include <stellar/stellar_sequence_segment.hpp>

#include <seqan3/core/debug_stream.hpp>

namespace stellar
{

template <typename TAlphabet>
template <typename TSwiftPattern>
StellarQuerySegment<TAlphabet>
StellarQuerySegment<TAlphabet>::fromPatternMatch(TSwiftPattern const & swiftPattern)
{
    size_t const queryID = swiftPattern.curSeqNo;
    std::cout << "queryID" << queryID << '\n';
    std::cout << "host of pattern" << std::addressof(host(swiftPattern)) << '\n';
    auto const & queryInfix = seqan2::getSequenceByNo(queryID, seqan2::indexText(seqan2::needle(swiftPattern)));
    static_assert(std::is_same_v<decltype(queryInfix), TInfixSegment const &>);
    auto const & underlyingQuery = host(queryInfix);
    std::cout << "queryInfix in fromPatternMatch" << queryInfix << '\n';
    std::cout << "from PatternMatch query address:" << std::addressof(queryInfix) << '\n';
    std::cout << "from PatternMatch host address:" << std::addressof(underlyingQuery) << '\n';
    static_assert(std::is_same_v<decltype(underlyingQuery), seqan2::String<TAlphabet> const &>);
    auto const queryInfixInfix = seqan2::infix(swiftPattern, queryInfix);

    return {underlyingQuery, seqan2::beginPosition(queryInfixInfix), seqan2::endPosition(queryInfixInfix)};
}

} // namespace stellar

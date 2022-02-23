
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
    using TSequence = seqan::String<TAlphabet>;

    size_t const queryID = swiftPattern.curSeqNo;
    TSequence const & query = seqan::getSequenceByNo(queryID, seqan::indexText(seqan::needle(swiftPattern)));
    TInfixSegment const queryInfix = seqan::infix(swiftPattern, query);
    return {query, seqan::beginPosition(queryInfix), seqan::endPosition(queryInfix)};
}

} // namespace stellar

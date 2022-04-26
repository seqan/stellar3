
#pragma once

#include <seqan/seeds.h>

namespace stellar
{
using namespace seqan;

///////////////////////////////////////////////////////////////////////////////
// Computes the banded alignment matrix and additionally a string with the best
//   alignment end point for each alignment length.
template <typename TTrace, typename TEnd, typename TStringSet, typename TScore, typename TDiagonal>
inline void
_align_banded_nw_best_ends(TTrace& trace,
                           String<TEnd> & bestEnds,
                           TStringSet const & str,
                           TScore const & sc,
                           TDiagonal const diagL,
                           TDiagonal const diagU)
{
    typedef typename Value<TTrace>::Type TTraceValue;
    typedef typename Value<TScore>::Type TScoreValue;
    typedef typename Value<TStringSet>::Type TString;
    typedef typename Size<TTrace>::Type TSize;

    SEQAN_ASSERT_GEQ(diagU, diagL);

    // Initialization
    TTraceValue const Diagonal = 0;
    TTraceValue const Horizontal = 1;
    TTraceValue const Vertical = 2;
    TString const& str1 = str[0];
    TString const& str2 = str[1];
    TSize const len1 = length(str1) + 1;
    TSize const len2 = length(str2) + 1;
    TSize const diagonalWidth = (TSize) (diagU - diagL + 1);
    TSize hi_diag = diagonalWidth;
    TSize lo_diag = 0;
    if (diagL > 0) lo_diag = 0;
    else lo_diag = (diagU < 0) ? hi_diag : (TSize) (1 - diagL);
    TSize const lo_row = (diagU <= 0) ? -diagU : 0;
    TSize const hi_row = [&]()
    {
        TSize const max_hi_row = len2;
        // Note: diagL might be negative
        assert((TDiagonal) len1 >= diagL);
        if (len1 - diagL < max_hi_row)
            return len1 - diagL;
        else
            return max_hi_row;
    }();
    TSize const height = hi_row - lo_row;

    typedef String<TScoreValue> TRow;
    TRow mat, len;
    resize(mat, diagonalWidth);
    resize(len, diagonalWidth);
    resize(trace, height * diagonalWidth);

    // Classical DP with affine gap costs
    typedef typename Iterator<TRow, Standard>::Type TRowIter;
    typedef typename Iterator<TTrace, Standard>::Type TTraceIter;
    TSize actualCol = 0;
    TSize actualRow = 0;
    TScoreValue verti_val = 0;
    TScoreValue hori_val = 0;
    TScoreValue hori_len = len1+len2+1;
    TSize errors;

    using TAlphabet [[maybe_unused]] = typename Value<TString>::Type;

    assert(scoreMatch(sc) == 1u);
    assert(scoreGap(sc) == scoreGapExtendHorizontal(sc, TAlphabet{}, TAlphabet{}));
    assert(scoreGap(sc) == scoreGapExtendVertical(sc, TAlphabet{}, TAlphabet{}));
    assert(scoreMismatch(sc) == scoreGap(sc));

    TScoreValue const matchScore = scoreMatch(sc);
    TScoreValue const gapScore = scoreGap(sc);

    for(TSize row = 0; row < height; ++row) {
        actualRow = row + lo_row;
        if (lo_diag > 0) --lo_diag;
        if ((TDiagonal)actualRow >= (TDiagonal)len1 - diagU) --hi_diag;
        TTraceIter traceIt = begin(trace, Standard()) + row * diagonalWidth + lo_diag;
        TRowIter matIt = begin(mat, Standard()) + lo_diag;
        TRowIter lenIt = begin(len, Standard()) + lo_diag;
        hori_val = std::numeric_limits<TScoreValue>::min();
        hori_len = len1+len2+1;
        for(TSize col = lo_diag; col<hi_diag; ++col, ++matIt, ++traceIt, ++lenIt) {
            actualCol = col + diagL + actualRow;
            if (actualCol >= len1) break;

            if ((actualRow != 0) && (actualCol != 0)) {
                TAlphabet const str1entry = sequenceEntryForScore(sc, str1, ((int) actualCol - 1));
                TAlphabet const str2entry = sequenceEntryForScore(sc, str2, ((int) actualRow - 1));

                // Get the new maximum for mat
                *matIt += score(sc, str1entry, str2entry);
                *traceIt = Diagonal;
                ++(*lenIt);

                verti_val =
                    (col < diagonalWidth - 1) ?
                    *(matIt+1) + gapScore :
                    std::numeric_limits<TScoreValue>::min();

                if (verti_val > *matIt)
                {
                    *matIt = verti_val;
                    *traceIt = Vertical;
                    *lenIt = *(lenIt+1) + 1;
                }

                hori_val =
                    (col > 0) ?
                    hori_val + gapScore :
                    std::numeric_limits<TScoreValue>::min();
                if (hori_val > *matIt)
                {
                    *matIt = hori_val;
                    *traceIt = Horizontal;
                    *lenIt = hori_len + 1;
                }
                hori_val = *matIt;
                hori_len = *lenIt;
            } else {
                // Usual initialization for first row and column
                if (actualRow == 0) {
                    *matIt = actualCol * gapScore;
                    *lenIt = actualCol;
                }
                else {
                    *matIt = actualRow * gapScore;
                    *lenIt = actualRow;
                    hori_val = *matIt;
                    hori_len = actualRow;
                }
            }

            // *matIt: the alignment_score
            // *lenIt: the alignment_length (basically length of best trace path of the current cell)
            // alignment_length = |matches| + |mismatches| + |gaps|
            //
            // alignment_score
            //     = |matches| * match_score + |mismatches| * gap_score + |gaps| * gap_score
            //
            // alignment_length * match_score
            //     = |matches| * match_score + |mismatches| * match_score + |gaps| * match_score
            //
            // alignment_score - alignment_length * match_score
            //     = 0 + (|mismatches| + |gaps|)(gap_score - match_score)
            //
            // Thus
            //   (alignment_score - alignment_length * match_score) / (gapScore - matchScore)
            // = |mismatches| + |gaps| = errors
            errors = (*matIt - (*lenIt * matchScore)) / (gapScore - matchScore);
            SEQAN_ASSERT_LEQ(errors, length(bestEnds));
            if (errors == length(bestEnds)) {
                appendValue(bestEnds, TEnd(*lenIt, row, col));
            } else if (*lenIt > static_cast<TScoreValue>(value(bestEnds, errors).length))
                value(bestEnds, errors) = TEnd(*lenIt, row, col);
            //std::cerr << row << ',' << col << ':' << *matIt << std::endl;
        }
    }
    TSize newLength = length(bestEnds) - 1;
    while (newLength > 0 && bestEnds[newLength].length <= bestEnds[newLength-1].length) {
        --newLength;
    }
    resize(bestEnds, newLength + 1);
}

} // namespace stellar


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
    TTraceValue Diagonal = 0; TTraceValue Horizontal = 1; TTraceValue Vertical = 2;
    TString const& str1 = str[0];
    TString const& str2 = str[1];
    TSize len1 = length(str1) + 1;
    TSize len2 = length(str2) + 1;
    TSize diagonalWidth = (TSize) (diagU - diagL + 1);
    TSize hi_diag = diagonalWidth;
    TSize lo_diag = 0;
    if (diagL > 0) lo_diag = 0;
    else lo_diag = (diagU < 0) ? hi_diag : (TSize) (1 - diagL);
    TSize lo_row = (diagU <= 0) ? -diagU : 0;
    TSize hi_row = len2;
    if (len1 - diagL < hi_row) hi_row = len1 - diagL;
    TSize height = hi_row - lo_row;

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
                // Get the new maximum for mat
                *matIt += score(const_cast<TScore&>(sc), sequenceEntryForScore(const_cast<TScore&>(sc), str1, ((int) actualCol - 1)),
                                sequenceEntryForScore(const_cast<TScore&>(sc), str2, ((int) actualRow - 1)));
                *traceIt = Diagonal;
                ++(*lenIt);
                if ((verti_val = (col < diagonalWidth - 1) ? *(matIt+1) +
                    scoreGapExtendVertical(sc,sequenceEntryForScore(sc, str1, ((int) actualCol - 1)),
                                           sequenceEntryForScore(sc, str2, ((int) actualRow - 1))) : std::numeric_limits<TScoreValue>::min()) > *matIt)
                {
                    *matIt = verti_val;
                    *traceIt = Vertical;
                    *lenIt = *(lenIt+1) + 1;
                }
                if ((hori_val = (col > 0) ? hori_val +
                    scoreGapExtendHorizontal(sc, sequenceEntryForScore(sc, str1, ((int) actualCol - 1)),
                                             sequenceEntryForScore(sc, str2, ((int) actualRow - 1))) : std::numeric_limits<TScoreValue>::min()) > *matIt)
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
                    *matIt = actualCol * scoreGapExtendHorizontal(sc, sequenceEntryForScore(sc, str1, ((int) actualCol - 1)),
                                                                  sequenceEntryForScore(sc, str2, -1));
                    *lenIt = actualCol;
                }
                else {
                    *matIt = actualRow * scoreGapExtendVertical(sc, sequenceEntryForScore(sc, str1, -1),
                                                                sequenceEntryForScore(sc, str2, ((int) actualRow - 1)));
                    *lenIt = actualRow;
                    hori_val = *matIt;
                    hori_len = actualRow;
                }
            }
            errors = (*matIt - (*lenIt * scoreMatch(const_cast<TScore&>(sc)))) /
                        (scoreGap(const_cast<TScore&>(sc)) - scoreMatch(const_cast<TScore&>(sc)));
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

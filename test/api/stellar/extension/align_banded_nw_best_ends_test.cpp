#include <gtest/gtest.h>

#include <stellar/stellar_extension.hpp>
#include <stellar/extension/extension_banded_trace_matrix.hpp>

using TScore = int;
using TDiagonal = int;
using TTraceBackMatrix = stellar::extension_banded_trace_matrix;
using TEndInfo = stellar::ExtensionEndPosition<size_t>;

template <typename TData>
std::vector<int> actualTraceData(TData const & data)
{
    return std::vector<int>(data.begin(), data.end());
}

void expect_same_matrix(TTraceBackMatrix & traceBackMatrix1, TTraceBackMatrix & traceBackMatrix2)
{
    auto [beginRow, endRow] = traceBackMatrix1.rowInterval();
    auto [beginRow2, endRow2] = traceBackMatrix2.rowInterval();

    ASSERT_EQ(beginRow, beginRow2);
    ASSERT_EQ(endRow, endRow2);
    ASSERT_EQ(traceBackMatrix1.dataSize(), traceBackMatrix2.dataSize());

    for (size_t row = beginRow; row < endRow; ++row)
    {
        EXPECT_EQ(
            actualTraceData(traceBackMatrix1.rowSpan(row)),
            actualTraceData(traceBackMatrix2.rowSpan(row))
        ) << "Row: " << row;
    }
}

TEST(align_banded_nw_best_ends, identicalAlignment)
{
    seqan::String<seqan::Dna> sequence1 = "TGTC";
    seqan::String<seqan::Dna> sequence2 = "GCCT";

    seqan::StringSet<seqan::String<seqan::Dna>> sequences;
    appendValue(sequences, sequence1);
    appendValue(sequences, sequence2);

    TDiagonal const diagL = -503;
    TDiagonal const diagU = 503;
    size_t const rowCount = length(sequence2) + 1;
    size_t const columnCount = length(sequence1) + 1;
    TTraceBackMatrix traceBackMatrix1(rowCount, columnCount, diagL, diagU);
    TTraceBackMatrix traceBackMatrix2(rowCount, columnCount, diagL, diagU);
    seqan::String<TEndInfo> possibleEnds1, possibleEnds2;

    seqan::Score<TScore> scoringScheme1(1, -1, -1);
    _align_banded_nw_best_ends (
        traceBackMatrix1.underlyingTraceMatrix(),
        possibleEnds1,
        sequences,
        scoringScheme1,
        diagL,
        diagU
    );

    seqan::Score<TScore> scoringScheme2(1, -1, -1);
    _align_banded_nw_best_ends (
        traceBackMatrix2.underlyingTraceMatrix(),
        possibleEnds2,
        sequences,
        scoringScheme2,
        diagL,
        diagU
    );

    expect_same_matrix(traceBackMatrix1, traceBackMatrix2);
}

TEST(align_banded_nw_best_ends, sameTraceMatrixButDifferentParameters)
{
    seqan::String<seqan::Dna> sequence1 =
        "TGTCAGCGGATGGGATGGTTCGTAATGGTAGTGGATTGCCCTTTGGAGTTAAATTACTTCTGCTCTGACACAATAGATCGGTTTAATGACCATTCTCCGCTCACGCTAGA"
        "GTGAGCCAGAGTGTGTTTGGTGCAGTTCATACGGTCCATTGCGTGAACTGTGCGGGCTAGTAGAGGTTTAACACGGACATGGCCTTGATGGGCGCACTTAAACAGTCCGA"
        "GTAATTGGTTGGATTAGCCAGAAATAGCATCAACTAGAGGCCCTATGTGGTGACTGACCTCGCTGACTTACATCTTGGCGTTGTCTGTCATAAAGCTCGCGTTCGCCAGC"
        "TGTCTCTAAGCGTATAATCGCACACCGCTTAAGGGGGTAGAACTCAGTCACTGTTTTTTTAGTGC";
    seqan::String<seqan::Dna> sequence2 =
        "ATCTTAATTCATGTGCACGCTACTTACAGGCTAGTGGCACGGCTGGCTGGCCTGTGAGATCTGTCGACAGACTGACTGTAGGGTGTATCGGCGTTGTTTGAACGGTTGCG"
        "AACGGGTCGCCGTGCCAAAGCATTACGGTTGTTCGTGGGGGATTATCGCGCTGGGTCCCGATATCGTTCTGGAGCGAGCTAAAAATATTACTTGGGACAAAGGTCTGAAG"
        "ATAGTAAATATGAGAAGTTCATCTATTAAGGCTCACACTACTGGTAAGTGGGGTGGGTCATGCGATAATCCGAGGTGTCATCATCGAGATGAAATATATAACCGCAAAGG"
        "GCCTCCCGATTTCCCAATAATCTGCCTTAGAGC";

    seqan::StringSet<seqan::String<seqan::Dna>> sequences;
    appendValue(sequences, sequence1);
    appendValue(sequences, sequence2);

    TDiagonal const diagL = -503;
    TDiagonal const diagU = 503;

    // diagonals are bigger than sequences
    EXPECT_GE(diagU, length(sequence1)); // sequence 1 is not bounded by band
    EXPECT_GE(-diagL, length(sequence2)); // sequence 2 is not bounded by band

    size_t const rowCount = length(sequence2) + 1;
    size_t const columnCount = length(sequence1) + 1;

    TTraceBackMatrix traceBackMatrix1(rowCount, columnCount, diagL, diagU);
    TTraceBackMatrix traceBackMatrix2(rowCount, columnCount, diagL, diagU);
    seqan::String<TEndInfo> possibleEnds1, possibleEnds2;

    seqan::Score<TScore> scoringScheme1(1, -99998, -99998);
    _align_banded_nw_best_ends (
        traceBackMatrix1.underlyingTraceMatrix(),
        possibleEnds1,
        sequences,
        scoringScheme1,
        diagL,
        diagU
    );

    seqan::Score<TScore> scoringScheme2(1, -11, -11);
    _align_banded_nw_best_ends (
        traceBackMatrix2.underlyingTraceMatrix(),
        possibleEnds2,
        sequences,
        scoringScheme2,
        diagL,
        diagU
    );

    expect_same_matrix(traceBackMatrix1, traceBackMatrix2);
}

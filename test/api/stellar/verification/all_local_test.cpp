#include <gtest/gtest.h>

#include <stellar/test/error_rate.hpp>

#include <stellar/verification/all_local.hpp>

#include <stellar/stellar_database_segment.hpp>
#include <stellar/stellar_query_segment.hpp>

TEST(AllLocal, empty)
{
    using TAlphabet = seqan2::Dna5;
    seqan2::String<TAlphabet> database{};
    seqan2::String<TAlphabet> query{};
    stellar::stellar_verification_time verification_runtime{};

    stellar::StellarDatabaseSegment<TAlphabet> databaseSegment{database, 0u, 0u};
    stellar::StellarQuerySegment<TAlphabet> querySegment{query, 0u, 0u};

    double epsilon = 0.01; // From stellar_index_test.cpp StellarIndexTest::validSeedWithExactMatches
    int minLength = 9; // From stellar_index_test.cpp StellarIndexTest::validSeedWithExactMatches
    unsigned delta = 16u; // From stellar_index_test.cpp StellarIndexTest::validSeedWithExactMatches
    double xDrop = 5.0; // default from app

    EXPECT_EQ(stellar::StellarOptions{}.xDrop, xDrop); // default xDrop is 5

    stellar::verifySwiftHit(
        databaseSegment.asFinderSegment(), //infH
        querySegment.asPatternSegment(), //infV
        epsilon,
        minLength,
        xDrop,
        delta,
        [](auto && alignment) -> bool
        {
            std::cout << "alignment: " << alignment << std::endl;
            ADD_FAILURE() << "Empty sequences should not have any alignment." << std::endl;
            return true;
        },
        verification_runtime,
        stellar::AllLocal{}
    );
}

TEST(AllLocal, validSeedWithExactMatches)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCGCAGAACACG" "A" "CTCCTCTACCTTACCGCGT"};
    // original
    TSequence query{"CTCGAGGGTTTACGCATATCTGG" "TAACCGCAGAACACG" "A" "AGAGCCTGAGA"};
    stellar::stellar_verification_time verification_runtime{};

    stellar::StellarDatabaseSegment<TAlphabet> databaseSegment{database, 20u, 20u + 16u};
    stellar::StellarQuerySegment<TAlphabet> querySegment{query, 14u, 14u + 6u + 3u + 16u + 11u};

    double epsilon = 0.125; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    int minLength = 9; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    unsigned delta = 16u; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    double xDrop = 5.0; // default from app

    EXPECT_EQ(stellar::StellarOptions{}.xDrop, xDrop); // default xDrop is 5

    using TAlignment = seqan2::Align<TSequence const, seqan2::ArrayGaps>;
    std::vector<TAlignment> alignments;

    stellar::verifySwiftHit(
        databaseSegment.asFinderSegment(), //infH
        querySegment.asPatternSegment(), //infV
        epsilon,
        minLength,
        xDrop,
        delta,
        [&](auto & alignment) -> bool
        {
            static_assert(std::is_same<decltype(alignment), TAlignment &>::value, "");
            alignments.push_back(alignment);
            return true;
        },
        verification_runtime,
        stellar::AllLocal{}
    );

    EXPECT_EQ(databaseSegment.asInfixSegment(), "TAACCGCAGAACACGA");
    EXPECT_EQ(querySegment.asInfixSegment(), "CATATC" "TGG" "TAACCGCAGAACACGA" "AGAGCCTGAGA");

    ASSERT_EQ(alignments.size(), 1u);
    EXPECT_EQ(row(alignments[0], 0), "GACTAACCGCAGAACACGA");
    //                                |  ||||||||||||||||
    EXPECT_EQ(row(alignments[0], 1), "G--TAACCGCAGAACACGA");

    stellar::test::error_rate_t errors = stellar::test::error_rate(alignments[0]);
    EXPECT_EQ(errors.alignment_length, 19u);
    EXPECT_EQ(errors.error_columns, 2u);
    EXPECT_DOUBLE_EQ(errors.error_rate(), 2.0 / 19.0);
}

TEST(AllLocal, oneErrorInsertion)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCGC"/* */"AGAACACG" "A" "CTCCTCTACCTTACCGCGT"};
    // 1 error, insert in query sequence
    TSequence query{"CTCGAGGGTTTACGCATATCTGG" "TAACCGC" "A" "AGAACACG" "A" "AGAGCCTGAGA"};
    stellar::stellar_verification_time verification_runtime{};

    stellar::StellarDatabaseSegment<TAlphabet> databaseSegment{database, 20u, 20u + 16u};
    stellar::StellarQuerySegment<TAlphabet> querySegment{query, 14u, 14u + 9u + 17u + 11u};

    double epsilon = 0.125; // 9 length * 0.125 error-rate = 1 error
    int minLength = 9; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    unsigned delta = 16u; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    double xDrop = 5.0; // default from app

    EXPECT_EQ(stellar::StellarOptions{}.xDrop, xDrop); // default xDrop is 5

    using TAlignment = seqan2::Align<TSequence const, seqan2::ArrayGaps>;
    std::vector<TAlignment> alignments;

    stellar::verifySwiftHit(
        databaseSegment.asFinderSegment(), //infH
        querySegment.asPatternSegment(), //infV
        epsilon,
        minLength,
        xDrop,
        delta,
        [&](auto & alignment) -> bool
        {
            static_assert(std::is_same<decltype(alignment), TAlignment &>::value, "");
            alignments.push_back(alignment);
            return true;
        },
        verification_runtime,
        stellar::AllLocal{}
    );

    EXPECT_EQ(databaseSegment.asInfixSegment(), "TAACCGC" "AGAACACGA");
    EXPECT_EQ(querySegment.asInfixSegment(), "CATATCTGG" "TAACCGC" "A" "AGAACACGA" "AGAGCCTGAGA");

    ASSERT_EQ(alignments.size(), 2u);
    EXPECT_EQ(row(alignments[0], 0), "TAACCGC-AGAACACGAC");
    //                                ||||||| |||||||||
    EXPECT_EQ(row(alignments[0], 1), "TAACCGCAAGAACACGA-");

    EXPECT_EQ(row(alignments[1], 0), "TAACCGCA-GAACACGAC");
    //                                ||||||| |||||||||
    EXPECT_EQ(row(alignments[1], 1), "TAACCGCAAGAACACGA-");

    {
        stellar::test::error_rate_t errors = stellar::test::error_rate(alignments[0]);
        EXPECT_EQ(errors.alignment_length, 18u);
        EXPECT_EQ(errors.error_columns, 2u);
        EXPECT_DOUBLE_EQ(errors.error_rate(), 2.0 / 18.0);
    }

    {
        stellar::test::error_rate_t errors = stellar::test::error_rate(alignments[1]);
        EXPECT_EQ(errors.alignment_length, 18u);
        EXPECT_EQ(errors.error_columns, 2u);
        EXPECT_DOUBLE_EQ(errors.error_rate(), 2.0 / 18.0);
    }
}

TEST(AllLocal, oneErrorDeletion)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCG" "C" "AGAACACG" "A" "CTCCTCTACCTTACCGCGT"};
    // 1 error, delete in query sequence
    TSequence query{"CTCGAGGGTTTACGCATATCTGG" "TAACCG"/*C*/"AGAACACG" "A" "AGAGCCTGAGA"};
    stellar::stellar_verification_time verification_runtime{};

    stellar::StellarDatabaseSegment<TAlphabet> databaseSegment{database, 27u, 27u + 9u};
    stellar::StellarQuerySegment<TAlphabet> querySegment{query, 21u, 21u + 6u + 2u + 9u + 11u};

    double epsilon = 0.125; // 9 length * 0.125 error-rate = 1 error
    int minLength = 9; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    unsigned delta = 16u; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    double xDrop = 5.0; // default from app

    EXPECT_EQ(stellar::StellarOptions{}.xDrop, xDrop); // default xDrop is 5

    using TAlignment = seqan2::Align<TSequence const, seqan2::ArrayGaps>;
    std::vector<TAlignment> alignments;

    stellar::verifySwiftHit(
        databaseSegment.asFinderSegment(), //infH
        querySegment.asPatternSegment(), //infV
        epsilon,
        minLength,
        xDrop,
        delta,
        [&](auto & alignment) -> bool
        {
            static_assert(std::is_same<decltype(alignment), TAlignment &>::value, "");
            alignments.push_back(alignment);
            return true;
        },
        verification_runtime,
        stellar::AllLocal{}
    );

    EXPECT_EQ(databaseSegment.asInfixSegment(), "AGAACACGA");
    EXPECT_EQ(querySegment.asInfixSegment(), "GGTAAC" "CG" "AGAACACGA" "AGAGCCTGAGA");

    ASSERT_EQ(alignments.size(), 1u);
    EXPECT_EQ(row(alignments[0], 0), "TAACCGCAGAACACGAC");
    //                                |||||| |||||||||
    EXPECT_EQ(row(alignments[0], 1), "TAACCG-AGAACACGA-");

    stellar::test::error_rate_t errors = stellar::test::error_rate(alignments[0]);
    EXPECT_EQ(errors.alignment_length, 17u);
    EXPECT_EQ(errors.error_columns, 2u);
    EXPECT_DOUBLE_EQ(errors.error_rate(), 2.0 / 17.0);
}

TEST(AllLocal, oneErrorSubstitution)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCG" "C" "AGAACACG" "A" "CTCCTCTACCTTACCGCGT"};
    // 1 error, substitution in query sequence
    TSequence query{"CTCGAGGGTTTACGCATATCTGG" "TAACCG" "G" "AGAACACG" "A" "AGAGCCTGAGA"};
    stellar::stellar_verification_time verification_runtime{};

    stellar::StellarDatabaseSegment<TAlphabet> databaseSegment{database, 27u, 27u + 9u};
    stellar::StellarQuerySegment<TAlphabet> querySegment{query, 21u, 21u + 6u + 3u + 9u + 11u};

    double epsilon = 0.125; // 9 length * 0.125 error-rate = 1 error
    int minLength = 9; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    unsigned delta = 16u; // From stellar_index_test.cpp StellarIndexTest::validSeedWithOneErrorMatches
    double xDrop = 5.0; // default from app

    EXPECT_EQ(stellar::StellarOptions{}.xDrop, xDrop); // default xDrop is 5

    using TAlignment = seqan2::Align<TSequence const, seqan2::ArrayGaps>;
    std::vector<TAlignment> alignments;

    stellar::verifySwiftHit(
        databaseSegment.asFinderSegment(), //infH
        querySegment.asPatternSegment(), //infV
        epsilon,
        minLength,
        xDrop,
        delta,
        [&](auto & alignment) -> bool
        {
            static_assert(std::is_same<decltype(alignment), TAlignment &>::value, "");
            alignments.push_back(alignment);
            return true;
        },
        verification_runtime,
        stellar::AllLocal{}
    );

    EXPECT_EQ(databaseSegment.asInfixSegment(), "AGAACACGA");
    EXPECT_EQ(querySegment.asInfixSegment(), "GGTAAC" "CGG" "AGAACACGA" "AGAGCCTGAGA");

    ASSERT_EQ(alignments.size(), 1u);
    EXPECT_EQ(row(alignments[0], 0), "TAACCGCAGAACACGAC");
    //                                |||||| |||||||||
    EXPECT_EQ(row(alignments[0], 1), "TAACCGGAGAACACGA-");

    stellar::test::error_rate_t errors = stellar::test::error_rate(alignments[0]);
    EXPECT_EQ(errors.alignment_length, 17u);
    EXPECT_EQ(errors.error_columns, 2u);
    EXPECT_DOUBLE_EQ(errors.error_rate(), 2.0 / 17.0);
}

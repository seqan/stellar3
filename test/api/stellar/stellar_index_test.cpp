#include <gtest/gtest.h>

#include <stellar/stellar.hpp>

struct StringSetOwnerFactory
{
    template <typename TAlphabet>
    static decltype(auto)
    dependentQueries(seqan2::StringSet<seqan2::String<TAlphabet>, seqan2::Owner<> > const & sequences)
    {
        return sequences; // pass as is
    }

    template <typename TAlphabet>
    static decltype(auto) underlyingSequence(seqan2::String<TAlphabet> const & sequence)
    {
        return sequence; // pass as is
    }
};

struct StringSetDependentFactory
{
    template <typename TAlphabet>
    static seqan2::StringSet<seqan2::String<TAlphabet>, seqan2::Dependent<>>
    dependentQueries(seqan2::StringSet<seqan2::String<TAlphabet>> const & sequences)
    {
        return sequences; // convert
    }

    template <typename TAlphabet>
    static decltype(auto) underlyingSequence(seqan2::String<TAlphabet> const & sequence)
    {
        return sequence; // pass as is
    }
};

struct InfixSegmentVectorFactory
{
    template <typename TAlphabet>
    using TInfixSequence = seqan2::Segment<seqan2::String<TAlphabet> const, seqan2::InfixSegment>;

    template <typename TAlphabet>
    static auto
    dependentQueries(seqan2::StringSet<seqan2::String<TAlphabet>> const & sequences)
    {
        std::vector<TInfixSequence<TAlphabet>> infixSequences{};
        for (auto const & sequence : sequences)
            infixSequences.emplace_back(sequence, 0u, seqan2::length(sequence));

        return infixSequences; // convert
    }

    template <typename TAlphabet>
    static decltype(auto) underlyingSequence(TInfixSequence<TAlphabet> const & sequence)
    {
        return host(sequence); // pass as is
    }
};

template <typename TFactory>
struct StellarIndexTest : public ::testing::Test {
public:
    TFactory factory{};

    template <typename TSequenceSegment, typename TSequence>
    static void expect_segment(
        TSequenceSegment const & sequenceSegment,
        TSequence const & expectedUnderlyingSequence,
        size_t const expectedBeginPosition,
        size_t const expectedEndPosition,
        std::string const expectedSubsequence)
    {
        using TInterval = std::pair<size_t, size_t>;

        TSequenceSegment expectedSequenceSegment{
            expectedUnderlyingSequence,
            expectedBeginPosition,
            expectedEndPosition
        };

        TSequence const & actualSequence = sequenceSegment.underlyingSequence();

        // expect that the infix segment points to the right underlying sequence
        EXPECT_EQ(std::addressof(actualSequence), std::addressof(expectedUnderlyingSequence));

        // check whether underlying sequence has the same content (it should if prior test passes)
        EXPECT_EQ(actualSequence, expectedUnderlyingSequence);

        // check whether sequence corresponds to expected sub-sequence
        EXPECT_EQ(sequenceSegment.asInfixSegment(), expectedSubsequence);

        // check whether segment interval is the same as expected
        EXPECT_EQ(sequenceSegment.interval(), TInterval(expectedBeginPosition, expectedEndPosition));

        // last check if is the same segment
        EXPECT_EQ(sequenceSegment, expectedSequenceSegment);
    }
};

using ConstructFactories = ::testing::Types<StringSetOwnerFactory, StringSetDependentFactory, InfixSegmentVectorFactory>;
TYPED_TEST_SUITE(StellarIndexTest, ConstructFactories);

template <typename TAlphabet>
struct results
{
    using TDatabaseSegment = stellar::StellarDatabaseSegment<TAlphabet>;
    using TQuerySegment = stellar::StellarQuerySegment<TAlphabet>;
    using TAlignment = std::pair<TDatabaseSegment, TQuerySegment>;

    // Note: verifySwiftHit's delta is the sum of pattern_delta + pattern_overlap
    std::vector<unsigned> pattern_deltas{};
    std::vector<unsigned> pattern_overlaps{};
    std::vector<unsigned> verify_deltas{};
    std::vector<TAlignment> alignments{};
    stellar::StellarComputeStatistics statistics{};
};

// Hijack SwiftHitVerifier for testing.
namespace stellar
{
struct TVerifyPassthroughSeed{};

template <>
struct SwiftHitVerifier<TVerifyPassthroughSeed>
{
    EPSMatchOptions eps_match_options;
    VerifierOptions verifier_options;

    template <typename TAlphabet, typename TDelta, typename TOnAlignmentResultFn>
    void verify(StellarDatabaseSegment<TAlphabet> const & databaseSegment,
                StellarQuerySegment<TAlphabet> const & querySegment,
                TDelta const delta,
                TOnAlignmentResultFn && onAlignmentResult,
                [[maybe_unused]] stellar_verification_time & verification_runtime)
    {
        onAlignmentResult(databaseSegment, querySegment, delta);
    }
};

} // namespace stellar

template <typename TAlphabet, typename TypeParam>
results<TAlphabet> stellar_kernel_swift_seeds(
    StellarIndexTest<TypeParam> const & self,
    seqan2::String<TAlphabet> const & database,
    seqan2::StringSet<seqan2::String<TAlphabet>> const & queries,
    stellar::StellarOptions const & options)
{
    using TSequence = seqan2::String<TAlphabet>;
    using TInfixSequence = seqan2::Segment<TSequence const, seqan2::InfixSegment>;

    decltype(auto) dependentQueries = self.factory.dependentQueries(queries);

    if constexpr (std::is_same<TypeParam, StringSetOwnerFactory>::value)
    {
        EXPECT_TRUE((std::is_same<seqan2::StringSet<TSequence> const &, decltype(dependentQueries)>::value));
    } else if constexpr (std::is_same<TypeParam, StringSetDependentFactory>::value)
    {
        EXPECT_TRUE((std::is_same<seqan2::StringSet<TSequence, seqan2::Dependent<>>, decltype(dependentQueries)>::value));
    } else if constexpr (std::is_same<TypeParam, InfixSegmentVectorFactory>::value)
    {
        EXPECT_TRUE((std::is_same<std::vector<TInfixSequence>, decltype(dependentQueries)>::value));
    } else
    {
        ADD_FAILURE() << "Unknown Factory";
    }

    // make sure that dependentQueries are reference to the actual queries (have same pointer address)
    EXPECT_GT(length(dependentQueries), 0u);
    EXPECT_EQ(std::addressof(self.factory.underlyingSequence(dependentQueries[0])), std::addressof(queries[0]));
    for (size_t i = 0; i < length(dependentQueries); ++i)
    {
        EXPECT_EQ(std::addressof(self.factory.underlyingSequence(dependentQueries[i])), std::addressof(queries[i]));
    }

    stellar::StellarIndex<TAlphabet> index{dependentQueries, options};
    index.construct();

    stellar::StellarSwiftPattern<TAlphabet> swiftPattern = index.createSwiftPattern();
    stellar::StellarSwiftFinder<TAlphabet> swiftFinder
    {
        seqan2::infix(database, 0u, seqan2::length(database)),
        options.minRepeatLength,
        options.maxRepeatPeriod
    };

    static_assert(std::is_same<decltype(swiftPattern.bucketParams[0].delta), unsigned>::value, "");
    static_assert(std::is_same<decltype(swiftPattern.bucketParams[0].overlap), unsigned>::value, "");

    EXPECT_EQ(
        std::addressof(stellar::StellarIndex<TAlphabet>::qgramIndexFromPattern(swiftPattern)),
        std::addressof(index.qgramIndex));

    EXPECT_EQ(
        std::addressof(stellar::StellarIndex<TAlphabet>::sequencesFromQGramIndex(index.qgramIndex)),
        std::addressof(index.dependentQueries));

    EXPECT_EQ(
        std::addressof(stellar::StellarIndex<TAlphabet>::sequencesFromPattern(swiftPattern)),
        std::addressof(index.dependentQueries));

    using TResults = results<TAlphabet>;
    using TDatabaseSegment = typename TResults::TDatabaseSegment;
    using TQuerySegment = typename TResults::TQuerySegment;

    TResults results{};

    stellar::SwiftHitVerifier<stellar::TVerifyPassthroughSeed> verifier
    {
        STELLAR_DESIGNATED_INITIALIZER(.eps_match_options =, options),
        STELLAR_DESIGNATED_INITIALIZER(.verifier_options =, options),
    };
    auto isPatternDisabled = [](...){ return false; };

    stellar::stellar_kernel_runtime kernel_runtime{};

    results.statistics = stellar::_stellarKernel(
        swiftFinder,
        swiftPattern,
        verifier,
        isPatternDisabled,
        [&](TDatabaseSegment const & databaseSegment, TQuerySegment const & querySegment, unsigned const delta)
    {
        // should always be the same number
        results.pattern_deltas.emplace_back(swiftPattern.bucketParams[0].delta);
        // should always be the same number
        results.pattern_overlaps.emplace_back(swiftPattern.bucketParams[0].overlap);
        // should always be the same number = pattern_deltas + pattern_overlaps
        results.verify_deltas.emplace_back(delta);
        // different for each invocation
        results.alignments.emplace_back(databaseSegment, querySegment);
    }, kernel_runtime);

    // sort alignments by query and not database
    std::sort(results.alignments.begin(), results.alignments.end(), [&](auto const & v1, auto const & v2)
    {
        return v1.second < v2.second;
    });

    return results;
}

TYPED_TEST(StellarIndexTest, validSeedWithExactMatches)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCGCAGAACACG" "ACTCCTCTACCTTACCGCGT"};

    seqan2::StringSet<TSequence> queries{};
    // original
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "C"/**/ "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, insert in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "C" "A" "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, delete in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG"/*C   */ "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, substitution in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "G"/**/ "AGAACACG" "A" "AGAGCCTGAGA");
    // another sequence
    seqan2::appendValue(queries, "CCGACTACCCACTTACTTATTAGCCG" "TAACCGCAGAACACG" "GACCAATCAGGCCC");
    // another smaller sequence
    seqan2::appendValue(queries, "TAGCCAGTTTA" "GCAGAACAC" "CAAGA");

    size_t const kmerSize = 7u;
    stellar::StellarOptions options{};
    options.qGram = kmerSize;
    options.epsilon = {1, 100};
    options.minLength = 9u;

    using TResults = results<TAlphabet>;
    TResults results = stellar_kernel_swift_seeds(*this, database, queries, options);

    EXPECT_EQ(results.statistics.numSwiftHits, 6u);
    EXPECT_EQ(results.statistics.totalLength, 16u + 9u + 9u + 9u + 15u + 9u);
    EXPECT_EQ(results.statistics.maxLength, 16u);
    EXPECT_EQ(results.verify_deltas, (std::vector<unsigned>{16u, 16u, 16u, 16u, 16u, 16u}));
    EXPECT_EQ(results.pattern_deltas, (std::vector<unsigned>{16u, 16u, 16u, 16u, 16u, 16u}));
    EXPECT_EQ(results.pattern_overlaps, (std::vector<unsigned>{0u, 0u, 0u, 0u, 0u, 0u}));

    ASSERT_EQ(results.alignments.size(), 6u);

    // original
    this->expect_segment(results.alignments[0].first, database, 20u, 20u + 16u,
                         /*  */"TAACCGCAGAACACGA");
    this->expect_segment(results.alignments[0].second, queries[0], 20u, 20u + 3u + 16u + 11u,
                         "TGG" "TAACCGCAGAACACGA" "AGAGCCTGAGA");

    // 1 error, insert in query sequence
    this->expect_segment(results.alignments[1].first, database, 27u, 27u + 9u,
                         /*   */"AGAACACGA");
    this->expect_segment(results.alignments[1].second, queries[1], 27u, 27u + 4u + 9u + 11u,
                         "CGCA" "AGAACACGA" "AGAGCCTGAGA");

    // 1 error, delete in query sequence
    this->expect_segment(results.alignments[2].first, database, 27u, 27u + 9u,
                         /* */"AGAACACGA");
    this->expect_segment(results.alignments[2].second, queries[2], 27u, 27u + 2u + 9u + 11u,
                         "CG" "AGAACACGA" "AGAGCCTGAGA");

    // 1 error, substitution in query sequence
    this->expect_segment(results.alignments[3].first, database, 27u, 27u + 9u,
                         /*  */"AGAACACGA");
    this->expect_segment(results.alignments[3].second, queries[3], 27u, 27u + 3u + 9u + 11u,
                         "CGG" "AGAACACGA" "AGAGCCTGAGA");

    // another sequence
    this->expect_segment(results.alignments[4].first, database, 20u, 20u + 15u,
                         /*     */"TAACCGCAGAACACG");
    this->expect_segment(results.alignments[4].second, queries[4], 20u, 20u + 6u + 15u + 10u,
                         "TAGCCG" "TAACCGCAGAACACG" "GACCAATCAG");

    // another smaller sequence
    this->expect_segment(results.alignments[5].first, database, 25u, 25u + 9u,
                         /* */"GCAGAACAC");
    this->expect_segment(results.alignments[5].second, queries[5], 9u, 9u + 2u + 9u + 5u,
                         "TA" "GCAGAACAC" "CAAGA");
}

TYPED_TEST(StellarIndexTest, validSeedWithOneErrorMatches)
{
    using TAlphabet = seqan2::Dna5;
    using TSequence = seqan2::String<TAlphabet>;
    TSequence database{"CAACGGACTGCTGTCTAGAC" "TAACCGCAGAACACG" "ACTCCTCTACCTTACCGCGT"};

    seqan2::StringSet<TSequence> queries{};
    // original
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "C"/**/ "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, insert in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "C" "A" "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, delete in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG"/*C   */ "AGAACACG" "A" "AGAGCCTGAGA");
    // 1 error, substitution in query sequence
    seqan2::appendValue(queries, "CTCGAGGGTTTACGCATATCTGG" "TAACCG" "G"/**/ "AGAACACG" "A" "AGAGCCTGAGA");
    // another sequence
    seqan2::appendValue(queries, "CCGACTACCCACTTACTTATTAGCCG" "TAACCGCAGAACACG" "GACCAATCAGGCCC");
    // another smaller sequence
    seqan2::appendValue(queries, "TAGCCAGTTTA" "GCAGAACAC" "CAAGA");

    size_t const kmerSize = 7u;
    stellar::StellarOptions options{};
    options.qGram = kmerSize;
    options.epsilon = {1, 8}; // 9 length * 0.125 error-rate = 1 error
    options.minLength = 9u;

    using TResults = results<TAlphabet>;
    TResults results = stellar_kernel_swift_seeds(*this, database, queries, options);

    EXPECT_EQ(results.statistics.numSwiftHits, 6u);
    EXPECT_EQ(results.statistics.totalLength, 16u + 16u + 9u + 9u + 15u + 9u);
    EXPECT_EQ(results.statistics.maxLength, 16u);
    EXPECT_EQ(results.verify_deltas, (std::vector<unsigned>{22u, 22u, 22u, 22u, 22u, 22u}));
    EXPECT_EQ(results.pattern_deltas, (std::vector<unsigned>{16u, 16u, 16u, 16u, 16u, 16u}));
    EXPECT_EQ(results.pattern_overlaps, (std::vector<unsigned>{6u, 6u, 6u, 6u, 6u, 6u}));

    ASSERT_EQ(results.alignments.size(), 6u);
    // original (same result as with 0 errors, but 6 chars earlier)
    this->expect_segment(results.alignments[0].first, database, 20u, 20u + 16u,
                         /*           */"TAACCGCAGAACACGA");
    this->expect_segment(results.alignments[0].second, queries[0], 14u, 14u + 6u + 3u + 16u + 11u,
                         "CATATC" "TGG" "TAACCGCAGAACACGA" "AGAGCCTGAGA");

    // 1 error, insert in query sequence (complete new result compared with 0 errors)
    this->expect_segment(results.alignments[1].first, database, 20u, 20u + 16u,
                         /*        */"TAACCGC"/* */"AGAACACGA");
    this->expect_segment(results.alignments[1].second, queries[1], 14u, 14u + 9u + 17u + 11u,
                         "CATATCTGG" "TAACCGC" "A" "AGAACACGA" "AGAGCCTGAGA");

    // 1 error, delete in query sequence (same result as with 0 errors, but 6 chars earlier)
    this->expect_segment(results.alignments[2].first, database, 27u, 27u + 9u,
                         /*          */"AGAACACGA");
    this->expect_segment(results.alignments[2].second, queries[2], 21u, 21u + 6u + 2u + 9u + 11u,
                         "GGTAAC" "CG" "AGAACACGA" "AGAGCCTGAGA");

    // 1 error, substitution in query sequence (same result as with 0 errors, but 6 chars earlier)
    this->expect_segment(results.alignments[3].first, database, 27u, 27u + 9u,
                         /*          */"AGAACACGA");
    this->expect_segment(results.alignments[3].second, queries[3], 21u, 21u + 6u + 3u + 9u + 11u,
                        "GGTAAC" "CGG" "AGAACACGA" "AGAGCCTGAGA");

    // another sequence (same result as with 0 errors, but 6 chars earlier)
    this->expect_segment(results.alignments[4].first, database, 20u, 20u + 15u,
                         /*              */"TAACCGCAGAACACG");
    this->expect_segment(results.alignments[4].second, queries[4], 14u, 14u + 6u + 6u + 15u + 10u,
                         "ACTTAT" "TAGCCG" "TAACCGCAGAACACG" "GACCAATCAG");

    // another smaller sequence (same result as with 0 errors, but 6 chars earlier)
    this->expect_segment(results.alignments[5].first, database, 25u, 25u + 9u,
                         /*          */"GCAGAACAC");
    this->expect_segment(results.alignments[5].second, queries[5], 3u, 3u + 6u + 2u + 9u + 5u,
                         "CCAGTT" "TA" "GCAGAACAC" "CAAGA");
}

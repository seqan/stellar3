#include <gtest/gtest.h>

#include <stellar/stellar.hpp>

using TAlphabet = seqan2::Dna5;
using TDatabaseSegment = stellar::StellarDatabaseSegment<TAlphabet>;
using TStorage = std::vector<TDatabaseSegment>;

////////////////////////////////////////////////
//  struct StellarDatabaseSegment
////////////////////////////////////////////////
TEST(StellarDatabaseSegment, underlyingDatabase)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    seqan2::String<TAlphabet> const & resultDatabase = database;
    EXPECT_EQ(resultDatabase, database);
    EXPECT_EQ(std::addressof(resultDatabase), std::addressof(database));
}

TEST(StellarDatabaseSegment, beginPosition)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    EXPECT_EQ(segment.beginPosition(), 3u);
}

TEST(StellarDatabaseSegment, endPosition)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    EXPECT_EQ(segment.endPosition(), length(database) - 3);
}

TEST(StellarDatabaseSegment, interval)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    EXPECT_EQ(segment.interval(), (std::pair<size_t, size_t>{3u, length(database) - 3}));
}

TEST(StellarDatabaseSegment, size)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    EXPECT_EQ(length(segment.asInfixSegment()), 6u);
    EXPECT_EQ(segment.size(), 6u);
}

TEST(StellarDatabaseSegment, asInfixSegment)
{
    seqan2::String<TAlphabet> database{"ACG""TACGTA""CGT"};
    stellar::StellarDatabaseSegment<TAlphabet> segment{database, 3u, length(database) - 3};

    EXPECT_EQ(segment.asInfixSegment(), "TACGTA");
    EXPECT_EQ(segment.asInfixSegment(), seqan2::infix(database, 3u, length(database) - 3));
}

TEST(StellarDatabaseSegment, fromFinderMatch)
{
    using TFinderSegment = seqan2::Segment<seqan2::Segment<seqan2::String<TAlphabet> const, seqan2::InfixSegment>, seqan2::InfixSegment>;

    seqan2::String<TAlphabet> database{};
    resize(database, 1'000'000u); // 1Mb
    std::generate(begin(database), end(database), [i = 0u]() mutable
    {
        TAlphabet dna_table[] = {'A', 'C', 'G', 'T'};
        uint8_t rank = (i++) % sizeof(dna_table);
        return dna_table[rank];
    });

    {
        // ensure that database is generated correctly
        stellar::StellarDatabaseSegment<TAlphabet> segment{database, 0u, 10u};
        EXPECT_EQ(segment.asInfixSegment(), "ACGTACGTAC");
    }

    {
        auto const databaseInfixSequence = "ACGTACGTACGTACGTACGTACGTACGTACGTACGT";
        auto const finderMatch = seqan2::infix(database, 111'948u, 111'984u);
        stellar::StellarDatabaseSegment<TAlphabet> segment
            = stellar::StellarDatabaseSegment<TAlphabet>::fromFinderMatch(finderMatch);
        EXPECT_EQ(segment.asInfixSegment(), databaseInfixSequence);

        TFinderSegment finderSegment = segment.asFinderSegment();

        EXPECT_EQ(seqan2::beginPosition(finderSegment), 111'948u);
        EXPECT_EQ(seqan2::endPosition(finderSegment), 111'984u);
        EXPECT_EQ(seqan2::infix(segment.underlyingDatabase(),
                               seqan2::beginPosition(finderSegment),
                               seqan2::endPosition(finderSegment)),
                  databaseInfixSequence);

        EXPECT_EQ(seqan2::beginPosition(host(finderSegment)), 0u);
        EXPECT_EQ(seqan2::endPosition(host(finderSegment)), 1'000'000u);
        EXPECT_EQ(std::addressof(host(host(finderSegment))), std::addressof(database));
    }

    {
        auto const databaseInfixSequence = "TACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTA";
        auto const finderMatch = seqan2::infix(database, 230'711u, 230'781u);
        stellar::StellarDatabaseSegment<TAlphabet> segment
            = stellar::StellarDatabaseSegment<TAlphabet>::fromFinderMatch(finderMatch);
        EXPECT_EQ(segment.asInfixSegment(), databaseInfixSequence);

        TFinderSegment finderSegment = segment.asFinderSegment();

        EXPECT_EQ(seqan2::beginPosition(finderSegment), 230'711u);
        EXPECT_EQ(seqan2::endPosition(finderSegment), 230'781u);
        EXPECT_EQ(seqan2::infix(segment.underlyingDatabase(),
                               seqan2::beginPosition(finderSegment),
                               seqan2::endPosition(finderSegment)),
                  databaseInfixSequence);

        EXPECT_EQ(seqan2::beginPosition(host(finderSegment)), 0u);
        EXPECT_EQ(seqan2::endPosition(host(finderSegment)), 1'000'000u);
        EXPECT_EQ(std::addressof(host(host(finderSegment))), std::addressof(database));
    }
}

TEST(StellarDatabaseSegment, comparison)
{
    std::vector<seqan2::String<TAlphabet>> sequences{"ACGTACGTACGT", "TGCATGCATGCATGCA"};

    stellar::StellarDatabaseSegment<TAlphabet> segment1, segment2;

    enum struct ordering {less = -1, equal = 0, greater = +1};

    auto const make_segments = [&](ordering sequenceOrder, ordering beginPositionOrder, ordering endPositionOrder)
    {
        auto assert_order = [](
            [[maybe_unused]] size_t value1,
            [[maybe_unused]] size_t value2,
            [[maybe_unused]] ordering order)
        {
            [[maybe_unused]] int diff = static_cast<int>(value1) - static_cast<int>(value2);
            [[maybe_unused]] ordering valueOrder = (diff < 0) ? ordering::less : ((diff == 0) ? ordering::equal : ordering::greater);
            assert(valueOrder == order);
        };
        size_t const sequence1_id = (sequenceOrder <= ordering::equal) ? 0u : 1u;
        size_t const sequence2_id = (ordering::equal <= sequenceOrder) ? 0u : 1u;
        assert_order(sequence1_id, sequence2_id, sequenceOrder);

        size_t const begin1 = (beginPositionOrder <= ordering::equal) ? 2u : 4u;
        size_t const begin2 = (ordering::equal <= beginPositionOrder) ? 2u : 4u;
        assert_order(begin1, begin2, beginPositionOrder);

        size_t const end1 = std::max(begin1, begin2) + ((endPositionOrder <= ordering::equal) ? 2u : 4u);
        size_t const end2 = std::max(begin1, begin2) + ((ordering::equal <= endPositionOrder) ? 2u : 4u);
        assert_order(end1, end2, endPositionOrder);

        using segment_t = stellar::StellarDatabaseSegment<TAlphabet>;
        return std::pair<segment_t, segment_t>{
            {sequences[sequence1_id], begin1, end1},
            {sequences[sequence2_id], begin2, end2}};
    };

    std::vector<std::tuple<ordering, ordering, ordering, ordering>> ordering;
    ordering.emplace_back(ordering::equal, ordering::equal, ordering::equal, ordering::equal);
    ordering.emplace_back(ordering::equal, ordering::equal, ordering::less, ordering::less);
    ordering.emplace_back(ordering::equal, ordering::equal, ordering::greater, ordering::greater);
    ordering.emplace_back(ordering::equal, ordering::less, ordering::equal, ordering::less);
    ordering.emplace_back(ordering::equal, ordering::less, ordering::less, ordering::less);
    ordering.emplace_back(ordering::equal, ordering::less, ordering::greater, ordering::less);
    ordering.emplace_back(ordering::equal, ordering::greater, ordering::equal, ordering::greater);
    ordering.emplace_back(ordering::equal, ordering::greater, ordering::less, ordering::greater);
    ordering.emplace_back(ordering::equal, ordering::greater, ordering::greater, ordering::greater);

    ordering.emplace_back(ordering::less, ordering::equal, ordering::equal, ordering::less);
    ordering.emplace_back(ordering::less, ordering::equal, ordering::less, ordering::less);
    ordering.emplace_back(ordering::less, ordering::equal, ordering::greater, ordering::less);
    ordering.emplace_back(ordering::less, ordering::less, ordering::equal, ordering::less);
    ordering.emplace_back(ordering::less, ordering::less, ordering::less, ordering::less);
    ordering.emplace_back(ordering::less, ordering::less, ordering::greater, ordering::less);
    ordering.emplace_back(ordering::less, ordering::greater, ordering::equal, ordering::less);
    ordering.emplace_back(ordering::less, ordering::greater, ordering::less, ordering::less);
    ordering.emplace_back(ordering::less, ordering::greater, ordering::greater, ordering::less);

    ordering.emplace_back(ordering::greater, ordering::equal, ordering::equal, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::equal, ordering::less, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::equal, ordering::greater, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::less, ordering::equal, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::less, ordering::less, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::less, ordering::greater, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::greater, ordering::equal, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::greater, ordering::less, ordering::greater);
    ordering.emplace_back(ordering::greater, ordering::greater, ordering::greater, ordering::greater);

    for (auto [sequenceOrder, beginPositionOrder, endPositionOrder, resultOrder] : ordering)
    {
        std::tie(segment1, segment2) = make_segments(sequenceOrder, beginPositionOrder, endPositionOrder);
        switch (resultOrder)
        {
            case ordering::equal:
            EXPECT_FALSE(segment1 < segment2);
            EXPECT_TRUE(segment1 <= segment2);
            EXPECT_TRUE(segment1 == segment2);
            EXPECT_FALSE(segment1 != segment2);
            EXPECT_FALSE(segment1 > segment2);
            EXPECT_TRUE(segment1 >= segment2);
            break;
            case ordering::less:
            EXPECT_TRUE(segment1 < segment2);
            EXPECT_TRUE(segment1 <= segment2);
            EXPECT_FALSE(segment1 == segment2);
            EXPECT_TRUE(segment1 != segment2);
            EXPECT_FALSE(segment1 > segment2);
            EXPECT_FALSE(segment1 >= segment2);
            break;
            case ordering::greater:
            EXPECT_FALSE(segment1 < segment2);
            EXPECT_FALSE(segment1 <= segment2);
            EXPECT_FALSE(segment1 == segment2);
            EXPECT_TRUE(segment1 != segment2);
            EXPECT_TRUE(segment1 > segment2);
            EXPECT_TRUE(segment1 >= segment2);
            break;
        }
    }
}

////////////////////////////////////////////////
// TStorage _getDatabaseSegments()
////////////////////////////////////////////////
seqan2::StringSet<seqan2::String<TAlphabet>> getDatabases()
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"AACAGTC"});
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"ACGTCG"});
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"CCGCTGC"});
    return databases;
}

stellar::StellarOptions getPrefilteringOptions(std::vector<size_t> const seqInt, unsigned const segBegin, unsigned const segEnd)
{
    stellar::StellarOptions options;
    options.minLength = 2;
    options.binSequences = seqInt;
    options.segmentBegin = segBegin;
    options.segmentEnd = segEnd;
    return options;
}

TEST(getDatabaseSegment, all_sequences)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases = getDatabases();
    auto options = getPrefilteringOptions(std::vector<size_t>{1}, 0u, 2u);

    TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);

    EXPECT_EQ(length(databaseSegments), 3u);
    EXPECT_EQ(databaseSegments[0].asInfixSegment(), (seqan2::String<TAlphabet>) {"AACAGTC"});
    EXPECT_EQ(databaseSegments[1].asInfixSegment(), (seqan2::String<TAlphabet>) {"ACGTCG"});
    EXPECT_EQ(databaseSegments[2].asInfixSegment(), (seqan2::String<TAlphabet>) {"CCGCTGC"});
}

TEST(getDatabaseSegment, last_two)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases = getDatabases();
    auto options = getPrefilteringOptions(std::vector<size_t>{1, 2}, 0u, 2u);
    options.prefilteredSearch = true;

    TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);

    // each database sequence is made into a segment if options.searchSegment == false
    // a subset of sequences may be extracted with _importSequencesOfInterest if options.prefilteredSearch == true
    EXPECT_EQ(length(databaseSegments), 3u);
    EXPECT_EQ(databaseSegments[0].asInfixSegment(), (seqan2::String<TAlphabet>) {"AACAGTC"});
    EXPECT_EQ(databaseSegments[1].asInfixSegment(), (seqan2::String<TAlphabet>) {"ACGTCG"});
    EXPECT_EQ(databaseSegments[2].asInfixSegment(), (seqan2::String<TAlphabet>) {"CCGCTGC"});
}

TEST(getDatabaseSegment, from_begin)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"ACGTCG"});

    auto options = getPrefilteringOptions(std::vector<size_t>{1}, 0u, 2u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);

    EXPECT_EQ(length(databaseSegments), 1u);
    EXPECT_EQ(length(databaseSegments[0].asInfixSegment()), 2u);
    EXPECT_EQ(databaseSegments[0].size(), 2u);
    EXPECT_EQ(databaseSegments[0].asInfixSegment(), (seqan2::String<TAlphabet>) {"AC"});
}

TEST(getDatabaseSegment, whole_sequence)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"AACAGTC"});
    auto options = getPrefilteringOptions(std::vector<size_t>{0}, 0u, 7u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);

    EXPECT_EQ(length(databaseSegments), 1u);
    EXPECT_EQ(length(databaseSegments[0].asInfixSegment()), 7u);
    EXPECT_EQ(databaseSegments[0].size(), 7u);
    EXPECT_EQ(databaseSegments[0].asInfixSegment(), (seqan2::String<TAlphabet>) {"AACAGTC"});
}

/*
TEST(getDatabaseSegment, seq_out_of_range)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases = getDatabases();
    auto options = getPrefilteringOptions(3u, 0u, 2u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    try {
        TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Sequence of interest out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

*/

TEST(getDatabaseSegment, index_out_of_range)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"ACGTCG"});
    auto options = getPrefilteringOptions(std::vector<size_t>{1}, 0u, 8u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    /*!TODO: update gtest to 1.11?
    EXPECT_THAT(
        [] () {TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);},
        ThrowsMessageHasSubstr<std::runtime_error>("Incorrect segment definition")
    );
    */

    try {
        TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Segment end out of range"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(getDatabaseSegment, too_short)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"ACGTCG"});
    auto options = getPrefilteringOptions(std::vector<size_t>{1}, 0u, 1u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    try {
        TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Segment shorter than minimum match length"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(getDatabaseSegment, incorrect_indices)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::appendValue(databases, (seqan2::String<TAlphabet>) {"ACGTCG"});
    auto options = getPrefilteringOptions(std::vector<size_t>{1}, 2u, 0u);
    options.prefilteredSearch = true;
    options.searchSegment = true;

    try {
        TStorage databaseSegments = stellar::_getDatabaseSegments<TAlphabet, TStorage>(databases, options);
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("Incorrect segment definition"));
    }
    catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

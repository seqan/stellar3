#include <gtest/gtest.h>

#include <functional>
#include <stellar/prefilter/prefilter_agent.hpp>
#include <stellar/prefilter/prefilter_agents.hpp>

using TAlphabet = seqan::Dna5;
using TPrefilterAgent = stellar::prefilter_agent<TAlphabet>;

struct MyPrefilterAgent1 : TPrefilterAgent
{
    using TBase = TPrefilterAgent;
    using TBase::TDatabaseSegment;
    using TBase::TQueryFilter;
    using TBase::TPrefilterCallback;

    virtual void prefilter(TPrefilterCallback callback) override
    {
        using TQuerySegment = seqan::Segment<seqan::String<TAlphabet> const, seqan::InfixSegment>;

        std::vector<TDatabaseSegment> database_segments
        {
            TDatabaseSegment{database_sequence, 0, 5}, // AAACC
            TDatabaseSegment{database_sequence, 3, 11} // CCCGGGTT
        };
        std::span<TDatabaseSegment> database_segments_span{database_segments};

        TQuerySegment query_segment{query_sequence, 1, 7}; // TCCCGG
        std::span<TQuerySegment> query_segments_span{&query_segment, 1};

        stellar::StellarIndex<TAlphabet> index{query_segments_span, stellar::IndexOptions{}};
        stellar::StellarSwiftPattern<TAlphabet> pattern = index.createSwiftPattern();

        callback(database_segments_span, pattern);
    }

    seqan::String<TAlphabet> database_sequence{"AAACCCGGGTT"};
    seqan::String<TAlphabet> query_sequence{"TTCCCGGGAAA"};
};

struct MyPrefilterAgent2 : TPrefilterAgent
{
    using TBase = TPrefilterAgent;
    using TBase::TDatabaseSegment;
    using TBase::TQueryFilter;
    using TBase::TPrefilterCallback;

    virtual void prefilter(TPrefilterCallback callback) override
    {
        using TQuerySegment = seqan::Segment<seqan::String<TAlphabet> const, seqan::InfixSegment>;

        std::vector<TDatabaseSegment> database_segments
        {
            TDatabaseSegment{database_sequence, 0, 5}, // TTCCC
            TDatabaseSegment{database_sequence, 3, 11} // CCGGGAAA
        };
        std::span<TDatabaseSegment> database_segments_span{database_segments};

        TQuerySegment query_segment{query_sequence, 1, 7}; // AACCCG
        std::span<TQuerySegment> query_segments_span{&query_segment, 1};

        stellar::StellarIndex<TAlphabet> index{query_segments_span, stellar::IndexOptions{}};
        stellar::StellarSwiftPattern<TAlphabet> pattern = index.createSwiftPattern();

        callback(database_segments_span, pattern);
    }

    seqan::String<TAlphabet> database_sequence{"TTCCCGGGAAA"};
    seqan::String<TAlphabet> query_sequence{"AAACCCGGGTT"};
};

TEST(prefilter_agents_test, movable)
{
    std::vector<MyPrefilterAgent1> agents_original(10u);
    stellar::prefilter_agents<TAlphabet> agents1{agents_original};

    stellar::prefilter_agents<TAlphabet> agents2 = std::move(agents1);
}

TEST(prefilter_agents_test, reserve)
{
    stellar::prefilter_agents<TAlphabet> agents{};
    agents.reserve(100);
}

TEST(prefilter_agents_test, emplace_back)
{
    using TDatabaseSegment = typename stellar::prefilter_agent<TAlphabet>::TDatabaseSegment;
    using TQueryFilter = typename stellar::prefilter_agent<TAlphabet>::TQueryFilter;

    stellar::prefilter_agents<TAlphabet> agents{};

    agents.emplace_back<MyPrefilterAgent1>();
    agents.emplace_back<MyPrefilterAgent2>();

    stellar::prefilter_agent<TAlphabet> & agent1 = agents.begin()[0];
    stellar::prefilter_agent<TAlphabet> & agent2 = agents.begin()[1];

    {
        size_t callback_called = 0;
        agent1.prefilter([&](std::span<TDatabaseSegment const> database_segments, TQueryFilter & query_filter)
        {
            EXPECT_EQ(database_segments.size(), 2);
            EXPECT_EQ(database_segments[0].asInfixSegment(), "AAACC");
            EXPECT_EQ(database_segments[1].asInfixSegment(), "CCCGGGTT");

            stellar::StellarQGramStringSet<TAlphabet> const & query_segments
                = stellar::StellarIndex<TAlphabet>::sequencesFromPattern(query_filter);

            EXPECT_EQ(seqan::length(query_segments), 1);
            EXPECT_EQ(query_segments[0], "TCCCGG");

            ++callback_called;
        });
        EXPECT_EQ(callback_called, 1);
    }

    {
        size_t callback_called = 0;
        agent2.prefilter([&](std::span<TDatabaseSegment const> database_segments, TQueryFilter & query_filter)
        {
            EXPECT_EQ(database_segments.size(), 2);
            EXPECT_EQ(database_segments[0].asInfixSegment(), "TTCCC");
            EXPECT_EQ(database_segments[1].asInfixSegment(), "CCGGGAAA");

            stellar::StellarQGramStringSet<TAlphabet> const & query_segments
                = stellar::StellarIndex<TAlphabet>::sequencesFromPattern(query_filter);

            EXPECT_EQ(seqan::length(query_segments), 1);
            EXPECT_EQ(query_segments[0], "AACCCG");

            ++callback_called;
        });
        EXPECT_EQ(callback_called, 1);
    }
}

TEST(prefilter_agents_iterator_test, size)
{
    std::vector<MyPrefilterAgent1> agents_original(10u);
    stellar::prefilter_agents<TAlphabet> agents{agents_original};

    auto iterator = agents.begin();
    auto sentinel = agents.end();

    EXPECT_EQ(sentinel - iterator, 10);
    EXPECT_EQ(iterator - sentinel, -10);
}

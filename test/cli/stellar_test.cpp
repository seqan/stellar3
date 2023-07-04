#include <fstream>
#include <ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include "cli_test.hpp"

TEST_P(search_subset, stellar_search_subset)
{
    auto const [seq] = GetParam();

    std::string segments;
    for (auto id : seq)
    {
        segments += " --sequenceOfInterest ";
        segments += std::to_string(id);
    }
    segments += " > subset_out.stdout";

    cli_test_result const result = execute_app("stellar",
                                               data("multi_seq_ref.fasta"),
                                               data("query_e0.05.fasta"),
                                               "-o subset_out.gff",
                                               "--epsilon 0.05",
                                               "--minLength 50",
                                               "-k 15",
                                               "--verbose",
                                               segments);

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.err, std::string{"\n\n"}); // not sure where the whitespace comes from

    std::string const expected_matches = string_from_file(out_path(seq, "gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("subset_out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);

    std::string expected_output = string_from_file(out_path(seq, "stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("subset_out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(subset_suite,
                         search_subset,
                         testing::Combine(testing::Values(std::vector<size_t>{1}, std::vector<size_t>{0, 1}, std::vector<size_t>{1, 2}, std::vector<size_t>{0, 1, 2})),
                         [] (testing::TestParamInfo<search_subset::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)[0]) + "_" +
                                                std::to_string(std::get<0>(info.param).size());
                             return name;
                         });


TEST_P(search_segment, stellar_search_segment)
{
    auto const [seq, seg_range] = GetParam();

    cli_test_result const result = execute_app("stellar",
                                                data("ref.fasta"),
                                                data("query_e0.05.fasta"),
                                                "-o segment_out.gff",
                                                "--referenceLength 1024",
                                                "--sequenceOfInterest ", std::to_string(seq[0]),
                                                "--segmentBegin ", std::to_string(seg_range.first),
                                                "--segmentEnd ", std::to_string(seg_range.second),
                                                "--epsilon 0.05",
                                                "--minLength 50",
                                                "-k 15",
                                                "--verbose",
                                                "> segment_out.stdout");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.err, std::string{"\n\n"});

    std::string const expected_matches = string_from_file(out_path(seq[0], seg_range.first, seg_range.second, "gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("segment_out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);

    std::string expected_output = string_from_file(out_path(seq[0], seg_range.first, seg_range.second, "stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("segment_out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(segment_suite,
                         search_segment,
                         testing::Combine(testing::Values(std::vector<size_t>{0}), testing::Values(std::make_pair(0, 400), std::make_pair(500, 643), std::make_pair(600, 763))),
                         [] (testing::TestParamInfo<search_segment::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)[0]) + "_" +
                                                std::to_string(std::get<1>(info.param).first) + "_" +
                                                std::to_string(std::get<1>(info.param).second);
                             return name;
                         });

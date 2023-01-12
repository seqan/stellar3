#include <fstream>
#include <ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors

#include "cli_test.hpp"

TEST_P(stellar_search, prefiltered)
{
    auto const [seq, seg_range] = GetParam();

    cli_test_result const result = execute_app("stellar",
                                                data("ref.fasta"),
                                                data("query_e0.05.fasta"),
                                                "-o out.gff",
                                                "--sequenceOfInterest ", std::to_string(seq),
                                                "--segmentBegin ", std::to_string(seg_range.first),
                                                "--segmentEnd ", std::to_string(seg_range.second),
                                                "--epsilon 0.05",
                                                "--minLength 50",
                                                "--verbose",
                                                "--suppress-runtime-printing",
                                                "> out.stdout");
    EXPECT_EQ(result.exit_code, 0);
    //EXPECT_EQ(result.err, std::string{});

    std::string const expected_matches = string_from_file(out_path(seq, seg_range.first, seg_range.second, "gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);

    std::string expected_output = string_from_file(out_path(seq, seg_range.first, seg_range.second, "stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(stellar_suite,
                         stellar_search,
                         testing::Combine(testing::Values(0), testing::Values(std::make_pair(0, 400), std::make_pair(200, 600), std::make_pair(400, 700))),
                         [] (testing::TestParamInfo<stellar_search::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)) + "_" +
                                                std::to_string(std::get<1>(info.param).first) + "_" +
                                                std::to_string(std::get<1>(info.param).second);
                             return name;
                         });

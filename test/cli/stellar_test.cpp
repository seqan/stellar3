#include <fstream>
#include <ranges>     // range comparisons
#include <string>                // strings
#include <vector>                // vectors
#include <cmath>

#include "cli_test.hpp"

TEST_P(search_subset, stellar_search_subset)
{
    auto const [seq, er] = GetParam();
    std::stringstream err_stream;
    err_stream << std::setprecision(2) << er;
    std::string err_str = err_stream.str();


    std::string segments;
    for (auto id : seq)
    {
        segments += " --sequenceOfInterest ";
        segments += std::to_string(id);
    }
    segments += " > subset_out.stdout";

    cli_test_result const result = execute_app("stellar",
                                               data("multi_seq_ref.fasta"),
                                               data("query_e" + err_str + ".fasta"),
                                               "-o subset_out.gff",
                                               "--epsilon ", err_str,
                                               "--minLength 50",
                                               "--verbose",
                                               segments);

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.err, std::string{"\n\n"}); // not sure where the whitespace comes from

    std::string const expected_matches = string_from_file(out_path("subset", seq, err_str, "gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("subset_out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);

    std::string expected_output = string_from_file(out_path("subset", seq, err_str, "stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("subset_out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(subset_suite,
                         search_subset,
                         testing::Combine(testing::Values(std::vector<size_t>{1}, std::vector<size_t>{0, 1}, std::vector<size_t>{1, 2}, std::vector<size_t>{0, 1, 2}), testing::Values(0.0f, 0.05f)),
                         [] (testing::TestParamInfo<search_subset::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)[0]) + "_" +
                                                std::to_string(std::get<0>(info.param).size()) + "_" + 
                                                std::to_string((int) std::round(std::get<1>(info.param) * 100));
                             return name;
                         });


TEST_P(search_segment, stellar_search_segment)
{
    auto const [seq, seg_range, er] = GetParam();
    std::stringstream err_stream;
    err_stream << std::setprecision(2) << er;
    std::string err_str = err_stream.str();
    

    cli_test_result const result = execute_app("stellar",
                                                data("ref.fasta"),
                                                data("query_e" + err_str + ".fasta"),
                                                "-o segment_out.gff",
                                                "--referenceLength 2000",
                                                "--sequenceOfInterest ", std::to_string(seq[0]),
                                                "--segmentBegin ", std::to_string(seg_range.first),
                                                "--segmentEnd ", std::to_string(seg_range.second),
                                                "--epsilon ", err_str,
                                                "--minLength 50",
                                                "--verbose",
                                                "> segment_out.stdout");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.err, std::string{"\n\n"});

    std::string const expected_matches = string_from_file(out_path("segment", seq[0], seg_range.first, seg_range.second, err_str, "gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("segment_out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);
    std::string expected_output = string_from_file(out_path("segment", seq[0], seg_range.first, seg_range.second, err_str, "stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("segment_out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(segment_suite,
                         search_segment,
                         testing::Combine(testing::Values(std::vector<size_t>{0}), testing::Values(std::make_pair(0, 400), std::make_pair(500, 800)), testing::Values(0.0f, 0.05f)),
                         [] (testing::TestParamInfo<search_segment::ParamType> const & info)
                         {
                             std::string name = std::to_string(std::get<0>(info.param)[0]) + "_" +
                                                std::to_string(std::get<1>(info.param).first) + "_" +
                                                std::to_string(std::get<1>(info.param).second) + "_" + 
                                                std::to_string((int) std::round(std::get<2>(info.param) * 100));
                             return name;
                         });

/*
    For a 0.0 error rate the seed extension is done assuming a 0.001 error rate. 
    This test case checks that a match with a 0.001 error rate is not found by Stellar when searching with 0 errors.  
*/
TEST_P(search_small_error, edge_case)
{
    auto const er = GetParam();
    std::stringstream err_stream;
    err_stream << std::setprecision(4) << er;
    std::string err_str = err_stream.str();

    cli_test_result const result = execute_app("stellar",
                                               data("ref.fasta"),
                                               data("query_e0.001.fasta"),
                                               "-o small_er_out.gff",
                                               "--epsilon ", err_str,
                                               "--minLength 1000",
                                               "--verbose",
                                               "> small_er_out.stdout");

    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.err, std::string{"\n\n"}); // not sure where the whitespace comes from

    std::string const expected_matches = string_from_file(cli_test::data("er_edge_case_e" + err_str + ".gff"), std::ios::binary);
    std::string const actual_matches = string_from_file("small_er_out.gff", std::ios::binary);

    EXPECT_EQ(expected_matches, actual_matches);

    std::string expected_output = string_from_file(cli_test::data("er_edge_case_e" + err_str + ".stdout"), std::ios::binary);
    size_t pos = expected_output.find("User specified");    // do not compare paths
    expected_output = expected_output.substr(pos);

    std::string actual_output = string_from_file("small_er_out.stdout", std::ios::binary);
    pos = actual_output.find("User specified");
    actual_output = actual_output.substr(pos);

    EXPECT_EQ(expected_output, actual_output);
}

INSTANTIATE_TEST_SUITE_P(edge_case_suite,
                         search_small_error,
                         testing::Values(0.0f, 0.0009f, 0.001f),
                         [] (testing::TestParamInfo<search_small_error::ParamType> const & info)
                         {
                             std::string name =  "er_edge_case_" + std::to_string((int) std::round(info.param * 10000));
                             return name;
                         });

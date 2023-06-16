#include <cstring>

#include <gtest/gtest.h>

#include <stellar/io/import_sequence.hpp>

using TAlphabet = seqan2::Dna5;
std::string databaseFile = std::string{DATADIR} + "/multi_seq_ref.fasta";

TEST(import_sequences, all_sequences)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::_importAllSequences(databaseFile.c_str(), "database", databases, databaseIDs, refLen, std::cout, std::cerr);

    EXPECT_EQ(length(databases), 3u);
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"GATGACTCAGTCTTGTTGATTAGGCACCTCGGTATGTGGGCATTAGGCACATTGCTCTGTTTCTTGAAGT"
                                                        "CTGGTATGAGCACAAGGTGTGTCCCAACCGACAACTGGTTCAATGGCCACCCCGACCTAAAGGACGTTTC"
                                                        "CGCTTCGATTGTGAGGACTTTAACAGGTTTTCGTCTGGCAGAATCATGTCCTTACTGCTTATCCAGGTCT"
                                                        "TTTAAAGTTCGTTTCAGACTTTGGTCCCAAGCGACTCCAAACGGAGAACCGTACGAATATCTACCCAGTC"
                                                        "CTACGAAAAAATGACTCAGTGGGCACAGGGGGTTTACAGTGTGATCAGTTAGCGTCCGGGAGAAAATATA"
                                                        "ATCTGTGTAGCGAGGATTCTATATCAGACCGATAAATCTAATCGGCCCGGTATAAATTCTCGTACCGAAC"
                                                        "AACTTCTAACTTGGACGGTTGTACACTTACGGGAACTAGCAAACTCTAAGATAATAGAAGGCCTGAATCC"
                                                        "GGCGTTACACCCATAGGGGAATAACGCCGAAATTGGTGGTTCTCGATAATTGCCAGTAATGCATCACAGC"});
    EXPECT_EQ(databaseIDs[0], "1");

    EXPECT_EQ(databases[1], (seqan2::String<TAlphabet>) {"ATCTGCCTGGGTGGGGAATTGGGACAACCCTTGGGTTATAGACGTGCTCGTCAAAGGACAAGAGGAAATA"
                                                        "CCCATCTGGTCATCGGGGATCCGATGGCATCGCCAGGTATTACGCCCCTCCATGAGAACAAAACAGCTCG"
                                                        "GATAACGGTCAAACCGGCAGATGGTTAATGATCATGAGAATCCTTTGCTACGGTTAAAATACCCTGTAAG"
                                                        "GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"
                                                        "TGACGGTTAATTCGAACAAATTTAGATGATTATTCCGTATTAGA"});
    EXPECT_EQ(databaseIDs[1], "2");

    EXPECT_EQ(databases[2], (seqan2::String<TAlphabet>) {"GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"});
    EXPECT_EQ(databaseIDs[2], "3");

    EXPECT_EQ(refLen, 560 + 464 + 210);
}

TEST(import_sequence_of_interest, first)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::_importSequencesOfInterest(databaseFile.c_str(), std::vector<size_t>{0}, databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 1u);
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"GATGACTCAGTCTTGTTGATTAGGCACCTCGGTATGTGGGCATTAGGCACATTGCTCTGTTTCTTGAAGT"
                                                        "CTGGTATGAGCACAAGGTGTGTCCCAACCGACAACTGGTTCAATGGCCACCCCGACCTAAAGGACGTTTC"
                                                        "CGCTTCGATTGTGAGGACTTTAACAGGTTTTCGTCTGGCAGAATCATGTCCTTACTGCTTATCCAGGTCT"
                                                        "TTTAAAGTTCGTTTCAGACTTTGGTCCCAAGCGACTCCAAACGGAGAACCGTACGAATATCTACCCAGTC"
                                                        "CTACGAAAAAATGACTCAGTGGGCACAGGGGGTTTACAGTGTGATCAGTTAGCGTCCGGGAGAAAATATA"
                                                        "ATCTGTGTAGCGAGGATTCTATATCAGACCGATAAATCTAATCGGCCCGGTATAAATTCTCGTACCGAAC"
                                                        "AACTTCTAACTTGGACGGTTGTACACTTACGGGAACTAGCAAACTCTAAGATAATAGAAGGCCTGAATCC"
                                                        "GGCGTTACACCCATAGGGGAATAACGCCGAAATTGGTGGTTCTCGATAATTGCCAGTAATGCATCACAGC"});
    EXPECT_EQ(databaseIDs[0], "1");
    EXPECT_EQ(refLen, 560 + 464 + 210); // need the size of the underlying reference to calculate e-values consistently
}

TEST(import_sequence_of_interest, last_two)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::_importSequencesOfInterest(databaseFile.c_str(), std::vector<size_t>{1, 2}, databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 2u);
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"ATCTGCCTGGGTGGGGAATTGGGACAACCCTTGGGTTATAGACGTGCTCGTCAAAGGACAAGAGGAAATA"
                                                        "CCCATCTGGTCATCGGGGATCCGATGGCATCGCCAGGTATTACGCCCCTCCATGAGAACAAAACAGCTCG"
                                                        "GATAACGGTCAAACCGGCAGATGGTTAATGATCATGAGAATCCTTTGCTACGGTTAAAATACCCTGTAAG"
                                                        "GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"
                                                        "TGACGGTTAATTCGAACAAATTTAGATGATTATTCCGTATTAGA"});
    EXPECT_EQ(databaseIDs[0], "2");

    EXPECT_EQ(databases[1], (seqan2::String<TAlphabet>) {"GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"});
    EXPECT_EQ(databaseIDs[1], "3");
    EXPECT_EQ(refLen, 560 + 464 + 210);
}

TEST(import_sequence_of_interest, out_of_range)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    std::vector<size_t> sequenceIndex{3};

    testing::internal::CaptureStderr();
    uint64_t refLen{0};
    stellar::_importSequencesOfInterest(databaseFile.c_str(), sequenceIndex, databases, databaseIDs, refLen);
    std::string err = testing::internal::GetCapturedStderr();

    EXPECT_EQ(err,std::string("ERROR: Found 0 out of " + std::to_string(sequenceIndex.size()) + " reference sequences.\n"));
}

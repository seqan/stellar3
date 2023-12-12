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
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"TATGCACCAGAGTATGGAAGCATAAGCTCTGCATGCAAAGGTACATCAGATCCTGCGGTTGGGTGCCAAC"
                                                         "CCAAGTGTGTTCACGGGCGCTTGACAGACATCGGAGGATGGTGCACACTCACTCGACCAGCGCAAAGCAC"
                                                         "AGGATCTCACGGGCGGACATCTCTTAGGTCAGTCATCGTGGAGGAATGCTTGTACGTTCTTTTGGCTTCC"
                                                         "CCTAACACGGCGGGCGTCTCCGGTACGTATCCTGTCGGTACACCCCTTAAGCCCCTAGGCCCGAAGAACA"
                                                         "TAGCGCATTTCACGCTCTCTACGAATGACCGCAACGATCAAATGGGCGAGAACAACTAATTCCGATTCAT"
                                                         "GGGGTTTGTGGATTGTGACACAGCGCGCCCGCTACTGCGGGACGTGAGGACGCCCAATTCTGCCAAGGAT"
                                                         "TATTTAGGGTGTTTCACTAGAGTTATGCGCCGACCCCGGTTGGACCAGCTTGCATTCGAAACTGCGTTAC"
                                                         "ACAGCACCCCACCGCAATCGTATGACTCTCGCTGAAAAAGGGTGGTCAACCATTACACCTCTTATGCCTG"});
    EXPECT_EQ(databaseIDs[0], "chr1");

    EXPECT_EQ(databases[1], (seqan2::String<TAlphabet>) {"GTTGTGGGAGGCTCGGTCTTAAGCAGCGCGCGAGCTGTGATCCAGGCTACCACGGACATAGTGTATGGAA"
                                                         "AGTGATCCAGAGTAGACCCGCGGGGGCCTGACCTAACCTATATAAGTTGTATCGTGGCTATGAGGGTAGT"
                                                         "CGCCGGAGAAAACGTATGCTTACTGATTTTTAAGTCGGCGTGGCGCCGAAGCCGGATCGGTTGTAAGCTA"
                                                         "GCCGGGCCTAGGGGTTCACCGTAACGGATTAGTCAAATTAAAATCCAGCGATGACTTCCTGATAGAACTC"
                                                         "AAGTCGTGACCCCTCCGCTGCGGGCCTACATCTGTTTTCGCAGGCGTGGTTGTTTACCAGGTATGGTGCT"
                                                         "CATCTCTATTAGTCACGGGCAGCATGGTGTCACCGAACCGCGCGTCTCCTAATATCTGGTCTACCGATTT"
                                                         "AGCCCCGGCAAATAACTTTGGATTGTGGTTGGAGAGTGCCAGAACTGACGGGCGCTGCCGTGGGGCTCCT"
                                                         "AACTAAAAACGCCACGGACCTGGCTAACATTCGTTGTTGACTATAACATTTGAGGGCGCTTCGGATTCCC"
                                                         "CATACTGCCAGAGTATTATGTGGGTGGTAAACATAGATTCTATATAGTCAACGACATACACTCATTATTA"
                                                         "TGCAATTGCGG"});
    EXPECT_EQ(databaseIDs[1], "chr2");

    EXPECT_EQ(databases[2], (seqan2::String<TAlphabet>) {"CCTAGGGGTTCACCGTAACGGATTAGTCAAATTAAAATCCAGCGATGACTTCCTGATAGAACTCAAGTCG"
                                                         "TGACCCCTCCGCTGCGGGCCTACATCTGTTTTCGCAGGCGTGGTTGTTTACCAGGTATGGTGCTCATCTC"
                                                         "TATTAGTCACGGGCAGCATGGTGTCACCGAACCGCGCGTCTCCTAATATCTGGTCTACCGATTTAGCCCC"
                                                         "GGCAAATAACTTTGG"});
    EXPECT_EQ(databaseIDs[2], "chr3");

    EXPECT_EQ(refLen, 560 + 641 + 225);
}

TEST(import_sequence_of_interest, first)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::_importSequencesOfInterest(databaseFile.c_str(), std::vector<size_t>{0}, databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 1u);
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"TATGCACCAGAGTATGGAAGCATAAGCTCTGCATGCAAAGGTACATCAGATCCTGCGGTTGGGTGCCAAC"
                                                         "CCAAGTGTGTTCACGGGCGCTTGACAGACATCGGAGGATGGTGCACACTCACTCGACCAGCGCAAAGCAC"
                                                         "AGGATCTCACGGGCGGACATCTCTTAGGTCAGTCATCGTGGAGGAATGCTTGTACGTTCTTTTGGCTTCC"
                                                         "CCTAACACGGCGGGCGTCTCCGGTACGTATCCTGTCGGTACACCCCTTAAGCCCCTAGGCCCGAAGAACA"
                                                         "TAGCGCATTTCACGCTCTCTACGAATGACCGCAACGATCAAATGGGCGAGAACAACTAATTCCGATTCAT"
                                                         "GGGGTTTGTGGATTGTGACACAGCGCGCCCGCTACTGCGGGACGTGAGGACGCCCAATTCTGCCAAGGAT"
                                                         "TATTTAGGGTGTTTCACTAGAGTTATGCGCCGACCCCGGTTGGACCAGCTTGCATTCGAAACTGCGTTAC"
                                                         "ACAGCACCCCACCGCAATCGTATGACTCTCGCTGAAAAAGGGTGGTCAACCATTACACCTCTTATGCCTG"});
    EXPECT_EQ(databaseIDs[0], "chr1");
    EXPECT_EQ(refLen, 560 + 641 + 225); // need the size of the underlying reference to calculate e-values consistently
}

TEST(import_sequence_of_interest, last_two)
{
    seqan2::StringSet<seqan2::String<TAlphabet>> databases;
    seqan2::StringSet<seqan2::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::_importSequencesOfInterest(databaseFile.c_str(), std::vector<size_t>{1, 2}, databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 2u);
    EXPECT_EQ(databases[0], (seqan2::String<TAlphabet>) {"GTTGTGGGAGGCTCGGTCTTAAGCAGCGCGCGAGCTGTGATCCAGGCTACCACGGACATAGTGTATGGAA"
                                                         "AGTGATCCAGAGTAGACCCGCGGGGGCCTGACCTAACCTATATAAGTTGTATCGTGGCTATGAGGGTAGT"
                                                         "CGCCGGAGAAAACGTATGCTTACTGATTTTTAAGTCGGCGTGGCGCCGAAGCCGGATCGGTTGTAAGCTA"
                                                         "GCCGGGCCTAGGGGTTCACCGTAACGGATTAGTCAAATTAAAATCCAGCGATGACTTCCTGATAGAACTC"
                                                         "AAGTCGTGACCCCTCCGCTGCGGGCCTACATCTGTTTTCGCAGGCGTGGTTGTTTACCAGGTATGGTGCT"
                                                         "CATCTCTATTAGTCACGGGCAGCATGGTGTCACCGAACCGCGCGTCTCCTAATATCTGGTCTACCGATTT"
                                                         "AGCCCCGGCAAATAACTTTGGATTGTGGTTGGAGAGTGCCAGAACTGACGGGCGCTGCCGTGGGGCTCCT"
                                                         "AACTAAAAACGCCACGGACCTGGCTAACATTCGTTGTTGACTATAACATTTGAGGGCGCTTCGGATTCCC"
                                                         "CATACTGCCAGAGTATTATGTGGGTGGTAAACATAGATTCTATATAGTCAACGACATACACTCATTATTA"
                                                         "TGCAATTGCGG"});
    EXPECT_EQ(databaseIDs[0], "chr2");

    EXPECT_EQ(databases[1], (seqan2::String<TAlphabet>) {"CCTAGGGGTTCACCGTAACGGATTAGTCAAATTAAAATCCAGCGATGACTTCCTGATAGAACTCAAGTCG"
                                                         "TGACCCCTCCGCTGCGGGCCTACATCTGTTTTCGCAGGCGTGGTTGTTTACCAGGTATGGTGCTCATCTC"
                                                         "TATTAGTCACGGGCAGCATGGTGTCACCGAACCGCGCGTCTCCTAATATCTGGTCTACCGATTTAGCCCC"
                                                         "GGCAAATAACTTTGG"});
    EXPECT_EQ(databaseIDs[1], "chr3");
    EXPECT_EQ(refLen, 560 + 641 + 225);
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

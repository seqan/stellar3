#include <gtest/gtest.h>

#include <stellar/app/stellar.main.tpp>

using TAlphabet = seqan::Dna5;
std::string databaseFile = std::string{DATADIR} + "/multi_seq_ref.fasta";

TEST(import_sequences, all_sequences)
{
    seqan::StringSet<seqan::String<TAlphabet>> databases;
    seqan::StringSet<seqan::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::app::_importSequences(databaseFile, "database", databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 3u);
    EXPECT_EQ(databases[0], (seqan::String<TAlphabet>) {"GATGACTCAGTCTTGTTGATTAGGCACCTCGGTATGTGGGCATTAGGCACATTGCTCTGTTTCTTGAAGT"
                                                        "CTGGTATGAGCACAAGGTGTGTCCCAACCGACAACTGGTTCAATGGCCACCCCGACCTAAAGGACGTTTC"
                                                        "CGCTTCGATTGTGAGGACTTTAACAGGTTTTCGTCTGGCAGAATCATGTCCTTACTGCTTATCCAGGTCT"
                                                        "TTTAAAGTTCGTTTCAGACTTTGGTCCCAAGCGACTCCAAACGGAGAACCGTACGAATATCTACCCAGTC"
                                                        "CTACGAAAAAATGACTCAGTGGGCACAGGGGGTTTACAGTGTGATCAGTTAGCGTCCGGGAGAAAATATA"
                                                        "ATCTGTGTAGCGAGGATTCTATATCAGACCGATAAATCTAATCGGCCCGGTATAAATTCTCGTACCGAAC"
                                                        "AACTTCTAACTTGGACGGTTGTACACTTACGGGAACTAGCAAACTCTAAGATAATAGAAGGCCTGAATCC"
                                                        "GGCGTTACACCCATAGGGGAATAACGCCGAAATTGGTGGTTCTCGATAATTGCCAGTAATGCATCACAGC"});
    EXPECT_EQ(databaseIDs[0], "1");

    EXPECT_EQ(databases[1], (seqan::String<TAlphabet>) {"ATCTGCCTGGGTGGGGAATTGGGACAACCCTTGGGTTATAGACGTGCTCGTCAAAGGACAAGAGGAAATA"
                                                        "CCCATCTGGTCATCGGGGATCCGATGGCATCGCCAGGTATTACGCCCCTCCATGAGAACAAAACAGCTCG"
                                                        "GATAACGGTCAAACCGGCAGATGGTTAATGATCATGAGAATCCTTTGCTACGGTTAAAATACCCTGTAAG"
                                                        "GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"
                                                        "TGACGGTTAATTCGAACAAATTTAGATGATTATTCCGTATTAGA"});
    EXPECT_EQ(databaseIDs[1], "2");

    EXPECT_EQ(databases[2], (seqan::String<TAlphabet>) {"GACCGAATGTACCCAAATAAGGCAAGCAACGGAGTATACACCGGAGTCTCCAGTGTTCGGACTGACTCGC"
                                                        "TGGGATAAGCTGACAGACGACTTATTGCCAATTGCGTTGATGTCTAAGAAGGCGAGCTTCCCCTCTCCTA"
                                                        "GGTGCTGGTGGTGGCTCCGAACAAGGGGCTGACCTGCTCACCAGGTATTGTAGAGATCTGGCCATGGGTT"});
    EXPECT_EQ(databaseIDs[2], "3");
}

TEST(import_sequence_of_interest, first)
{
    seqan::StringSet<seqan::String<TAlphabet>> databases;
    seqan::StringSet<seqan::CharString> databaseIDs;

    uint64_t refLen{0};
    stellar::app::_importSequenceOfInterest(databaseFile, 0, databases, databaseIDs, refLen);

    EXPECT_EQ(length(databases), 1u);
    EXPECT_EQ(databases[0], (seqan::String<TAlphabet>) {"GATGACTCAGTCTTGTTGATTAGGCACCTCGGTATGTGGGCATTAGGCACATTGCTCTGTTTCTTGAAGT"
                                                        "CTGGTATGAGCACAAGGTGTGTCCCAACCGACAACTGGTTCAATGGCCACCCCGACCTAAAGGACGTTTC"
                                                        "CGCTTCGATTGTGAGGACTTTAACAGGTTTTCGTCTGGCAGAATCATGTCCTTACTGCTTATCCAGGTCT"
                                                        "TTTAAAGTTCGTTTCAGACTTTGGTCCCAAGCGACTCCAAACGGAGAACCGTACGAATATCTACCCAGTC"
                                                        "CTACGAAAAAATGACTCAGTGGGCACAGGGGGTTTACAGTGTGATCAGTTAGCGTCCGGGAGAAAATATA"
                                                        "ATCTGTGTAGCGAGGATTCTATATCAGACCGATAAATCTAATCGGCCCGGTATAAATTCTCGTACCGAAC"
                                                        "AACTTCTAACTTGGACGGTTGTACACTTACGGGAACTAGCAAACTCTAAGATAATAGAAGGCCTGAATCC"
                                                        "GGCGTTACACCCATAGGGGAATAACGCCGAAATTGGTGGTTCTCGATAATTGCCAGTAATGCATCACAGC"});
    EXPECT_EQ(databaseIDs[0], "1");
}

TEST(import_sequence_of_interest, out_of_range)
{
    seqan::StringSet<seqan::String<TAlphabet>> databases;
    seqan::StringSet<seqan::CharString> databaseIDs;

    unsigned sequenceIndex = 3;

    testing::internal::CaptureStderr();
    uint64_t refLen{0};
    stellar::app::_importSequenceOfInterest(databaseFile, sequenceIndex, databases, databaseIDs, refLen);
    std::string err = testing::internal::GetCapturedStderr();

    EXPECT_EQ(err,std::string("ERROR: Sequence index " + std::to_string(sequenceIndex) + " out of range.\n"));
}

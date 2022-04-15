#include <gtest/gtest.h>

#include <stellar/stellar_extension.hpp>

using TExtensionEndPosition = stellar::ExtensionEndPosition<size_t>;
using TPair = seqan::Pair<typename seqan::Iterator<seqan::String<TExtensionEndPosition> const>::Type>;

TEST(longestEpsMatch, minLengthNotReached1)
{
    seqan::String<TExtensionEndPosition> leftExtensions{};
    seqan::String<TExtensionEndPosition> rightExtensions{};

    appendValue(leftExtensions, TExtensionEndPosition{20, 100, 200}); // error: 0
    appendValue(rightExtensions, TExtensionEndPosition{20, 100, 200}); // error: 0

    size_t seedLength = 100;
    size_t seedError = 0; // could be up to 10 right now
    double epsilon = 0.1;
    size_t minLength = 150; // allow 15

    TPair endPositionPair
        = stellar::longestEpsMatch(leftExtensions, rightExtensions, seedLength, seedError, minLength, epsilon);

    // no match found, since minLength not reached (all length combinations are < 150)
    EXPECT_TRUE(endPositionPair == TPair(0, 0));
}

TEST(longestEpsMatch, minLengthNotReached2)
{
    seqan::String<TExtensionEndPosition> leftExtensions{};
    seqan::String<TExtensionEndPosition> rightExtensions{};

    // matrix: 30 x 20 of extension lengths
    //      0| 1| ⋯ |18|19
    //   ||==|==|=⋯=|==|==
    // 0 || 0| 1| ⋯ |18|19
    // 1 || 1| 2| ⋯ |19|20
    // ⋯ ||
    // 28||28|29| ⋯ |47|48
    // 29||29|30| ⋯ |48|49
    //
    // + 100 length of the seed => all don't match minLength

    // both combinations don't exceed length 50
    for (size_t length = 0; length < 30; ++length)
        appendValue(leftExtensions, TExtensionEndPosition{length, 100, 200}); // error: length

    for (size_t length = 0; length < 20; ++length)
        appendValue(rightExtensions, TExtensionEndPosition{length, 100, 200}); // error: length

    size_t seedLength = 100;
    size_t seedError = 0; // could be up to 10 right now
    double epsilon = 0.1;
    size_t minLength = 150; // allow 15

    TPair endPositionPair
        = stellar::longestEpsMatch(leftExtensions, rightExtensions, seedLength, seedError, minLength, epsilon);

    // no match found, since minLength not reached (all length combinations are < 150)
    EXPECT_TRUE(endPositionPair == TPair(0, 0));
}

TEST(longestEpsMatch, epsilonNotReached1)
{
    seqan::String<TExtensionEndPosition> leftExtensions{};
    seqan::String<TExtensionEndPosition> rightExtensions{};

    // matrix: 1 x 1 of extension lengths
    //     30
    //   ||==
    // 20||50
    //
    // + 100 length of the seed
    // => 150 minLength fullfilled, but
    // error-rate is 16 / 150 = 0.1066.. > 0.1

    appendValue(leftExtensions, TExtensionEndPosition{20, 100, 200}); // error: 0
    appendValue(rightExtensions, TExtensionEndPosition{30, 100, 200}); // error: 0

    size_t seedLength = 100;
    size_t seedError = 16;
    double epsilon = 0.1;
    size_t minLength = 150; // allow 15

    TPair endPositionPair
        = stellar::longestEpsMatch(leftExtensions, rightExtensions, seedLength, seedError, minLength, epsilon);

    // no match found, since minLength not reached (all length combinations are < 150)
    EXPECT_TRUE(endPositionPair == TPair(0, 0));
}

TEST(longestEpsMatch, epsilonNotReached2)
{
    seqan::String<TExtensionEndPosition> leftExtensions{};
    seqan::String<TExtensionEndPosition> rightExtensions{};

    // matrix: 5 x 3 of extension lengths
    //      10| 25| 30
    //   ||===|===|===
    // 10||x20|x35|x40
    // 20||x30|x45|*50
    // 30||x40|*55|*60
    // 39||x49|*64|*69
    // 50||*60|*75|*80
    // x - minLength not reached; * minLength reached
    // + 100 length of the seed (base)
    //
    // error-rate:
    //              10|         25|         30
    //   ||===========|===========|===========
    // 10||13/120=.108|14/135=.103|15/140=.108
    // 20||14/130=.107|15/145=.103|16/150=.107
    // 30||15/140=.107|16/155=.103|17/160=.107
    // 39||16/149=.107|17/164=.104|18/169=.107
    // 50||17/160=.106|18/175=.103|19/180=.106

    appendValue(leftExtensions, TExtensionEndPosition{10, 0, 0}); // error: 0
    appendValue(leftExtensions, TExtensionEndPosition{20, 1, 1}); // error: 1
    appendValue(leftExtensions, TExtensionEndPosition{30, 2, 2}); // error: 2
    appendValue(leftExtensions, TExtensionEndPosition{39, 3, 3}); // error: 3
    appendValue(leftExtensions, TExtensionEndPosition{50, 4, 4}); // error: 4
    appendValue(rightExtensions, TExtensionEndPosition{10, 0, 0}); // error: 0
    appendValue(rightExtensions, TExtensionEndPosition{25, 1, 1}); // error: 1
    appendValue(rightExtensions, TExtensionEndPosition{30, 2, 2}); // error: 2

    size_t seedLength = 100;
    size_t seedError = 13;
    double epsilon = 0.1;
    size_t minLength = 150; // allow 15 errors

    TPair endPositionPair
        = stellar::longestEpsMatch(leftExtensions, rightExtensions, seedLength, seedError, minLength, epsilon);

    // no match found, since minLength not reached (all length combinations are < 150)
    EXPECT_TRUE(endPositionPair == TPair(0, 0));
}

TEST(longestEpsMatch, multipleValidEpsMatches)
{
    seqan::String<stellar::ExtensionEndPosition<size_t> > leftExtensions{};
    seqan::String<stellar::ExtensionEndPosition<size_t> > rightExtensions{};

    appendValue(leftExtensions, TExtensionEndPosition{5, 0, 0}); // error: 0
    appendValue(leftExtensions, TExtensionEndPosition{9, 1, 1}); // error: 1
    appendValue(leftExtensions, TExtensionEndPosition{10, 2, 2}); // error: 2
    appendValue(leftExtensions, TExtensionEndPosition{15, 3, 3}); // error: 3
    appendValue(leftExtensions, TExtensionEndPosition{17, 4, 4}); // error: 4
    appendValue(leftExtensions, TExtensionEndPosition{19, 5, 5}); // error: 5
    appendValue(leftExtensions, TExtensionEndPosition{21, 6, 6}); // error: 6
    appendValue(leftExtensions, TExtensionEndPosition{24, 7, 7}); // error: 7

    appendValue(rightExtensions, TExtensionEndPosition{2, 0, 0}); // error: 0
    appendValue(rightExtensions, TExtensionEndPosition{5, 1, 1}); // error: 1
    appendValue(rightExtensions, TExtensionEndPosition{8, 2, 2}); // error: 2
    appendValue(rightExtensions, TExtensionEndPosition{13, 3, 3}); // error: 3
    appendValue(rightExtensions, TExtensionEndPosition{16, 4, 4}); // error: 4
    appendValue(rightExtensions, TExtensionEndPosition{21, 5, 5}); // error: 5
    appendValue(rightExtensions, TExtensionEndPosition{28, 6, 6}); // error: 6
    appendValue(rightExtensions, TExtensionEndPosition{29, 7, 7}); // error: 7
    appendValue(rightExtensions, TExtensionEndPosition{32, 8, 8}); // error: 8
    appendValue(rightExtensions, TExtensionEndPosition{35, 9, 9}); // error: 9
    appendValue(rightExtensions, TExtensionEndPosition{67, 10, 10}); // error: 10
    appendValue(rightExtensions, TExtensionEndPosition{72, 11, 11}); // error: 11
    appendValue(rightExtensions, TExtensionEndPosition{73, 12, 12}); // error: 12
    appendValue(rightExtensions, TExtensionEndPosition{77, 13, 13}); // error: 13
    appendValue(rightExtensions, TExtensionEndPosition{81, 14, 14}); // error: 14
    appendValue(rightExtensions, TExtensionEndPosition{130, 15, 15}); // error: 15
    appendValue(rightExtensions, TExtensionEndPosition{131, 16, 16}); // error: 16
    appendValue(rightExtensions, TExtensionEndPosition{190, 17, 17}); // error: 17
    appendValue(rightExtensions, TExtensionEndPosition{192, 18, 18}); // error: 18

    // seed_error: 1
    // min_length: 128
    //
    // seed_length
    // +100            5|           6|          10|          16|          18|          20|          23|          25
    //    ||============|============|============|============|============|============|============|============
    //   2||L 1/107=.009|L 2/111=.018|L 3/112=.027|L 4/117=.034|L 5/119=.042|L 6/121=.050|L 7/123=.057|L 8/126=.063
    //   5||L 2/110=.018|L 3/114=.026|L 4/115=.035|L 5/120=.042|L 6/122=.049|L 7/124=.056|L 8/126=.063|? 9/129=.070
    //   8||L 3/113=.027|L 4/117=.034|L 5/118=.042|L 6/123=.049|L 7/125=.056|L 8/127=.063|? 9/129=.070|?10/132=.076
    //  13||L 4/118=.034|L 5/122=.041|L 6/123=.049|o 7/128=.055|o 8/130=.062|? 9/132=.068|?10/134=.075|?11/137=.080
    //  16||L 5/121=.041|L 6/125=.048|L 7/126=.056|o 8/131=.061|? 9/133=.068|?10/135=.074|?11/137=.080|?12/140=.086
    //  21||L 6/126=.048|o 7/130=.054|o 8/131=.061|? 9/136=.066|?10/138=.072|?11/140=.079|?12/142=.085|x13/145=.090
    //  23||o 7/133=.053|o 8/137=.058|? 9/138=.065|?10/143=.070|?11/145=.076|?12/147=.082|x13/149=.087|x14/152=.092
    //  25||o 8/134=.060|? 9/138=.065|?10/139=.072|?11/144=.076|?12/146=.082|x13/148=.088|x14/150=.093|x15/153=.098
    //  26||? 9/137=.066|?10/141=.071|?11/142=.077|?12/147=.082|x13/149=.087|x14/151=.093|x15/153=.098|?16/156=.103
    //  27||?10/140=.071|?11/144=.076|?12/145=.083|x13/150=.087|x14/152=.092|x15/154=.097|?16/156=.103|x17/159=.107
    //  67||?11/172=.064|?12/176=.068|x13/177=.073|x14/182=.077|x15/184=.082|?16/186=.086|x17/188=.090|?18/191=.094
    //  72||?12/177=.068|x13/181=.072|x14/182=.077|x15/187=.080|?16/189=.085|x17/191=.089|?18/193=.093|?19/196=.097
    //  77||x13/178=.073|x14/182=.077|x15/183=.082|?16/188=.085|x17/190=.089|?18/192=.094|?19/194=.098|x20/197=.102
    //  81||x14/182=.077|x15/186=.081|?16/187=.086|x17/192=.089|?18/194=.093|?19/196=.097|x20/198=.101|x21/201=.104
    // 130||x15/186=.081|?16/190=.084|x17/191=.089|?18/196=.092|?19/198=.096|x20/200=.100|x21/202=.104|x22/205=.107
    // 131||?16/235=.068|x17/239=.071|?18/240=.075|?19/245=.078|x20/247=.081|x21/249=.084|x22/251=.088|x23/254=.091
    // 190||x17/236=.072|?18/240=.075|?19/241=.079|x20/246=.081|x21/248=.085|x22/250=.088|x23/252=.091|x24/255=.094
    // 191||?18/295=.061|?19/299=.064|x20/300=.067|x21/305=.069|x22/307=.072|x23/309=.074|x24/311=.077|x25/314=.080
    // 192||?19/297=.064|x20/301=.066|x21/302=.070|x22/307=.072|x23/309=.074|x24/311=.077|x25/313=.080|x26/316=.082
    //
    // Legend: ?: Might be an eps-match, o: Is an eps-match, x: Is NO eps-match, L: min-length not reached

    size_t seedLength = 100;
    size_t seedError = 1;
    double epsilon = 0.06;
    size_t minLength = 128; // allow 7 errors

    TPair endPositionPair
        = stellar::longestEpsMatch(leftExtensions, rightExtensions, seedLength, seedError, minLength, epsilon);

    // valid eps-matches:
    // (e: 8, l: 134, L[0], R[7])
    // (e: 8, l: 137, L[1], R[6]) // longest one
    // (e: 7, l: 133, L[0], R[6])
    // (e: 7, l: 130, L[1], R[5])
    // (e: 7, l: 128, L[3], R[3])
    EXPECT_EQ(endPositionPair.i1 - begin(leftExtensions), 1);
    EXPECT_EQ(endPositionPair.i2 - begin(rightExtensions), 6);
}

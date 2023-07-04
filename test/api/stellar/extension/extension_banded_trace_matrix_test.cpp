#include <gtest/gtest.h>

#include <stellar/extension/extension_banded_trace_matrix.hpp>

TEST(extension_banded_trace_matrix, construct)
{
    stellar::extension_banded_trace_matrix matrix
    {
        6u, //rowCount
        5u, //columnCount
        -2, //lowerDiagonal
        +2 //upperDiagonal
    };

    EXPECT_EQ(matrix.rows(), 6u);
    EXPECT_EQ(matrix.columns(), 5u);
    EXPECT_EQ(matrix.lowerDiagonal(), -2);
    EXPECT_EQ(matrix.upperDiagonal(), +2);
}

using TPositionInterval = std::pair<size_t, size_t>;
TEST(extension_banded_trace_matrix, rowInterval)
{
    {
        //  |e|A|B|C|D|
        // e|0|1|2|x|x|
        // A|1|2|3|4|x|
        // B|2|3|4|5|6|
        // C|x|4|5|6|7|
        // D|x|x|6|7|8|
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, -2, +2};
        EXPECT_EQ(TPositionInterval(0u, 5u), matrix.rowInterval());
    }

    {
        //  |e|A|B|C|D|
        // e|x|x|x|x|x|
        // A|1|x|x|x|x|
        // B|2|3|x|x|x|
        // C|x|4|5|x|x|
        // D|x|x|6|7|x|
        // E|x|x|x|8|9|
        // F|x|x|x|x|0|
        // G|x|x|x|x|x|
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 8u, /*columns*/ 5u, -2, -1};
        EXPECT_EQ(TPositionInterval(1u, 7u), matrix.rowInterval());
    }

    {
        //  |e|A|B|C|D|
        // e|x|1|2|x|x|
        // A|x|x|3|4|x|
        // B|x|x|x|5|6|
        // C|x|x|x|x|7|
        // D|x|x|x|x|x|
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, +1, +2};
        EXPECT_EQ(TPositionInterval(0u, 4u), matrix.rowInterval());
    }
}

TEST(extension_banded_trace_matrix, columnIntervalInRow)
{
    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, -2, +2};

        //  |e|A|B|C|D|
        // e|0|1|2|x|x|
        EXPECT_EQ(TPositionInterval(0u, 3u), matrix.columnIntervalInRow(0u));
        // A|1|2|3|4|x|
        EXPECT_EQ(TPositionInterval(0u, 4u), matrix.columnIntervalInRow(1u));
        // B|2|3|4|5|6|
        EXPECT_EQ(TPositionInterval(0u, 5u), matrix.columnIntervalInRow(2u));
        // C|x|4|5|6|7|
        EXPECT_EQ(TPositionInterval(1u, 5u), matrix.columnIntervalInRow(3u));
        // D|x|x|6|7|8|
        EXPECT_EQ(TPositionInterval(2u, 5u), matrix.columnIntervalInRow(4u));
    }

    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 8u, /*columns*/ 5u, -2, -1};

        //  |e|A|B|C|D|
        // e|x|x|x|x|x|
        EXPECT_EQ(TPositionInterval(0u, 0u), matrix.columnIntervalInRow(0u));
        // A|1|x|x|x|x|
        EXPECT_EQ(TPositionInterval(0u, 1u), matrix.columnIntervalInRow(1u));
        // B|2|3|x|x|x|
        EXPECT_EQ(TPositionInterval(0u, 2u), matrix.columnIntervalInRow(2u));
        // C|x|4|5|x|x|
        EXPECT_EQ(TPositionInterval(1u, 3u), matrix.columnIntervalInRow(3u));
        // D|x|x|6|7|x|
        EXPECT_EQ(TPositionInterval(2u, 4u), matrix.columnIntervalInRow(4u));
        // E|x|x|x|8|9|
        EXPECT_EQ(TPositionInterval(3u, 5u), matrix.columnIntervalInRow(5u));
        // F|x|x|x|x|0|
        EXPECT_EQ(TPositionInterval(4u, 5u), matrix.columnIntervalInRow(6u));
        // G|x|x|x|x|x|
        EXPECT_EQ(TPositionInterval(5u, 5u), matrix.columnIntervalInRow(7u));
        // H|x|x|x|x|x|
        EXPECT_EQ(TPositionInterval(5u, 5u), matrix.columnIntervalInRow(8u));
    }

    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, +1, +2};
        //  |e|A|B|C|D|
        // e|x|1|2|x|x|
        EXPECT_EQ(TPositionInterval(1u, 3u), matrix.columnIntervalInRow(0u));
        // A|x|x|3|4|x|
        EXPECT_EQ(TPositionInterval(2u, 4u), matrix.columnIntervalInRow(1u));
        // B|x|x|x|5|6|
        EXPECT_EQ(TPositionInterval(3u, 5u), matrix.columnIntervalInRow(2u));
        // C|x|x|x|x|7|
        EXPECT_EQ(TPositionInterval(4u, 5u), matrix.columnIntervalInRow(3u));
        // D|x|x|x|x|x|
        EXPECT_EQ(TPositionInterval(5u, 5u), matrix.columnIntervalInRow(4u));
        // E|x|x|x|x|x|
        EXPECT_EQ(TPositionInterval(5u, 5u), matrix.columnIntervalInRow(5u));
    }
}

TEST(extension_banded_trace_matrix, data)
{
    {
        //  |e|A|B|C|D|
        // e|0|1|2|x|x| = 5
        // A|1|2|3|4|x| = 5
        // B|2|3|4|5|6| = 5
        // C|x|4|5|6|7| = 5
        // D|x|x|6|7|8| = 5
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, -2, +2};
        EXPECT_EQ(matrix.dataSize(), 5 * 5);
        EXPECT_EQ(matrix.data().size(), 5 * 5);
    }

    {
        //  |e|A|B|C|D|
        // e|x|x|x|x|x| = 0
        // A|1|x|x|x|x| = 2
        // B|2|3|x|x|x| = 2
        // C|x|4|5|x|x| = 2
        // D|x|x|6|7|x| = 2
        // E|x|x|x|8|9| = 2
        // F|x|x|x|x|0| = 2
        // G|x|x|x|x|x| = 0
        // H|x|x|x|x|x| = 0
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 8u, /*columns*/ 5u, -2, -1};
        EXPECT_EQ(matrix.dataSize(), 6 * 2);
        EXPECT_EQ(matrix.data().size(), 6 * 2);
    }

    {
        //  |e|A|B|C|D|
        // e|x|1|2|x|x| = 2
        // A|x|x|3|4|x| = 2
        // B|x|x|x|5|6| = 2
        // C|x|x|x|x|7| = 2
        // D|x|x|x|x|x| = 0
        // E|x|x|x|x|x| = 0
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, +1, +2};
        EXPECT_EQ(matrix.dataSize(), 4 * 2);
        EXPECT_EQ(matrix.data().size(), 4 * 2);
    }
}

TEST(extension_banded_trace_matrix, rowSpan)
{
    auto actualTraceData = [](auto const & data)
    {
        return std::vector<int>(data.begin(), data.end());
    };

    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, -2, +2};
        std::iota(matrix.data().begin(), matrix.data().end(), seqan2::TraceBack{});

        //      ||e|A|B|C|D||
        // e|0|1||2|3|4|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(0)), (std::vector<int>{2, 3, 4}));
        // A  |5||6|7|8|9|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(1)), (std::vector<int>{6, 7, 8, 9}));
        // B    ||0|1|2|3|4||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(2)), (std::vector<int>{10, 11, 12, 13, 14}));
        // C    ||x|5|6|7|8||9|
        EXPECT_EQ(actualTraceData(matrix.rowSpan(3)), (std::vector<int>{15, 16, 17, 18}));
        // D    ||x|x|0|1|2||3|4|
        EXPECT_EQ(actualTraceData(matrix.rowSpan(4)), (std::vector<int>{20, 21, 22}));
    }

    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 8u, /*columns*/ 5u, -2, -1};
        std::iota(matrix.data().begin(), matrix.data().end(), seqan2::TraceBack{});

        //    ||e|A|B|C|D||
        // e  ||x|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(0)), (std::vector<int>{}));
        // A|0||1|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(1)), (std::vector<int>{1}));
        // B  ||2|3|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(2)), (std::vector<int>{2, 3}));
        // C  ||x|4|5|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(3)), (std::vector<int>{4, 5}));
        // D  ||x|x|6|7|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(4)), (std::vector<int>{6, 7}));
        // E  ||x|x|x|8|9||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(5)), (std::vector<int>{8, 9}));
        // F  ||x|x|x|x|0||1|
        EXPECT_EQ(actualTraceData(matrix.rowSpan(6)), (std::vector<int>{10}));
        // G  ||x|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(7)), (std::vector<int>{}));
        // H  ||x|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(8)), (std::vector<int>{}));
    }

    {
        stellar::extension_banded_trace_matrix matrix{/*rows*/ 5u, /*columns*/ 5u, +1, +2};
        std::iota(matrix.data().begin(), matrix.data().end(), seqan2::TraceBack{});

        //  |e|A|B|C|D||
        // e|x|0|1|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(0)), (std::vector<int>{0, 1}));
        // A|x|x|2|3|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(1)), (std::vector<int>{2, 3}));
        // B|x|x|x|4|5||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(2)), (std::vector<int>{4, 5}));
        // C|x|x|x|x|6||7|
        EXPECT_EQ(actualTraceData(matrix.rowSpan(3)), (std::vector<int>{6}));
        // D|x|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(4)), (std::vector<int>{}));
        // E|x|x|x|x|x||
        EXPECT_EQ(actualTraceData(matrix.rowSpan(5)), (std::vector<int>{}));
    }
}

/**
 * @file
 */
#include <cstring>
#include "testlib.h"
#include "../src/sortlib.h"

Line cstrToLine(const char* str) {
    return { str, str + strlen(str) };
}

void compareLines(std::vector<Line>& actual, std::vector<Line>& expected) {
    ASSERT_EQUALS(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        ASSERT_EQUALS(actual[i].lineStart, expected[i].lineStart);
        ASSERT_EQUALS(actual[i].lineEnd, expected[i].lineEnd);
    }
}

//----------------------------------------------------------------------------------------------------------------------

TEST(compareLinesDirect, compareLines_equalLines) {
    const char* str1 = "abc";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesDirect(line1, line2), 0);
}

TEST(compareLinesDirect, compareLines_firstIsLess) {
    const char* str1 = "abc";
    const char* str2 = "abd";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_firstIsGreater) {
    const char* str1 = "abd";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

TEST(compareLinesDirect, compareLines_firstIsShorter) {
    const char* str1 = "ab";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_secondIsShorter) {
    const char* str1 = "abc";
    const char* str2 = "ab";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(sortLinesDirect, linesAreSorted) {
    std::vector<Line> lines = {
            cstrToLine("abc"),
            cstrToLine("abd"),
            cstrToLine("abe"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("abc"),
            cstrToLine("abd"),
            cstrToLine("abe"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesDirect);

    compareLines(lines, expectedResult);
}

TEST(sortLinesDirect, randomUnsortedLines) {
    std::vector<Line> lines = {
            cstrToLine("ab"),
            cstrToLine("abdeda"),
            cstrToLine("dccbe"),
            cstrToLine("dcf"),
            cstrToLine("badc"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("ab"),
            cstrToLine("abdeda"),
            cstrToLine("badc"),
            cstrToLine("dccbe"),
            cstrToLine("dcf"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesDirect);

    compareLines(lines, expectedResult);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(sortLinesReverse, linesAreSorted) {
    std::vector<Line> lines = {
            cstrToLine("cba"),
            cstrToLine("dba"),
            cstrToLine("eba"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("cba"),
            cstrToLine("dba"),
            cstrToLine("eba"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesReverse);

    compareLines(lines, expectedResult);
}

TEST(sortLinesReverse, randomUnsortedLines) {
    std::vector<Line> lines = {
            cstrToLine("ab"),
            cstrToLine("abdeda"),
            cstrToLine("cf"),
            cstrToLine("dccbe"),
            cstrToLine("dcf"),
            cstrToLine("badc"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("abdeda"),
            cstrToLine("ab"),
            cstrToLine("badc"),
            cstrToLine("dccbe"),
            cstrToLine("cf"),
            cstrToLine("dcf"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesReverse);

    compareLines(lines, expectedResult);
}

/**
 * @file
 */
#include <cstring>
#include "testlib.h"
#include "../src/sortlib.h"

Line cstrToLine(const char* str) {
    return { str, str + strlen(str) - 1 }; // -1 excludes \0 from the Line
}

void compareLines(std::vector<Line>& actual, std::vector<Line>& expected) {
    ASSERT_EQUALS(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        ASSERT_EQUALS(actual[i].lineStart, expected[i].lineStart);
        ASSERT_EQUALS(actual[i].lineEnd, expected[i].lineEnd);
    }
}

//----------------------------------------------------------------------------------------------------------------------

TEST(compareLinesDirect, compareLines_equalLines_english) {
    const char* str1 = "abc";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesDirect(line1, line2), 0);
}

TEST(compareLinesDirect, compareLines_equalLinesWithPunctuatuion_english) {
    const char* str1 = "--1-1-1-!!-a  b!;!c,,   ";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesDirect(line1, line2), 0);
}

TEST(compareLinesDirect, compareLines_firstIsLess_english) {
    const char* str1 = "abc";
    const char* str2 = "abd";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_firstIsGreater_english) {
    const char* str1 = "abd";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

TEST(compareLinesDirect, compareLines_firstIsShorter_english) {
    const char* str1 = "ab";
    const char* str2 = "abc";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_secondIsShorter_english) {
    const char* str1 = "abc";
    const char* str2 = "ab";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

TEST(compareLinesDirect, compareLines_equalLines_russian) {
    const char* str1 = "абв";
    const char* str2 = "абв";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesDirect(line1, line2), 0);
}

TEST(compareLinesDirect, compareLines_equalLinesWithPunctuation_russian) {
    const char* str1 = "  3--31(%@ а ----!1323!#_%)б    в!!31-3-1    ";
    const char* str2 = "абв";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesDirect(line1, line2), 0);
}

TEST(compareLinesDirect, compareLines_firstIsLess_russian) {
    const char* str1 = "абв";
    const char* str2 = "абг";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_firstIsGreater_russian) {
    const char* str1 = "абг";
    const char* str2 = "абв";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

TEST(compareLinesDirect, compareLines_firstIsShorter_russian) {
    const char* str1 = "аб";
    const char* str2 = "абв";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) < 0);
}

TEST(compareLinesDirect, compareLines_secondIsShorter_russian) {
    const char* str1 = "абв";
    const char* str2 = "аб";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesDirect(line1, line2) > 0);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(compareLinesReverse, compareLines_equalLines_english) {
    const char* str1 = "cba";
    const char* str2 = "cba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesReverse(line1, line2), 0);
}

TEST(compareLinesReverse, compareLines_equalLinesWithPunctuation_english) {
    const char* str1 = "    5325%#@%@0  c!!#_%(!b %#@#(%) a %@  ";
    const char* str2 = "cba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesReverse(line1, line2), 0);
}

TEST(compareLinesReverse, compareLines_firstIsLess_english) {
    const char* str1 = "cba";
    const char* str2 = "dba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) < 0);
}

TEST(compareLinesReverse, compareLines_firstIsGreater_english) {
    const char* str1 = "dba";
    const char* str2 = "cba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) > 0);
}

TEST(compareLinesReverse, compareLines_firstIsShorter_english) {
    const char* str1 = "ba";
    const char* str2 = "cba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) < 0);
}

TEST(compareLinesReverse, compareLines_secondIsShorter_english) {
    const char* str1 = "cba";
    const char* str2 = "ba";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) > 0);
}

TEST(compareLinesReverse, compareLines_equalLines_russian) {
    const char* str1 = "вба";
    const char* str2 = "вба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesReverse(line1, line2), 0);
}

TEST(compareLinesReverse, compareLines_equalLinesWithPunctuation_russian) {
    const char* str1 = "   !@#в б :\"!@$%\\// а  412 ";
    const char* str2 = "вба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_EQUALS(compareLinesReverse(line1, line2), 0);
}

TEST(compareLinesReverse, compareLines_firstIsLess_russian) {
    const char* str1 = "вба";
    const char* str2 = "гба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) < 0);
}

TEST(compareLinesReverse, compareLines_firstIsGreater_russian) {
    const char* str1 = "гба";
    const char* str2 = "вба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) > 0);
}

TEST(compareLinesReverse, compareLines_firstIsShorter_russian) {
    const char* str1 = "ба";
    const char* str2 = "вба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) < 0);
}

TEST(compareLinesReverse, compareLines_secondIsShorter_russian) {
    const char* str1 = "вба";
    const char* str2 = "ба";

    Line line1 = cstrToLine(str1);
    Line line2 = cstrToLine(str2);

    ASSERT_TRUE(compareLinesReverse(line1, line2) > 0);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(sortLinesDirect, linesAreSorted_english) {
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

TEST(sortLinesDirect, randomUnsortedLines_english) {
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

TEST(sortLinesDirect, linesAreSorted_russian) {
    std::vector<Line> lines = {
            cstrToLine("абв"),
            cstrToLine("абг"),
            cstrToLine("абд"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("абв"),
            cstrToLine("абг"),
            cstrToLine("абд"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesDirect);

    compareLines(lines, expectedResult);
}

TEST(sortLinesDirect, randomUnsortedLines_russian) {
    std::vector<Line> lines = {
            cstrToLine("аб"),
            cstrToLine("абгдга"),
            cstrToLine("гввбд"),
            cstrToLine("гве"),
            cstrToLine("багв"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("аб"),
            cstrToLine("абгдга"),
            cstrToLine("багв"),
            cstrToLine("гввбд"),
            cstrToLine("гве"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesDirect);

    compareLines(lines, expectedResult);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(sortLinesReverse, linesAreSorted_english) {
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

TEST(sortLinesReverse, randomUnsortedLines_english) {
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

TEST(sortLinesReverse, linesAreSorted_russian) {
    std::vector<Line> lines = {
            cstrToLine("вба"),
            cstrToLine("гба"),
            cstrToLine("дба"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("вба"),
            cstrToLine("гба"),
            cstrToLine("дба"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesReverse);

    compareLines(lines, expectedResult);
}

TEST(sortLinesReverse, randomUnsortedLines_russian) {
    std::vector<Line> lines = {
            cstrToLine("аб"),
            cstrToLine("абгдга"),
            cstrToLine("ве"),
            cstrToLine("гввгд"),
            cstrToLine("гве"),
            cstrToLine("багв"),
    };

    std::vector<Line> expectedResult = {
            cstrToLine("абгдга"),
            cstrToLine("аб"),
            cstrToLine("багв"),
            cstrToLine("гввгд"),
            cstrToLine("ве"),
            cstrToLine("гве"),
    };

    sortLines(lines.begin(), lines.end(), compareLinesReverse);

    compareLines(lines, expectedResult);
}

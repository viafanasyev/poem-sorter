/**
 * @file
 */
#include <cassert>
#include <iostream>
#include <vector>
#include "MappedFile.h"
#include "sortlib.h"

/**
 * Splits the given text by lines (by '\\n' symbols). Empty lines (lines without letters) are removed.
 * Each '\\n' replaced with '\\0'.
 * @param[in] start pointer to a first character of the text to split
 * @param[in] len   length of the text to split
 * @return vector of Line - pointers to the first and last symbol of the line.
 */
std::vector<Line> splitLines(char* start, size_t len) {
    assert(start != nullptr);

    std::vector<Line> lines;

    char* end = start + len;
    char* cur = start;
    bool containsAlpha = false;
    while (cur < end) {
        containsAlpha = false;
        while (cur < end && *cur != '\n') {
            containsAlpha |= tolower(*cur) >= 'a' && tolower(*cur) <= 'z';
            ++cur;
        }
        if (containsAlpha) {
            lines.emplace_back(start, cur - 1);
        }
        *cur = '\0';
        start = ++cur;
    }

    return lines;
}

/**
 * Writes lines to the given file.
 * @param[in] lines    lines to write
 * @param[in] fileName name of the file to write the lines in
 */
void writeLines(const std::vector<Line>& lines, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    for (auto [start, _] : lines) {
        fprintf(file, "%s\n", start);
    }
}

/**
 * Writes the text lines sorted in direct order to the given file.
 * @param[in] lines    lines to sort and write
 * @param[in] fileName name of the file to write the lines in
 */
void writeSortedDirect(std::vector<Line> lines, const char* fileName) {
    sortLines(lines.begin(), lines.end(), compareLinesDirect);
    writeLines(lines, fileName);
}

/**
 * Writes the text lines sorted in reverse order to the given file.
 * @param[in] lines    lines to sort and write
 * @param[in] fileName name of the file to write the lines in
 */
void writeSortedReverse(std::vector<Line> lines, const char* fileName) {
    sortLines(lines.begin(), lines.end(), compareLinesReverse);
    writeLines(lines, fileName);
}

/**
 * Writes the original file lines to a given file.
 * @param[in] lines    lines of the original file
 * @param[in] fileName name of the file to write the lines in
 */
void writeOriginal(const std::vector<Line>& lines, const char* fileName) {
    writeLines(lines, fileName);
}

//----------------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "File path is not provided");
        return -1;
    }

    const char* filePath = argv[1];
    MappedFile mappedFile(filePath);
    if (mappedFile.getTextPtr() == nullptr) {
        fprintf(stderr, "Invalid file");
        return -1;
    }

    auto lines = splitLines(mappedFile.getTextPtr(), mappedFile.getTextSize());

    srand(time(nullptr));
    writeSortedDirect(lines, "direct_sorted.txt");
    writeSortedReverse(lines, "reverse_sorted.txt");
    writeOriginal(lines, "original.txt");

    return 0;
}

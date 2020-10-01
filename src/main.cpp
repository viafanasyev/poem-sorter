/**
 * @file
 */
#include <cassert>
#include <iostream>
#include <vector>
#include "MappedFile.h"
#include "sortlib.h"
#include "text_helpers.h"

/**
 * Writes lines to the given file.
 * @param[in] lines    lines to write
 * @param[in] fileName name of the file to write the lines in
 */
void writeLines(const std::vector<Line>& lines, const char* fileName) {
    assert(fileName != nullptr);

    FILE* file = fopen(fileName, "w");
    for (auto [start, _] : lines) {
        fprintf(file, "%s\n", start);
    }
    fclose(file);
}

/**
 * Writes the text lines sorted in direct order to the given file.
 * @param[in] lines    lines to sort and write
 * @param[in] fileName name of the file to write the lines in
 */
void writeSortedDirect(std::vector<Line> lines, const char* fileName) {
    assert(fileName != nullptr);

    sortLines(lines.begin(), lines.end(), compareLinesDirect);
    writeLines(lines, fileName);
}

/**
 * Writes the text lines sorted in reverse order to the given file.
 * @param[in] lines    lines to sort and write
 * @param[in] fileName name of the file to write the lines in
 */
void writeSortedReverse(std::vector<Line> lines, const char* fileName) {
    assert(fileName != nullptr);

    sortLines(lines.begin(), lines.end(), compareLinesReverse);
    writeLines(lines, fileName);
}

/**
 * Writes the original file lines to a given file.
 * @param[in] lines    lines of the original file
 * @param[in] fileName name of the file to write the lines in
 */
void writeOriginal(const std::vector<Line>& lines, const char* fileName) {
    assert(fileName != nullptr);

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

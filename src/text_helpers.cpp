/**
 * @file
 * @brief Source file with implementation of helper functions for UTF-8 text
 */
#include <cassert>
#include "text_helpers.h"

Line::Line(const char* _lineStart, const char* _lineEnd) {
    lineStart = _lineStart;
    lineEnd = _lineEnd;
}

/**
 * Checks if the given character is an english letter (lowercase or uppercase).
 * @param[in] c character to check
 * @return true, if the character is an english letter, false otherwise.
 */
bool isEnglishAlpha(unsigned char c) {
    return tolower(c) >= 'a' && tolower(c) <= 'z';
}

/**
 * Checks if the two given bytes are a russian letter (lowercase or uppercase) in UTF-8 encoding.
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return true, if the two given bytes form a russian letter in UTF-8.
 */
bool isRussianAlpha(unsigned char first, unsigned char second) {
    if (first == 208) {
        return (second >= 144 && second <= 175) // A - Я
            || (second >= 176 && second <= 191) // а - п
            || (second == 129);                 // Ё
    }
    if (first == 209) {
        return (second >= 128 && second <= 143) // р - я
            || (second == 145);                 // ё
    }

    return false;
}

/**
 * Gives the size of the letter in bytes. Supports english and russian languages in UTF-8 encoding.
 * Check is performed in direct order (from left to right).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return 2, if the given byte pair form a russian letter in UTF-8; <br>
 *         1, if the <b> first </b> byte of the byte pair form an english letter; <br>
 *         0, if the given bytes don't form a letter.
 */
unsigned short getAlphaSizeDirect(unsigned char first, unsigned char second) {
    if (isEnglishAlpha(first)) return 1;
    if (isRussianAlpha(first, second)) return 2;
    return 0;
}

/**
 * Gives the size of the letter in bytes. Supports english and russian languages in UTF-8 encoding.
 * Check is performed in reverse order (from right to left).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return 2, if the given byte pair form a russian letter in UTF-8; <br>
 *         1, if the <b> second </b> byte of the byte pair form an english letter; <br>
 *         0, if the given bytes don't form a letter.
 */
unsigned short getAlphaSizeReverse(unsigned char first, unsigned char second) {
    if (isRussianAlpha(first, second)) return 2;
    if (isEnglishAlpha(second)) return 1;
    return 0;
}

/**
 * Gives the zero-based ordinal of the russian letter in UTF-8 encoding (e.g. А - 0, Б - 1, Я - 32).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return zero-based ordinal of the russian letter in UTF-8 or -1 if the given byte pair doesn't form a russian letter.
 */
unsigned short getRussianAlphaOrdinal(unsigned char first, unsigned char second) {
    if (first == 208) {
        if (second >= 144 && second <= 149) { // А - Е
            return second - 144;
        }
        if (second == 129) { // Ё
            return 6;
        }
        if (second >= 150 && second <= 175) { // Ж - Я
            return second - 150 + 7;
        }

        if (second >= 176 && second <= 181) { // а - е
            return second - 176;
        }
        if (second >= 182 && second <= 191) { // ж - п
            return second - 182 + 7;
        }
    }
    if (first == 209) {
        if (second == 145) { // ё
            return 6;
        }
        if (second >= 128 && second <= 143) { // р - я
            return second - 128 + 17;
        }
    }

    return -1;
}

/**
 * Seeks for the next letter between given string pointers.
 * Moves the starting string pointer while seeks for letter.
 * Search is performed in direct order (from left to right).
 * @param[in, out] strPtr  pointer to start search from
 * @param[in]      lineEnd pointer to a last character of the line to search in
 * @return size of the letter that was found or 0 if there is no letters.
 */
unsigned short seekAlphaDirect(const char*& strPtr, const char* lineEnd) {
    assert(strPtr != nullptr);
    assert(lineEnd != nullptr);

    unsigned short alphaSize = 0;
    while (strPtr <= lineEnd && (alphaSize = getAlphaSizeDirect(*strPtr, *(strPtr + 1))) == 0) ++strPtr;
    return alphaSize;
}

/**
 * Seeks for the next letter between given string pointers.
 * Moves the starting string pointer while seeks for letter.
 * Search is performed in direct order (from right to left).
 * @param[in, out] strPtr    pointer to start search from
 * @param[in]      lineStart pointer to a first character of the line to search in
 * @return size of the letter that was found or 0 if there is no letters.
 */
unsigned short seekAlphaReverse(const char*& strPtr, const char* lineStart) {
    assert(strPtr != nullptr);
    assert(lineStart != nullptr);

    unsigned short alphaSize = 0;
    while (strPtr >= lineStart && (alphaSize = getAlphaSizeReverse(*(strPtr - 1), *strPtr)) == 0) --strPtr;
    return alphaSize;
}

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
    unsigned short alphaSize = 0;
    while (cur < end) {
        containsAlpha = false;
        while (cur < end && *cur != '\n') {
            alphaSize = getAlphaSizeDirect(*cur, *(cur + 1));
            if (alphaSize == 0) {
                ++cur;
            } else {
                containsAlpha = true;
                cur += alphaSize;
            }
        }
        if (containsAlpha) {
            lines.emplace_back(start, cur - 1);
        }
        *cur = '\0';
        start = ++cur;
    }

    return lines;
}

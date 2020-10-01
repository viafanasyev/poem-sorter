/**
 * @file
 * @brief Header file with description of helper functions for UTF-8 text
 */
#ifndef POEM_SORTER_TEXT_HELPERS_H
#define POEM_SORTER_TEXT_HELPERS_H

#include <cctype>
#include <vector>

/**
 * Structure that contains a line of text. Line has a pointer to it's first and last characters.
 * @note last character of line "abc" is meant to be 'c', not '\\0'.
 */
struct Line {
    const char* lineStart;
    const char* lineEnd;

    Line(const char* _lineStart, const char* _lineEnd);
};

/**
 * Checks if the given character is an english letter (lowercase or uppercase).
 * @param[in] c character to check
 * @return true, if the character is an english letter, false otherwise.
 */
bool isEnglishAlpha(unsigned char c);

/**
 * Checks if the two given bytes are a russian letter (lowercase or uppercase) in UTF-8 encoding.
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return true, if the two given bytes form a russian letter in UTF-8.
 */
bool isRussianAlpha(unsigned char first, unsigned char second);

/**
 * Gives the size of the letter in bytes. Supports english and russian languages in UTF-8 encoding.
 * Check is performed in direct order (from left to right).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return 2, if the given byte pair form a russian letter in UTF-8; <br>
 *         1, if the <b> first </b> byte of the byte pair form an english letter; <br>
 *         0, if the given bytes don't form a letter.
 */
unsigned short getAlphaSizeDirect(unsigned char first, unsigned char second);

/**
 * Gives the size of the letter in bytes. Supports english and russian languages in UTF-8 encoding.
 * Check is performed in reverse order (from right to left).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return 2, if the given byte pair form a russian letter in UTF-8; <br>
 *         1, if the <b> second </b> byte of the byte pair form an english letter; <br>
 *         0, if the given bytes don't form a letter.
 */
unsigned short getAlphaSizeReverse(unsigned char first, unsigned char second);

/**
 * Gives the zero-based ordinal of the russian letter in UTF-8 encoding (e.g. А - 0, Б - 1, Я - 32).
 * @param[in] first  high byte of the byte pair to check
 * @param[in] second low byte of the byte pair to check
 * @return zero-based ordinal of the russian letter in UTF-8 or -1 if the given byte pair doesn't form a russian letter.
 */
unsigned short getRussianAlphaOrdinal(unsigned char first, unsigned char second);

/**
 * Compares two english letters.
 * @param[in] c1 first letter to compare
 * @param[in] c2 second letter to compare.
 * @return negative number, if first letter is less than second; <br>
 *         positive number, if first letter is greater than second; <br>
 *         zero,            if both letters are equal.
 */
inline int compareEnglishAlphas(unsigned char c1, unsigned char c2) {
    return tolower(c1) - tolower(c2);
}

/**
 * Compares two russian letters in UTF-8 encoding.
 * @param[in] first1  high byte of the first letter
 * @param[in] second1 low byte of the first letter
 * @param[in] first2  high byte of the second letter
 * @param[in] second2 low byte of the second letter
 * @return negative number, if first letter is less than second; <br>
 *         positive number, if first letter is greater than second; <br>
 *         zero,            if both letters are equal.
 */
inline int compareRussianAlphas(unsigned char first1, unsigned char second1, unsigned char first2, unsigned char second2) {
    return getRussianAlphaOrdinal(first1, second1) - getRussianAlphaOrdinal(first2, second2);
}

/**
 * Seeks for the next letter between given string pointers.
 * Moves the starting string pointer while seeks for letter.
 * Search is performed in direct order (from left to right).
 * @param[in, out] strPtr  pointer to start search from
 * @param[in]      lineEnd pointer to a last character of the line to search in
 * @return size of the letter that was found or 0 if there is no letters.
 */
unsigned short seekAlphaDirect(const char*& strPtr, const char* lineEnd);

/**
 * Seeks for the next letter between given string pointers.
 * Moves the starting string pointer while seeks for letter.
 * Search is performed in direct order (from right to left).
 * @param[in, out] strPtr    pointer to start search from
 * @param[in]      lineStart pointer to a first character of the line to search in
 * @return size of the letter that was found or 0 if there is no letters.
 */
unsigned short seekAlphaReverse(const char*& strPtr, const char* lineStart);

/**
 * Splits the given text by lines (by '\\n' symbols). Empty lines (lines without letters) are removed.
 * Each '\\n' replaced with '\\0'.
 * @param[in] start pointer to a first character of the text to split
 * @param[in] len   length of the text to split
 * @return vector of Line - pointers to the first and last symbol of the line.
 */
std::vector<Line> splitLines(char* start, size_t len);

#endif //POEM_SORTER_TEXT_HELPERS_H

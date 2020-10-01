/**
 * @file
 * @brief Source file with sorting functions implementation
 */
#include <cassert>
#include "sortlib.h"

/**
 * Compares two Lines in direct (from left to right) order. Punctuation and space symbols are skipped - only letters are compared.
 * Supports english and russian letters in UTF-8 encoding.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second; <br>
 *         positive number, if first Line is greater than second; <br>
 *         zero,            if both Lines are equal.
 */
int compareLinesDirect(const Line& str1, const Line& str2) {
    const char* ptr1 = str1.lineStart;
    const char* ptr2 = str2.lineStart;

    unsigned short alphaSize1 = 0;
    unsigned short alphaSize2 = 0;

    while (ptr1 <= str1.lineEnd && ptr2 <= str2.lineEnd) {
        alphaSize1 = seekAlphaDirect(ptr1, str1.lineEnd);
        alphaSize2 = seekAlphaDirect(ptr2, str2.lineEnd);

        if (ptr1 > str1.lineEnd && ptr2 > str2.lineEnd) return 0;
        if (ptr1 > str1.lineEnd) return -1;
        if (ptr2 > str2.lineEnd) return +1;

        if (alphaSize1 < alphaSize2) return -1;
        if (alphaSize1 > alphaSize2) return +1;

        if (alphaSize1 == 1) {
            int cmpResult = compareEnglishAlphas(*ptr1, *ptr2);
            if (cmpResult != 0) return cmpResult;
        } else { // if alphaSize1 == 2
            int cmpResult = compareRussianAlphas(*ptr1, *(ptr1 + 1), *ptr2, *(ptr2 + 1));
            if (cmpResult != 0) return cmpResult;
        }

        ptr1 += alphaSize1;
        ptr2 += alphaSize2;
    }

    // To remove trailing punctuation signs
    seekAlphaDirect(ptr1, str1.lineEnd);
    seekAlphaDirect(ptr2, str2.lineEnd);

    if (ptr1 > str1.lineEnd && ptr2 <= str2.lineEnd) return -1;
    if (ptr2 > str2.lineEnd && ptr1 <= str1.lineEnd) return +1;
    return 0;
}

/**
 * Compares two Lines in reverse (from right to left) order. Punctuation and space symbols are skipped - only letters are compared.
 * Supports english and russian letters in UTF-8 encoding.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second; <br>
 *         positive number, if first Line is greater than second; <br>
 *         zero,            if both Lines are equal.
 */
int compareLinesReverse(const Line& str1, const Line& str2) {
    const char* ptr1 = str1.lineEnd;
    const char* ptr2 = str2.lineEnd;

    unsigned short alphaSize1 = 0;
    unsigned short alphaSize2 = 0;

    while (ptr1 >= str1.lineStart && ptr2 >= str2.lineStart) {
        alphaSize1 = seekAlphaReverse(ptr1, str1.lineStart);
        alphaSize2 = seekAlphaReverse(ptr2, str2.lineStart);

        if (ptr1 < str1.lineStart && ptr2 < str2.lineStart) return 0;
        if (ptr1 < str1.lineStart) return -1;
        if (ptr2 < str2.lineStart) return +1;

        if (alphaSize1 < alphaSize2) return -1;
        if (alphaSize1 > alphaSize2) return +1;

        if (alphaSize1 == 1) {
            int cmpResult = compareEnglishAlphas(*ptr1, *ptr2);
            if (cmpResult != 0) return cmpResult;
        } else { // if alphaSize1 == 2
            int cmpResult = compareRussianAlphas(*(ptr1 - 1), *ptr1, *(ptr2 - 1), *ptr2);
            if (cmpResult != 0) return cmpResult;
        }

        ptr1 -= alphaSize1;
        ptr2 -= alphaSize2;
    }

    // To remove leading punctuation signs
    seekAlphaReverse(ptr1, str1.lineStart);
    seekAlphaReverse(ptr2, str2.lineStart);

    if (ptr1 < str1.lineStart && ptr2 >= str2.lineStart) return -1;
    if (ptr2 < str2.lineStart && ptr1 >= str1.lineStart) return +1;
    return 0;
}

/**
 * Sorts vector of Lines with a given comparator.
 * Sort is performed in range [begin; end).
 * @param[in] begin   iterator to the start (inclusive) of the sorting range
 * @param[in] end     iterator to the end (exclusive) ot the sorting range
 * @param[in] compare pointer to the comparator. Comparator should return: <br>
 *                      negative value, if a \< b; <br>
 *                      positive value, if a \> b; <br>
 *                      zero,           if a == b.
 */
void sortLines(
        std::vector<Line>::iterator begin,
        std::vector<Line>::iterator end,
        int (*compare) (const Line&, const Line&)
) {
    assert(compare != nullptr);

    if (begin + 1 >= end) return;

    auto pivot = *(begin + (rand() % (end - begin)));
    auto i = begin, j = begin;
    int cmpResult;
    for (auto k = begin; k < end; ++k) {
        cmpResult = compare(*k, pivot);
        if (cmpResult < 0) {
            std::swap(*i, *k);
            if (i != j) {
                std::swap(*j, *k);
            }
            ++i;
            ++j;
        } else if (cmpResult == 0) {
            std::swap(*j, *k);
            ++j;
        }
    }

    if (begin + 1 < i) sortLines(begin, i, compare);
    if (j + 1 < end) sortLines(j, end, compare);
}

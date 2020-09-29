/**
 * @file
 * @brief Source file with sorting functions implementation
 */
#include <cassert>
#include <iostream>
#include "sortlib.h"

Line::Line(const char* _lineStart, const char* _lineEnd) {
    lineStart = _lineStart;
    lineEnd = _lineEnd;
}

/**
 * Compares two Lines in direct (from left to right) order. Punctuation and space symbols are skipped - only letters are compared.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second;
 *         positive number, if first Line is greater than second;
 *         zero,            if both Lines are equal.
 */
int compareLinesDirect(const Line& str1, const Line& str2) {
    const char* ptr1 = str1.lineStart;
    const char* ptr2 = str2.lineStart;

    while (ptr1 <= str1.lineEnd && ptr2 <= str2.lineEnd) {
        while (ptr1 <= str1.lineEnd && (tolower(*ptr1) < 'a' || tolower(*ptr1) > 'z')) ++ptr1;
        while (ptr2 <= str2.lineEnd && (tolower(*ptr2) < 'a' || tolower(*ptr2) > 'z')) ++ptr2;

        if (*ptr1 < *ptr2) return -1;
        if (*ptr1 > *ptr2) return 1;

        ++ptr1;
        ++ptr2;
    }

    if (ptr1 <= str1.lineEnd) return 1;
    if (ptr2 <= str2.lineEnd) return -1;
    return 0;
}

/**
 * Compares two Lines in reverse (from right to left) order. Punctuation and space symbols are skipped - only letters are compared.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second;
 *         positive number, if first Line is greater than second;
 *         zero,            if both Lines are equal.
 */
int compareLinesReverse(const Line& str1, const Line& str2) {
    const char* ptr1 = str1.lineEnd;
    const char* ptr2 = str2.lineEnd;

    while (ptr1 >= str1.lineStart && ptr2 >= str2.lineStart) {
        while (ptr1 >= str1.lineStart && (tolower(*ptr1) < 'a' || tolower(*ptr1) > 'z')) --ptr1;
        while (ptr2 >= str2.lineStart && (tolower(*ptr2) < 'a' || tolower(*ptr2) > 'z')) --ptr2;

        if (*ptr1 < *ptr2) return -1;
        if (*ptr1 > *ptr2) return 1;

        --ptr1;
        --ptr2;
    }

    if (ptr1 >= str1.lineStart) return 1;
    if (ptr2 >= str2.lineStart) return -1;
    return 0;
}

/**
 * Sorts vector of Lines with a given comparator.
 * Sort is performed in range [begin; end).
 * @param[in] begin   iterator to the start (inclusive) of the sorting range
 * @param[in] end     iterator to the end (exclusive) ot the sorting range
 * @param[in] compare pointer to the comparator. Comparator should return:
 *                      negative value, if a \< b;
 *                      positive value, if a > b;
 *                      zero, if a == b.
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

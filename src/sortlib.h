/**
 * @file
 * @brief Header file with sorting functions description
 */
#ifndef POEM_SORTER_SORTLIB_H
#define POEM_SORTER_SORTLIB_H

#include <vector>
#include "text_helpers.h"

/**
 * Compares two Lines in direct (from left to right) order. Punctuation and space symbols are skipped - only letters are compared.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second; <br>
 *         positive number, if first Line is greater than second; <br>
 *         zero,            if both Lines are equal.
 */
int compareLinesDirect(const Line& str1, const Line& str2);

/**
 * Compares two Lines in reverse (from right to left) order. Punctuation and space symbols are skipped - only letters are compared.
 * @param[in] str1 first Line to compare
 * @param[in] str2 second Line to compare
 * @return negative number, if first Line is less than second; <br>
 *         positive number, if first Line is greater than second; <br>
 *         zero,            if both Lines are equal.
 */
int compareLinesReverse(const Line& str1, const Line& str2);

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
);

#endif //POEM_SORTER_SORTLIB_H

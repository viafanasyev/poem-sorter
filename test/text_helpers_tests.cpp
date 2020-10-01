/**
 * @file
 */
#include <vector>
#include <cstring>
#include "testlib.h"
#include "../src/text_helpers.h"

TEST(isRussianAlpha, allRussianLetters) {
    std::vector<const char*> testCases = {
            "А", "а",
            "Б", "б",
            "В", "в",
            "Г", "г",
            "Д", "д",
            "Е", "е",
            "Ё", "ё",
            "Ж", "ж",
            "З", "з",
            "И", "и",
            "Й", "й",
            "К", "к",
            "Л", "л",
            "М", "м",
            "Н", "н",
            "О", "о",
            "П", "п",
            "Р", "р",
            "С", "с",
            "Т", "т",
            "У", "у",
            "Ф", "ф",
            "Х", "х",
            "Ц", "ц",
            "Ч", "ч",
            "Ш", "ш",
            "Щ", "щ",
            "Ъ", "ъ",
            "Ы", "ы",
            "Ь", "ь",
            "Э", "э",
            "Ю", "ю",
            "Я", "я",
    };

    for (auto str : testCases) {
        ASSERT_TRUE(isRussianAlpha(*str, *(str + 1)));
    }
}

TEST(isEnglishAlpha, allEnglishLetters) {
    std::vector<char> testCases = {
            'A', 'a',
            'B', 'b',
            'C', 'c',
            'D', 'd',
            'E', 'e',
            'F', 'f',
            'G', 'g',
            'H', 'h',
            'I', 'i',
            'J', 'j',
            'K', 'l',
            'L', 'l',
            'M', 'm',
            'N', 'n',
            'O', 'o',
            'P', 'p',
            'Q', 'q',
            'R', 'r',
            'S', 's',
            'T', 't',
            'U', 'u',
            'V', 'v',
            'W', 'w',
            'X', 'x',
            'Y', 'y',
            'Z', 'z',
    };

    for (auto c : testCases) {
        ASSERT_TRUE(isEnglishAlpha(c));
    }
}

TEST(getRussianAlphaOrdinal, allRussianLetters) {
    std::vector<std::pair<const char*, int> > testCases = {
            { "А", 0  }, { "а", 0  },
            { "Б", 1  }, { "б", 1  },
            { "В", 2  }, { "в", 2  },
            { "Г", 3  }, { "г", 3  },
            { "Д", 4  }, { "д", 4  },
            { "Е", 5  }, { "е", 5  },
            { "Ё", 6  }, { "ё", 6  },
            { "Ж", 7  }, { "ж", 7  },
            { "З", 8  }, { "з", 8  },
            { "И", 9  }, { "и", 9  },
            { "Й", 10 }, { "й", 10 },
            { "К", 11 }, { "к", 11 },
            { "Л", 12 }, { "л", 12 },
            { "М", 13 }, { "м", 13 },
            { "Н", 14 }, { "н", 14 },
            { "О", 15 }, { "о", 15 },
            { "П", 16 }, { "п", 16 },
            { "Р", 17 }, { "р", 17 },
            { "С", 18 }, { "с", 18 },
            { "Т", 19 }, { "т", 19 },
            { "У", 20 }, { "у", 20 },
            { "Ф", 21 }, { "ф", 21 },
            { "Х", 22 }, { "х", 22 },
            { "Ц", 23 }, { "ц", 23 },
            { "Ч", 24 }, { "ч", 24 },
            { "Ш", 25 }, { "ш", 25 },
            { "Щ", 26 }, { "щ", 26 },
            { "Ъ", 27 }, { "ъ", 27 },
            { "Ы", 28 }, { "ы", 28 },
            { "Ь", 29 }, { "ь", 29 },
            { "Э", 30 }, { "э", 30 },
            { "Ю", 31 }, { "ю", 31 },
            { "Я", 32 }, { "я", 32 },
    };

    for (auto [str, expected] : testCases) {
        ASSERT_EQUALS(getRussianAlphaOrdinal(*str, *(str + 1)), expected);
    }
}

TEST(getAlphaSizeDirect, allEnglishLetters) {
    std::vector<char> testCases = {
            'A', 'a',
            'B', 'b',
            'C', 'c',
            'D', 'd',
            'E', 'e',
            'F', 'f',
            'G', 'g',
            'H', 'h',
            'I', 'i',
            'J', 'j',
            'K', 'l',
            'L', 'l',
            'M', 'm',
            'N', 'n',
            'O', 'o',
            'P', 'p',
            'Q', 'q',
            'R', 'r',
            'S', 's',
            'T', 't',
            'U', 'u',
            'V', 'v',
            'W', 'w',
            'X', 'x',
            'Y', 'y',
            'Z', 'z',
    };

    for (auto c : testCases) {
        ASSERT_EQUALS(getAlphaSizeDirect(c, ' '), 1);
        ASSERT_EQUALS(getAlphaSizeDirect(' ', c), 0);
    }
}


TEST(getAlphaSizeDirect, allRussianLetters) {
    std::vector<const char*> testCases = {
            "А", "а",
            "Б", "б",
            "В", "в",
            "Г", "г",
            "Д", "д",
            "Е", "е",
            "Ё", "ё",
            "Ж", "ж",
            "З", "з",
            "И", "и",
            "Й", "й",
            "К", "к",
            "Л", "л",
            "М", "м",
            "Н", "н",
            "О", "о",
            "П", "п",
            "Р", "р",
            "С", "с",
            "Т", "т",
            "У", "у",
            "Ф", "ф",
            "Х", "х",
            "Ц", "ц",
            "Ч", "ч",
            "Ш", "ш",
            "Щ", "щ",
            "Ъ", "ъ",
            "Ы", "ы",
            "Ь", "ь",
            "Э", "э",
            "Ю", "ю",
            "Я", "я",
    };

    for (auto str : testCases) {
        ASSERT_EQUALS(getAlphaSizeDirect(*str, *(str + 1)), 2);
    }
}

TEST(getAlphaSizeReverse, allEnglishLetters) {
    std::vector<char> testCases = {
            'A', 'a',
            'B', 'b',
            'C', 'c',
            'D', 'd',
            'E', 'e',
            'F', 'f',
            'G', 'g',
            'H', 'h',
            'I', 'i',
            'J', 'j',
            'K', 'l',
            'L', 'l',
            'M', 'm',
            'N', 'n',
            'O', 'o',
            'P', 'p',
            'Q', 'q',
            'R', 'r',
            'S', 's',
            'T', 't',
            'U', 'u',
            'V', 'v',
            'W', 'w',
            'X', 'x',
            'Y', 'y',
            'Z', 'z',
    };

    for (auto c : testCases) {
        ASSERT_EQUALS(getAlphaSizeReverse(' ', c), 1);
        ASSERT_EQUALS(getAlphaSizeReverse(c, ' '), 0);
    }
}


TEST(getAlphaSizeReverse, allRussianLetters) {
    std::vector<const char*> testCases = {
            "А", "а",
            "Б", "б",
            "В", "в",
            "Г", "г",
            "Д", "д",
            "Е", "е",
            "Ё", "ё",
            "Ж", "ж",
            "З", "з",
            "И", "и",
            "Й", "й",
            "К", "к",
            "Л", "л",
            "М", "м",
            "Н", "н",
            "О", "о",
            "П", "п",
            "Р", "р",
            "С", "с",
            "Т", "т",
            "У", "у",
            "Ф", "ф",
            "Х", "х",
            "Ц", "ц",
            "Ч", "ч",
            "Ш", "ш",
            "Щ", "щ",
            "Ъ", "ъ",
            "Ы", "ы",
            "Ь", "ь",
            "Э", "э",
            "Ю", "ю",
            "Я", "я",
    };

    for (auto str : testCases) {
        ASSERT_EQUALS(getAlphaSizeReverse(*str, *(str + 1)), 2);
    }
}

TEST(splitLines, sampleTextWithEmptyLines_emptyLinesRemovedExpected) {
    char text[] = "abaca \n daba, jaba \n  \n ,,123%!%,, \n haba \n\n--\n";

    std::vector<const char*> expectedLines = {
            "abaca ",
            " daba, jaba ",
            " haba ",
    };

    std::vector<Line> result = splitLines(text, strlen(text));

    ASSERT_EQUALS(result.size(), expectedLines.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_EQUALS(strcmp(result[i].lineStart, expectedLines[i]), 0);
    }
}

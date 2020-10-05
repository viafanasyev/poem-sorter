/**
 * @file
 */
#include <cstring>
#include "testlib.h"
#include "../src/MappedFile.h"

void compareText(char* actual, char* expected) {
    ASSERT_EQUALS(strlen(actual), strlen(expected));
    ASSERT_EQUALS(strcmp(actual, expected), 0);
}

//----------------------------------------------------------------------------------------------------------------------

TEST(MappedFileConstructor, mappingForExistingFile) {
    char text[] = "asdada\nasdasd   !!dasd\nasda asd, dd\n";
    const char* fileName = "TESTFILE.txt";
    FILE* file = fopen(fileName, "w");
    fprintf(file, "%s", text);
    fflush(file);

    MappedFile mappedFile(fileName);

    fclose(file);
    remove(fileName);

    strcat(text, "\n");
    ASSERT_EQUALS(mappedFile.getTextSize(), strlen(text));
    compareText(mappedFile.getTextPtr(), text);
}

TEST(MappedFileConstructor, mappingForNonExistingFile) {
    const char* fileName = "NON_EXISTING_FILE.NON_EXISTING_EXTENSION";
    MappedFile mappedFile(fileName);

    ASSERT_EQUALS(mappedFile.getTextSize(), 0);
    ASSERT_TRUE(mappedFile.getTextPtr() == nullptr);
}

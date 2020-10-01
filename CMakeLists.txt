cmake_minimum_required(VERSION 3.16)
project(poem_sorter)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wfloat-equal)

add_executable(
        sorter
        src/main.cpp
        src/sortlib.h
        src/sortlib.cpp
        src/MappedFile.cpp
        src/MappedFile.h
        src/text_helpers.h
        src/text_helpers.cpp)

add_executable(
        tests
        test/testlib.h
        test/testlib.cpp
        test/main.cpp
        test/sortlib_tests.cpp
        test/MappedFile_tests.cpp
        test/text_helpers_tests.cpp
        src/sortlib.h
        src/sortlib.cpp
        src/MappedFile.cpp
        src/MappedFile.h
        src/text_helpers.h
        src/text_helpers.cpp)
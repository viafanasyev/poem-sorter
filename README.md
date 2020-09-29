# Poem sorter

## Project description

This program is developed as a part of ISP RAS course.  

Program can sort poems (or any other text files) in direct (left to right) and reverse (right to left) orders line by line.  

Only english language is supported so far.

### Structure

* src/ : Main project
    * main.cpp : Entry point for the program.
    * sortlib.h, sortlib.cpp : Library for sorting texts in different directions.
    * MappedFile.h, MappedFile.cpp : Class for simplifying mapping file in memory.

* test/ : Tests and testing library
    * testlib.h, testlib.cpp : Library for testing with assertions and helper macros.
    * main.cpp : Entry point for tests. Just runs all tests.
    * sortlib_tests.cpp : Sorting library tests.
    * MappedFile_tests.cpp : MappedFile class tests.

* doc/ : doxygen documentation

* Doxyfile : doxygen config file

### Run

#### Sorter

To run main program execute next commands in terminal:
```
cmake . && make
./sorter file_name.txt
```

Results are stored in three files:
* direct_sorted.txt : Text sorted in direct (from left ot right) order;
* reverse_sorted.txt : Text sorted in reverse (from right to left) order;
* original.txt : Original text (except that lines without letters are removed).

#### Tests

To run tests execute next commands in terminal:
```
cmake . && make
./tests
```

### Documentation

Doxygen is used to create documentation. You can watch it by opening `doc/html/index.html` in browser.  

### OS

Program is developed under Ubuntu 20.04.1 LTS.
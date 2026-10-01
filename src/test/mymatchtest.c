//
// Created by hi on 24.01.2026.
//
#include <stdio.h>
#include <string.h>
#include "../../include/mymatch.h"
int main() {
    struct {
        const char *str1;
        const char *str2;
        int expected;
    } tests[] = {
        {"hello", "hello", 1},
    {"Hello", "hello", 0},
    {"abc", "abcd", 0},
    {"", "", 1},
    {"test", "test1", 0},


    {"t*", "test1", 1},
    {"*e*", "test1", 1},
    {"*", "test", 1},
    {"*t", "test", 1},
    {"e*", "test", 0},
    {"*a", "test", 0},
    {"*e*t", "test", 1},
    {"t*t", "test", 1},
    {"*test", "test", 1},


    {"te*", "test", 1},
    {"*st", "test", 1},
    {"*es*", "test", 1},
    {"t??t", "test", 1},
    {"t??t", "tent", 1},
    {"t??t", "teet", 1},
    {"t??t", "tet", 0},
    {"t???", "test", 1},
    {"t???", "tests", 0},
    {"*a*", "", 0},
    {"a*b*c", "axbyc", 1},
    {"a*b*c", "abc", 1},
    {"a*b*c", "acb", 0},
{"t*?t", "test", 1},
{"*?st", "test", 1},
{"t*?s", "tests", 1},
{"t*?s", "test", 0},
{"*?*?*", "abc", 1},
{"*?*?*", "", 0},
{"*?*?*", "a", 0},
{"*?*?*", "ab", 1},
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < num_tests; i++) {
        int result = mymatch(tests[i].str1, tests[i].str2);
        if (result == tests[i].expected) {
            printf("Test %d passed!\n", i + 1);
            passed++;
        } else {
            printf("Test %d failed: mymatch(\"%s\", \"%s\") returned %d, expected %d\n",
                   i + 1, tests[i].str1, tests[i].str2, result, tests[i].expected);
        }
    }

    printf("%d/%d tests passed.\n", passed, num_tests);
    return 0;
}
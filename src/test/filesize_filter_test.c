#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/fileinfo.h"
#include "../../include/filters.h"
// Declare size_filter from your implementation


int main() {
    int failed = 0;


    FILE *f;
    const char *small_file = "small_test.txt";
    const char *medium_file = "medium_test.txt";
    const char *large_file = "large_test.txt";


    f = fopen(small_file, "wb");
    fwrite("0123456789", 1, 10, f);
    fclose(f);


    f = fopen(medium_file, "wb");
    char buf[1024] = {0};
    fwrite(buf, 1, 1024, f);
    fclose(f);


    f = fopen(large_file, "wb");
    fwrite(buf, 1, 5*1024, f);
    fclose(f);


    FileInfo fi_small = {.path = (char*)small_file};
    FileInfo fi_medium = {.path = (char*)medium_file};
    FileInfo fi_large = {.path = (char*)large_file};


    struct {
        FileInfo *fi;
        char *pattern;
        int expected;
        char *desc;
    } tests[] = {
        {&fi_small, "<20b", 1, "small_file < 20B"},
        {&fi_small, ">5b", 1, "small_file > 5B"},
        {&fi_small, "=10b", 1, "small_file = 10B"},
        {&fi_small, ">20b", 0, "small_file > 20B"},
        {&fi_medium, "<2k", 1, "medium_file < 2K"},
        {&fi_medium, ">1k", 0, "medium_file > 1K"},
        {&fi_large, ">4k", 1, "large_file > 4K"},
        {&fi_large, "<6k", 1, "large_file < 6K"},
    };

    int num_tests = sizeof(tests)/sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++) {
        int result = size_filter(tests[i].fi, tests[i].pattern);
        if (result == tests[i].expected) {
            printf("✓ PASS: %s\n", tests[i].desc);
        } else {
            printf("✗ FAIL: %s (got %d, expected %d)\n",
                   tests[i].desc, result, tests[i].expected);
            failed++;
        }
    }

    // -----------------------------
    // Cleanup
    // -----------------------------
    remove(small_file);
    remove(medium_file);
    remove(large_file);

    if (failed == 0) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("%d test(s) failed\n", failed);
        return 1;
    }
}

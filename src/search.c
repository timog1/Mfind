//
// Created by hi on 24.01.2026.
//

#include "../include/mymatch.h"
#include "../include/search.h"

#include <string.h>

int search(const char *pattern,const char *string) {
    for (int j = 0; j < strlen(string); j++) {

        if (pattern[0] == string[j] || pattern[0] == '?') {
            if ( mymatch(&pattern[1], &string[j+1])) {
                return 1;
            }
        }
    }
    return 0;
}

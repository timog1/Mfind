//
// Created by hi on 24.01.2026.
//


#include <string.h>
#include "../include/mymatch.h"

#include <stdio.h>

#include "../include/search.h"

int mymatch(const char *pattern,const char *string) {

    for (int i = 0; i < strlen(pattern); i++) {
        if (pattern[i] == '*') {
            if (i+1 == strlen(pattern)) {
                return 1;
            }

            return search(&pattern[i+1], string);

        } else {
            if (pattern[i] != string[i] && pattern[i] != '?') {
                return 0;
            }

        }


    }

    if (strlen(pattern) == strlen(string)) {

        return 1;
    }
    return 0;

}



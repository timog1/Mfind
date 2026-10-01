#include <ctype.h>
#include <stdio.h>
#include <fnmatch.h>
#include "../include/fileinfo.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size_filter(FileInfo *fi, void *ctx) {
    FILE *f = fopen(fi->path, "rb");
    const char* pattern = ctx;
    if (f == NULL) {
        perror("Datei konnte nicht geöffnet werden");
        return -1;
    }
    int val = 0;
    for (int i = 1; pattern != '\0'; i++) {
        if (isdigit(pattern[i])) {
            val = val * 10 + (pattern[i] - '0');

        } else {
            switch (pattern[i]) {
                case 'b':


                    break;
                case 'k':

                    val =  val *1024;
                    break;
                case 'm':
                    val =  val *1024*1024;
                    break;
                case 'g':
                    val = val *1024*1024*1024;
                    break;
                default:
                    break;
            }
            break;

        }
    }


    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    fclose(f);

    switch (*pattern) {
        case '<':
            return size < val;
        case '>':
            return size > val;
        case '=':
            return size == val;
        default:
            return 0;
    }
    return 0;
}



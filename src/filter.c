

#include "../include/mymatch.h"
#include "../include/fileinfo.h"


int name_filter(FileInfo *fi, void *ctx) {
    const char* pattern = ctx;
    return mymatch(pattern, fi->name);

}
#ifndef FILEINFO_H
#define FILEINFO_H

#include <sys/stat.h>

typedef struct {
    char *path;
    const char *name;
    struct stat st;

} FileInfo;

#endif
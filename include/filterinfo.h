//
// Created by hi on 11.01.2026.
//
#include "fileinfo.h"
#include "Stream.h"
#ifndef MFIND_FILTERINFO_H
#define MFIND_FILTERINFO_H
typedef struct {
    Stream *stream;
    char *pattern;


} FilterInfo;
#endif //MFIND_FILTERINFO_H
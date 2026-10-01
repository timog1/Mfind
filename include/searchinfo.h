

#ifndef MFIND_SEARCHINFO_H
#define MFIND_SEARCHINFO_H
#include "processes.h"
#include "Stream.h"


typedef struct {
    const Stream *Stream;



    process **first;
} SearchInfo;
#endif //MFIND_SEARCHINFO_H
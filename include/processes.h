
#ifndef MFIND_PROCESSES_H
#define MFIND_PROCESSES_H
#include "fileinfo.h"


typedef struct process {
    struct process *next;
    int (*process_file)(FileInfo *fi, void *ctx);
    void *ctx;
} process;

void add_process(process **chain, process *add);
int get_process(process *chain, int t, process *res);
#endif
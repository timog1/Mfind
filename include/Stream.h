#include "fileinfo.h"
#include <pthread.h>

#ifndef MFIND_STREAM_H
#define MFIND_STREAM_H
typedef struct Node {
    FileInfo data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int done;//+1 per worker done
    int free;
} Stream;

void stream_init(Stream *s);
void stream_push(Stream *s, FileInfo fi);
void stream_destroy(Stream *s);
int stream_pop(Stream *s, FileInfo *out);
void done(Stream *s);
void addworker(Stream *s);
void removeworker(Stream *s);
#endif //MFIND_STREAM_H
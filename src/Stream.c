

#include <pthread.h>
#include "../include/Stream.h"

#include <stdlib.h>

#include "../include/fileinfo.h"

void stream_init(Stream *s) {
    s->head = s->tail = NULL;
    s->free = 0;
    s->done = 0;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
}
void done(Stream *s) {
    s->free = 1;
}

void stream_push(Stream *s, FileInfo fi) {
    Node *n = malloc(sizeof(Node));
    n->data = fi;
    n->next = NULL;

    pthread_mutex_lock(&s->mutex);
    if (s->tail)
        s->tail->next = n;
    else
        s->head = n;

    s->tail = n;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}

int stream_pop(Stream *s, FileInfo *out) {
    pthread_mutex_lock(&s->mutex);

    while (!s->head && !s->free)
        pthread_cond_wait(&s->cond, &s->mutex);

    if (!s->head) {
        pthread_mutex_unlock(&s->mutex);
        return 0; // nothing left
    }

    Node *n = s->head;
    s->head = n->next;
    if (!s->head) s->tail = NULL;

    *out = n->data;
    free(n);

    pthread_mutex_unlock(&s->mutex);
    return 1;
}
void addworker(Stream *s) {
    pthread_mutex_lock(&s->mutex);
    s->done += 1;
    pthread_mutex_unlock(&s->mutex);

}
void removeworker(Stream *s) {
    pthread_mutex_lock(&s->mutex);
    s->done -= 1;
    if (!s->head && s->done == 0) {
        // Letzter Worker + keine Jobs mehr
        s->free = 1;
        pthread_cond_broadcast(&s->cond);
    }
    pthread_mutex_unlock(&s->mutex);

}
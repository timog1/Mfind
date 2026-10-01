#include "../include/fileinfo.h"
#define _POSIX_C_SOURCE 200809L
#include "../include/filters.h"
#include "../include/searchinfo.h"
#include "../include/filterinfo.h"
#include  "../include/walker.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../include/processes.h"
#include "../include/args_auswerten.h"
#include "../include/Stream.h"
#include "../include/stdinworker.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct thread_info {
    int thread_id;
    SearchInfo si;
    int depth;
};
int main(int argc, char *argv[]) {
    SearchInfo si;
    int flag = 0;
    int if_threads = 0;
    const char *start_path = ".";
    process *filters = NULL;
    int threads_amount = 1;
    if (argc > 1) {
        if (argv[1][0] == '*') {
            flag = 1;
        }
        start_path = argv[1];
    }
    if (argc > 2 && argv[2][0] != '-') {
        char *endptr;
        int val = strtol(argv[2], &endptr, 10);

        if (*endptr != '\0') {
            fprintf(stderr, "Invalid number: %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        if (val <= 0) {
            fprintf(stderr, "Thread count must be positive\n");
            exit(EXIT_FAILURE);
        }
        threads_amount = (int)val;
        if_threads = 1;
    }
    if (argc > 2+if_threads) {
        filters = args_auswerten(argv,argc, if_threads);
    }

    si.first = &filters;
    if (flag) {
        stdinworker(filters);
        return 0;
    }
    pthread_t threads[threads_amount];
    Stream s;
    Stream *stream = &s;


    stream_init(stream);



    si.Stream = stream;
    stream->free = 0;
    stream->done = 0;
    struct stat st;
    if (lstat(start_path, &st) != 0) {
        perror(start_path);
        return 1;
    }
    FileInfo info = {
        .path = strdup(start_path),
        .name = NULL,
        .st = st
    };

    stream_push(stream, info);
    struct thread_info args[threads_amount];
    for (int i = 0; i < threads_amount; i++) {
        args[i].si = si;        // copy struct (important!)
        args[i].thread_id = i;

        pthread_create(&threads[i], NULL,
                       walk_directory_thread,
                       &args[i].si);
    }




    for (int i = 0; i < threads_amount; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;




}


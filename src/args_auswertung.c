#include <stdio.h>
#include <stdlib.h>
#include "../include/filters.h"
#include "../include/processes.h"
#include "../include/args_auswerten.h"
#include "../include/filterinfo.h"

process* args_auswerten(char* argv[], int argc, int start_index) {
    // start_index: index where the flags string is, e.g., 2 for "-ns"
    start_index = 2+start_index;
    if (start_index >= argc || argv[start_index][0] != '-') {
        return NULL;  // no flags given
    }

    process *filters = NULL;
    int arg_index = start_index + 1;  // index of first context argument
    char *flags = argv[start_index];

    for (int i = 1; flags[i] != '\0'; i++) { // skip the '-' in "-ns"
        int (*temp_proc)(FileInfo*, void*) = NULL;

        switch (flags[i]) {
            case 'n':
                temp_proc = name_filter;
                break;
            case 's':
                temp_proc = size_filter;
                break;
            default:
                fprintf(stderr, "Argument not recognized: %c\n", flags[i]);
                temp_proc = NULL;
                break;
        }

        if (temp_proc == NULL) continue;

        // assign context from argv[arg_index]
        char *ctx = NULL;
        if (arg_index < argc) {
            ctx = argv[arg_index];
            arg_index++;  // move to next context for next flag
        }

        process *next = malloc(sizeof(process));
        if (!next) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        next->next = NULL;
        next->process_file = temp_proc;
        next->ctx = ctx;

        add_process(&filters, next);
    }

    return filters;
}

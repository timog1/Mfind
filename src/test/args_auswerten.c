#include <stdio.h>
#include <stdlib.h>
#include "../../include/filters.h"
#include "../../include/processes.h"
#include "../../include/args_auswerten.h"

#include <string.h>

#include "../../include/fileinfo.h"

int main() {
    // -----------------------------
    // Simulate command line arguments
    // -----------------------------
    char *argv[] = {"./mfind", ".", "-sn", ">100B", "test*"};
    int argc = 5;

    process *filters = args_auswerten(argv, argc);

    if (!filters) {
        printf("✗ FAIL: args_auswerten returned NULL\n");
        return 1;
    }

    // -----------------------------
    // Check the first filter
    // -----------------------------
    if (filters->process_file == size_filter) {
        printf("✓ First filter is size_filter\n");
    } else {
        printf("✗ First filter is NOT size_filter\n");
    }

    if (filters->ctx && strcmp((char*)filters->ctx, ">100B") == 0) {
        printf("✓ First filter context is correct\n");
    } else {
        printf("✗ First filter context is incorrect\n");
    }

    // -----------------------------
    // Check the second filter
    // -----------------------------
    if (filters->next) {
        if (filters->next->process_file == name_filter) {
            printf("✓ Second filter is name_filter\n");
        } else {
            printf("✗ Second filter is NOT name_filter\n");
        }

        if (filters->next->ctx && strcmp((char*)filters->next->ctx, "test*") == 0) {
            printf("✓ Second filter context is correct\n");
        } else {
            printf("✗ Second filter context is incorrect\n");
        }
    } else {
        printf("✗ Second filter missing\n");
    }

    // -----------------------------
    // Cleanup
    // -----------------------------
    process *tmp;
    while (filters) {
        tmp = filters->next;
        free(filters);
        filters = tmp;
    }

    return 0;
}
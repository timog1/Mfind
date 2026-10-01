//
// Created by hi on 22.01.2026.
//
#include "../include/processes.h"

#include <stddef.h>

void add_process(process **chain, process *add) {
    if (*chain == NULL) {
        *chain = add;
        add->next = NULL;
        return;
    }

    process *temp = *chain;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = add;
    add->next = NULL;
}
int get_process(process *chain, int t, process *add) {
    process *temp = chain->next;

    while (t != 0) {
        if (temp->next == NULL) {
            return 0;
        }
        temp = temp->next;

        t--;
    }

    add = temp;
    return 1;
}
int get_next(process *chain, int t, process *add) {
   add = chain->next;
}
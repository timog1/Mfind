
#include <stdio.h>

#include <string.h>
#include "../include/fileinfo.h"
#include "../include/processes.h"
void stdinworker(process *f){
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        process *temp = f;
        FileInfo info;

        char *slash = strrchr(buffer, '/');
        if (slash)
            info.name = slash + 1;
        else
            info.name = buffer;
        while (1) {
            if (temp != NULL){
                if (temp->process_file != NULL) {
                    if (!temp->process_file(&info, temp->ctx)) {

                        break;
                    }
                }

                temp = temp->next;
            } else {
                printf("%s\n", buffer);
                break;
            }
        }

    }
}

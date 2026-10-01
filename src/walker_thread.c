#include <pthread.h>




#include "../include/walker.h"
#include "../include/fileinfo.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <limits.h>
#include "../include/processes.h"
#include "../include/Stream.h"
#include "../include/searchinfo.h"
#define PATH_MAX 4094
void *walk_directory_thread(void *args) {
    SearchInfo *si = (SearchInfo *)args;
    Stream *s = si->Stream;
    FileInfo fi;
    int working = 1;
    while (s->free == 0) {


        if (stream_pop(s, &fi)) {
            addworker(s);

            const char *path = fi.path;

            DIR *dir = opendir(path);
            if (!dir) {
                perror(path);
                free(fi.path); // free popped path if opendir fails
                continue;
            }

            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                    continue;

                char fullpath[PATH_MAX];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

                struct stat st;
                if (stat(fullpath, &st) != 0)
                    continue;

                char *p = malloc(strlen(fullpath) + 1);
                strcpy(p, fullpath);

                FileInfo info = { .path = p, .name = entry->d_name, .st = st };


                process *temp = *(si->first);


                int passed = 1;

                while (temp != NULL) {
                    if (temp->process_file != NULL) {
                        if (!temp->process_file(&info, temp->ctx)) {
                            passed = 0;
                            break;
                        }
                    }
                    temp = temp->next;
                }

                if (passed) {
                    printf("%s\n", info.path);
                }







                if (S_ISDIR(st.st_mode)) {

                    stream_push(s, info);
                } else {

                    free(p);
                }
            }

            closedir(dir);


            free(fi.path);
            removeworker(s);


        }

    }


  return NULL;
}


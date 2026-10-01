cmake_minimum_required(VERSION 3.10)
project(mfind C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(mfind
        src/main.c
        include/fileinfo.h
        include/walker.h
        src/filter.c
        include/filters.h
        include/filterinfo.h
        include/Stream.h
        src/Stream.c
        src/walker_thread.c
        include/searchinfo.h
        src/Filesize_filter.c
        include/processes.h
        src/processes.c
        src/mymatch.c
        include/mymatch.h
        src/search.c
        include/search.h
        src/stdin.c
        include/stdinworker.h
        src/args_auswertung.c
        include/args_auswerten.h


)
add_executable(mymatchtest
        src/test/mymatchtest.c
        include/mymatch.h
        include/search.h
        src/mymatch.c
        src/search.c
)
add_executable(argstest
        include/search.h
        src/search.c
        include/filters.h
        include/mymatch.h
        src/mymatch.c
        include/processes.h
        include/args_auswerten.h
        src/filter.c
        src/Filesize_filter.c
        src/processes.c
        src/args_auswertung.c
        src/test/args_auswerten.c
)
add_executable(filesize_filter_test
        src/search.c
        include/search.h
        include/filters.h
        src/mymatch.c
        include/mymatch.h
        src/filter.c
        src/Filesize_filter.c
        src/test/filesize_filter_test.c
        include/fileinfo.h

)






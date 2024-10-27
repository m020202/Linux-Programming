#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

void cmp(const char *, time_t);
struct stat sb;

int main(int argc, char **argv) {
    int i;
    time_t last_time[11];

    if (argc < 2) {
        fprintf(stderr, "failed");
        exit(0);
    }

    if (--argc > 10) {
        fprintf(stderr, "failed");
        exit(0);
    }

    for (i = 1; i < argc; ++i) {
        if (stat(argv[i], &sb) == -1) {
            fprintf(stderr, "failed");
            exit(0);
        }
        last_time[i] = sb.st_mtime;
    }

    for (;;) {
        for (i = 1; i < argc; ++i) {
            cmp(argv[i], last_time[i]);
        }
        sleep(60);
    }
}

void cmp(const char *path, time_t last) {
    if (stat(path, &sb) == -1 || sb.st_mtime != last) {
        fprintf(stderr, "failed");
        exit(1);
    }
}
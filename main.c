#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

#define MFILE 10

void cmp(const char *, time_t);
struct stat sb;

int main(int argc, char **argv) {
    int i;
    time_t last_time[MFILE + 1]; // 각 파일의 최근 수정 시간 기록

    if (argc < 2) {
        fprintf(stderr, "usage: lookout filename ... \n");
        exit(1);
    }

    if (--argc > MFILE){
        fprintf(stderr, "lookout: too many filenames\n");
        exit(1);
    }

    for (i = 1; i < argc; ++i) {
        if (stat(argv[i], &sb) == -1) {
            fprintf(stderr, "lookout: couldn't stat %s\n", argv[i]);
            exit(1);
        }
        last_time[i] = sb.st_mtime;
    }

    while (1) {
        for (i = 1; i < argc; ++i) {
            cmp(argv[i], last_time[i]);
        }
        sleep(60);
    }
}

void cmp(const char *path, time_t last) {
    if (stat(path, &sb) == -1 || sb.st_mtime != last) {
        fprintf(stderr, "lookout: %s changed\n", path);
        exit(0);
    }
}
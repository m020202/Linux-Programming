#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3)
        fprintf(stderr, "usage: move file1 file2\n");

    if (link(argv[1], argv[2]) == -1){
        perror("link failed");
        exit(1);
    }

    if (unlink(argv[1]) == -1) {
        perror("unlink failed");
        unlink(argv[2]);
        exit(1);
    }

    printf("Succeeded\n");

};
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <ulimit.h>

int main() {
    FILE *file;

    if (fopen("data.txt", "rb") != NULL)
        printf("YES");

    exit(0);
};
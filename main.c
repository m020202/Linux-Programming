#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int main() {
    struct stat sb;

    stat("data.txt", &sb);
    if (sb.st_mode & S_IRUSR) {
        printf("yes");
    }

    return 0;
}
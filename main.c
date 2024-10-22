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
    char *buf[512];
    symlink("data", "data3");
    printf("%d", readlink("data3", buf, 512));

    printf("%s", buf);
    return 0;
};
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
    ssize_t nread;
    char buf[512];

    while ((nread = read(0,buf, 512)) > 0)
        write(1, buf, nread);

    exit(0);
};
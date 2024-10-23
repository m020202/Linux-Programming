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
    int fd;
    ssize_t nread;
    char buf[512];

    fd = open("data", O_RDONLY);
    nread = read(fd, buf, 512);
    printf("%d", nread);

    close(fd);
};
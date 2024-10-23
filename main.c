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
    int fd = open("data.txt", O_RDWR);
    int newFd = fcntl(fd, F_DUPFD);

    printf("%d", newFd);

    close(fd);
};
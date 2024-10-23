#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <ulimit.h>

int fileStatus(int fd) {
    int arg1;

    if ((arg1 = fcntl(fd, F_GETFL)) == -1) {
        printf("file status failed\n");
        return -1;
    }

    switch (arg1 & O_ACCMODE) {
        case O_WRONLY:
            printf("WR");
            break;
        case O_RDONLY:
            printf("RD");
            break;
        case O_RDWR:
            printf("RDWR");
            break;
        default:
            printf("NO such mode");
    }

    if (arg1 & O_APPEND) {
        printf("-append flag set");
    }
}




int main() {
    int fd = open("data.txt", O_RDWR);

    fileStatus(fd);

    close(fd);
};
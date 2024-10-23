#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <ulimit.h>

int specialCreat(const char *path, mode_t mode) {
    mode_t oldU;
    int fd;

    if ((oldU = umask(0)) == -1) {
        perror("saving old mask: ");
        return -1;
    }

    if ((fd = open(path, O_WRONLY | O_CREAT | O_EXCL, mode)) == -1)
        perror("opening file");

    int num = umask(oldU);
    if (num == -1) {
        perror("resotring old mask");
    }
    else if (num == 0){
        printf("SUCCESS");
    }

    return fd;
}

int main() {
    specialCreat("data2.txt", 0666);

    exit(0);
};
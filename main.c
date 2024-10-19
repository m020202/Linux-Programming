#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>


int main() {
    struct statvfs buf;

    struct stat stat1;

    int fd = open("data2", O_RDONLY);

    printf("%d\n", fstatvfs(fd, &buf));

    printf("%d\n", fstat(fd, &stat1));

    return 0;
};
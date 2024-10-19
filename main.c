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

    printf("%d\n", statvfs("data2", &buf));

    printf("%d\n", stat("data2", &stat1));

    return 0;
};
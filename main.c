#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>


int main() {

    printf("%d\n", pathconf("data2", _PC_LINK_MAX));
    printf("%d\n", pathconf("data2", _PC_PATH_MAX));
    printf("%d\n", pathconf("data2", _PC_NAME_MAX));
    return 0;
};
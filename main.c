#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>


int main() {
    struct dirent dir;

    DIR *ptr;

    ptr = opendir("fortest");

    readdir(ptr);

    return 0;
};
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>


int main() {
    printf("%d", getpgrp());
    printf("%d", getpgid(1));

    return 0;
};
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int my_double_ls(const char *name) {
    struct dirent *d;
    DIR *dp;

    if ((dp = opendir(name)) == NULL) {
        return -1;
    }

    while (d = readdir(dp)) {
        if (d->d_ino != 0)
            printf("%s\n", d->d_name);
    }

    rewinddir(dp);

    while (d = readdir(dp)) {
        if (d->d_ino != 0)
            printf("%s\n", d->d_name);
    }

    closedir(dp);
    return 0;
}

int main() {
    my_double_ls("강의 자료");

    return 0;
}
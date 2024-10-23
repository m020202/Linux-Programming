#include <stdio.h>
#include <dirent.h>
#include <string.h>

int my_double_ls(const char *name) {
    DIR *dp;
    struct dirent *d;

    if ((dp = opendir(name)) == NULL)
        return -1;

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
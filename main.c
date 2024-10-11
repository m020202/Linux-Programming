#include <dirent.h>
#include <printf.h>

int main() {
    struct dirent *d;
    DIR *dp;

    if ((dp = opendir("강의 자료")) == NULL)
        return -1;

    while ((d=readdir(dp)) != NULL) {
        if (d->d_ino != 0)
            printf("%s \n", d->d_name);
    }

    rewinddir(dp);

    while ((d=readdir(dp)) != NULL) {
        if (d->d_ino != 0)
            printf("%s \n", d->d_name);
    }
    closedir(dp);

    return 0;
}
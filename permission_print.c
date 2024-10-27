#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>

int list(const char *name, const struct stat *status, int type) {
    if (type == FTW_NS)
        return 0;
    if (type == FTW_F)
        printf("%-30s\t0%3o\n", name, status->st_mode & 0777);
    else
        printf("%-30s*\t0%3o\n", name, status->st_mode & 0777);

    return 0;
}

int main(int argc, char **argv) {
    int list(const char *, const struct stat *, int type);
    if (argc == 1)
        ftw(".", list, 1);
    else
        ftw(argv[1], list, 1);

    return 0;
}
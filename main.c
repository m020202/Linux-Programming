#include <dirent.h>
#include <printf.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>

int list(const char *name, const struct stat *sptr, int type) {
    if (type == FTW_NS) {
        return 0;
    }
    if (type == FTW_F) {
        printf("%-30s\t0%3o\n", name, sptr->st_mode & 0777);
    }
    else
        printf("%-30s*\t0%3o\n", name, sptr->st_mode & 0777);

    return 0;
}

int main() {
    ftw(".", list, 1);
    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

static short octarray[9] = {
        0400, 0200, 0100,
        0040, 0020, 0010,
        0004, 0002, 0001
};

static char perms[10] = "rwxrwxrwx";

int fileData(const char *path) {
    struct stat buf;
    int i;
    char descrip[10];

    if (stat(path, &buf) == -1) {
        fprintf(stderr, "Couldn't stat %s\n", path);
        return -1;
    }

    for (i = 0; i < 9; ++i) {
        if (buf.st_mode & octarray[i])
            descrip[i] = perms[i];
        else
            descrip[i] = '-';
    }
    descrip[9] = '\0';

    printf("\nFile %s :\n", path);
    printf("Size %ld bytes\n", buf.st_size);
    printf("User-id %d, Group-id %d\n\n", buf.st_uid, buf.st_gid);
    printf("Permissions: %s\n", descrip);

    return 0;
}

int main() {
    fileData("data.txt");
};
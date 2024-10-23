#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <ulimit.h>

int main() {
    char *filename = "data.txt";
    if (access(filename, R_OK) == -1){
        fprintf(stderr, "User cannot read file %s\n", filename);
        exit(1);
    }

    printf("%s readable, proceeding\n", filename);

};
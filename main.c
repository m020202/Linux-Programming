#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

void printf1() {
    printf("printfunc\n");
}


int main() {
    printf("%d", atexit(printf1));

    execl("/bin/ls", "ls", "-l", (char *) NULL);

    return 0;
};
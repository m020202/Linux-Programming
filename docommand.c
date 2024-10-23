#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int docommand(char *command) {
    pid_t  pid;
    if ((pid = fork()) < 0)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, NULL);
        perror("execl");
        exit(1);
    }

    wait(0);
    return 0;
}

int main() {
    printf("%d", docommand("echo hello world"));

    return 0;
}

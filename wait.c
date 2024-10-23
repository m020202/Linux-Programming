#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status, exit_status;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork failed");
        return -1;
    }

    if (pid == 0) {
        sleep(4);
        exit(5);
    }

    if ((pid = wait(&status)) == -1) {
        perror("wait failed");
        exit(2);
    }

    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Exit status from %d was %d\n", pid, exit_status);
    }

    exit(0);
}
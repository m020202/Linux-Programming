#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"
#define MAXSIZE 64

int main(int argc, char **argv) {
    int fd;
    struct flock lock1, lock2;
    lock1.l_type = F_WRLCK;
    lock1.l_whence = SEEK_SET;
    lock1.l_len = 5;
    lock1.l_start = 0;

    lock2.l_type = F_WRLCK;
    lock2.l_whence = SEEK_SET;
    lock2.l_start = 5;
    lock2.l_len = 10;

    fd = open("hello", O_WRONLY);

    if (fcntl(fd, F_SETLKW, &lock1) == -1) {
        perror("A");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            if (fcntl(fd, F_SETLKW, &lock2) == -1) {
                perror("B");
            }
            if (fcntl(fd, F_SETLKW, &lock1) == -1) {
                perror("C");
            }
            exit(1);
    }
    sleep(5);
    if (fcntl(fd, F_SETLKW, &lock2) == -1) {
        perror("D");
        exit(1);
    }

    return 0;
}
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
    struct flock my_lock;
    my_lock.l_type = F_WRLCK;
    my_lock.l_start = 0;
    my_lock.l_len = 5;

    if ((fd = open("hello", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("Parent: lock recorded\n");

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            my_lock.l_len = 5;
            if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
                perror("fcntl");
                printf("child: locking\n");
                exit(1);
            }

            printf("child: locked and exiting\n");
            exit(1);
    }

    sleep(3);
    printf("parent: exiting\n");
    return 0;
}
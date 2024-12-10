#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"
#define MAXSIZE 64


int main(int argc, char** argv) {
    int fd;
    if ((fd = open("fifo", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    for (int i = 1; i < argc; ++i) {
        if (write(fd, argv[i], MAXSIZE) == -1) {
            perror("sender write");
            exit(1);
        }
    }

    return 0;
}
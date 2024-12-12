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
#define BUFSIZE 64

int main(int argc, char** argv) {
    int fd;

    if ((fd = open("fifo", O_WRONLY | O_NONBLOCK)) == -1) {
        perror("fifo");
        exit(1);
    }

    for (int i = 2; i < argc; ++i) {
        if (strlen(argv[i]) > BUFSIZE) {
            printf("too long\n");
            continue;
        }

        if (write(fd, argv[i], BUFSIZE) == -1) {
            perror("write");
            exit(1);
        }
    }

    return 0;
}
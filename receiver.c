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
    char buf[MAXSIZE];
    int fd;

    if (mkfifo("fifo", 0666) == -1) {
        perror("fifo");
        exit(1);
    }

    if ((fd = open("fifo", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    while(read(fd, buf, MAXSIZE) > 0) {
        printf("Message received: %s\n", buf);
    }

    return 0;
}
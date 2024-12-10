#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <setjmp.h>
#include "shared_memory.h"

void child(int p[2]) {
    close(p[0]);
    for (int i = 0; i < 3; ++i) {
        write(p[1], "hello!\n", 10);
        sleep(2);
    }

    write(p[1], "bye !!\n", 10);
    exit(1);
}

void parent(int p[2]) {
    close(p[1]);
    int nread;
    char buf[16];
    for (;;) {
        switch (nread = read(p[0], buf, 10)) {
            case -1:
                if (errno == EAGAIN) {
                    printf("EMPTY!!\n");
                    sleep(1);
                    break;
                }
                else {
                    printf("ERROR!\n");
                    exit(1);
                }
            case 0:
                printf("EOF !!\n");
                exit(1);
            default:
                printf("MSG= %s", buf);
        }
    }
}

int main() {
    int p[2];
    if (pipe(p) == -1) {
        perror("pipe");
        exit(1);
    }
    fcntl(p[0], F_SETFL, O_NONBLOCK);

    switch(fork()) {
        case -1:
            perror("fork()");
            exit(1);
        case 0:
            child(p);
        default:
            parent(p);
    }

    return 0;
}
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

#define MAXSIZE 6

void child(int p[2]) {
    close(p[0]);

    for (int i = 0; i < 2; ++i) {
        write(p[1], "hello", MAXSIZE);
        sleep(getpid() % 4);
    }

    write(p[1], "Bye!!", MAXSIZE);
    exit(0);
}

void parent(int p[3][2]) {
    fd_set readset, tmp;
    char buf[MAXSIZE], ch;
    FD_ZERO(&readset);
    FD_SET(0, &readset);
    for (int i = 0; i < 3; ++i) {
        close(p[i][1]);
        FD_SET(p[i][0], &readset);
    }

    while (tmp = readset, select(p[2][0] + 1, &tmp, NULL, NULL, NULL) > 0) {
        if (FD_ISSET(0, &tmp)) {
            printf("From standard input...: ");
            read(0, &ch, 1);
            printf("%c", ch);
        }

        for (int i = 0; i < 3; ++i) {
            if (FD_ISSET(p[i][0], &tmp)) {
                printf("Message From Child: %d\n", i);
                read(p[i][0], buf, MAXSIZE);
                printf("MSG= %s\n", buf);
            }
        }

        if (waitpid(-1, NULL, WNOHANG) == -1) return;
    }
}

int main() {
    int p[3][2];

    for (int i = 0; i < 3; ++i) {
        if (pipe(p[i]) == -1) {
            perror("pipe");
            exit(1);
        }
        switch (fork()) {
            case -1:
                perror("fork");
                exit(1);
            case 0:
                child(p[i]);
        }
    }
    parent(p);
    return 0;
}
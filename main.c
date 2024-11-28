#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define MSGSIZE 6

char *msg1 = "hello";
char *msg2 = "bye!!";

void parent(int p[3][2]) {
    char buf[MSGSIZE], ch;
    fd_set set, master;
    for (int i = 0; i < 3; ++i) close(p[i][1]); // 읽기만 하겠다.
    FD_ZERO(&master);
    FD_SET(0, &master);
    for (int i = 0; i < 3; ++i)
        FD_SET(p[i][0], &master);

    while(set = master, select(p[2][0] + 1, &set, NULL, NULL, NULL) > 0) {
        if (FD_ISSET(0, &set)) {
            printf("From standarad input...");
            read(0, &ch, 1);
            printf("%c\n", ch);
        }
        for (int i = 0; i < 3; ++i) {
            if (FD_ISSET(p[i][0], &set)) {
                if (read(p[i][0], buf, MSGSIZE) > 0) {
                    printf("Message from child %d\n", i);
                    printf("MSG = %s\n", buf);
                }
            }
        }
        if (waitpid(-1, NULL, WNOHANG) == -1) return;
    }
}

int child(int p[2]) {
    close(p[0]);
    for (int i = 0; i < 2; ++i) {
        write(p[1], msg1, MSGSIZE);
        sleep(getpid() % 4);
    }

    write(p[1], msg2, MSGSIZE);
    exit(1);
}

int main() {
    int p[3][2];
    for (int i = 0; i < 3; ++i) {
        if (pipe(p[i]) == -1)
            exit(1);
        switch (fork()) {
            case -1:
                exit(1);
            case 0:
                child(p[i]);
        }
    }
    parent(p);
    exit(0);
}
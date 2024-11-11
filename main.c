#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define MSGSIZE 6

int parent(int *);
int child(int *);

char *msg1 = "hello";
char *msg2 = "bye!!";

int main() {
    int p[2];
    if (pipe(p) == -1) {
        perror("pipe call");
        return 0;
    }
    if (fcntl(p[0], F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl call");
        return 0;
    }

    switch (fork()) {
        case -1:
            perror("fork call");
            exit(1);
        case 0:
            child(p);
        default:
            parent(p);
    }
    return 0;
}

int child(int p[2]) {
    int count;
    close(p[0]);
    for (count = 0; count < 3; count++) {
        write(p[1], msg1, MSGSIZE);
        sleep(3);
    }
    write(p[1], msg2, MSGSIZE);
    exit(0);
}

int parent(int p[2]) {
    int nread;
    char buf[MSGSIZE];
    close(p[1]);

    for(;;) {
        switch (nread = read(p[0], buf, MSGSIZE)) {
            case -1:
                if (errno == EAGAIN) {
                    printf("(pipe empty)\n");
                    sleep(1);
                    break;
                }
                else {
                    perror("read call");
                    exit(1);
                }
            case 0:
                printf("End of conversation\n");
                exit(0);
            default:
                printf("MSG=%s\n", buf);
        }
    }
}
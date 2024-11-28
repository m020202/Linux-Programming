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
char *msg2 = "bye";

int child(int p[2]) {
    int cnt;
    close(p[0]);
    for (cnt = 0; cnt < 3; ++cnt) {
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
                    perror("read call: ");
                    exit(1);
                }
            case 0:
                printf("End of Conversation\n");
                exit(0);
            default:
                printf("MSG=%s\n", buf);
        }
    }
}

int main() {
    int p[2];
    if (pipe(p) == -1)
        exit(0);
    if (fcntl(p[0], F_SETFL, O_NONBLOCK) == -1)
        exit(1);

    switch (fork()) {
        case -1:
            exit(1);
        case 0:
            child(p);
        default:
            parent(p);
    }
    return 0;
}
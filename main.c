#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define MSGSIZE 63
char *fifo = "fifo";
int main(int argc, char **argv) {
    int fd;
    char msgBuf[MSGSIZE + 1];

    if (mkfifo(fifo, 0644) == -1) {
        if (errno != EEXIST) return -1;
    }

    if ((fd = open(fifo, O_RDWR)) < 0)
        return -1;

    for (;;) {
        if (read(fd, msgBuf, MSGSIZE + 1) < 0)
            return -1;
        printf("message received %s\n", msgBuf);
    }
}

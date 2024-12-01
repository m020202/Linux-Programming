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

int main() {
    int fd;
    struct flock my_lock;

    my_lock.l_type = F_WRLCK;
    my_lock.l_whence = SEEK_SET;
    my_lock.l_start = 0;
    my_lock.l_len = 10;

    fd = open("hello", O_RDWR);

    if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
        perror("parent: locking");
        exit(1);
    }

    printf("parent: locked record\n");

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            my_lock.l_len = 5;
            if(fcntl(fd, F_SETLKW, &my_lock) == -1) {
                perror("child: locking");
                exit(1);
            }

            printf("child: locked and exiting\n");
            sleep(2);
            exit(0);
        default:
            sleep(2);
            printf("parent: exiting\n");
            close(fd);
            wait(NULL);
    }
}
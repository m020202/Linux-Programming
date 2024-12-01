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
    struct flock first_lock;
    first_lock.l_type = F_WRLCK;
    first_lock.l_whence = SEEK_SET;
    first_lock.l_start = 0;
    first_lock.l_len = 10;

    struct flock second_lock;
    second_lock.l_type = F_WRLCK;
    second_lock.l_whence = SEEK_SET;
    second_lock.l_start = 10;
    second_lock.l_len = 5;

    fd = open("hello", O_RDWR);

    if (fcntl(fd, F_SETLKW, &first_lock) == -1) {
        perror("A");
        return -1;
    }

    printf("A: lock succeeded (proc %d)\n", getpid());

    switch (fork()) {
        case -1:
            perror("fork error");
            return -2;
        case 0:
            if (fcntl(fd, F_SETLKW, &second_lock) == -1)
                perror("B");
            if (fcntl(fd, F_SETLKW, &first_lock) == -1)
                perror("C");
            printf("C: lock succeeded (proc %d)\n", getpid());
            return 0;
        default:
            printf("parent sleeping\n");
            sleep(5);
            if (fcntl(fd, F_SETLKW, &second_lock) == -1)
                perror("D");
            printf("D: lock succeeded (proc %d)\n", getpid());
            close(fd);
            wait(NULL);
    }

    return 0;
}
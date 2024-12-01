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
    my_lock.l_len = 0;

    if ((fd = open("hello", O_RDWR)) == -1) {
        perror("open error: ");
        return -1;
    }

    if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
        perror("lock error: ");
        close(fd);
        return -2;
    }

    printf("File locked completel\n");

    my_lock.l_type = F_UNLCK;
    my_lock.l_start = 50;
    my_lock.l_len = 20;

    if (fcntl(fd, F_SETLKW, &my_lock) == -1) {
        perror("lock error: ");
        close(fd);
        return -3;
    }

    printf("File locked From 0 to 50 and 70 to end\n");

    close(fd);
    return 0;
}
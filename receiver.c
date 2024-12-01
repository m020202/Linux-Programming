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
    struct flock my_lock, get_lock;

    my_lock.l_type = F_WRLCK;
    my_lock.l_whence = SEEK_SET;
    my_lock.l_start = 0;
    my_lock.l_len = 0;
    my_lock.l_pid = getpid();

    if ((fd = open("hello", O_RDWR)) == -1) {
        perror("open error: ");
        return -1;
    }

    if (fcntl(fd, F_SETLK, &my_lock) == -1) {
        perror("lock error: ");
        return -1;
    }

    printf("Cur locking pid: %d\n", my_lock.l_pid);
    sleep(5);

    return 0;
}
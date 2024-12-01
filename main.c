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

    switch (fork()) {
        case -1:
            perror("fork error: ");
            return -1;
        case 0:
            my_lock.l_len = 5;
            if (fcntl(fd, F_SETLK, &my_lock) == -1) {
                if (errno == EAGAIN || errno == EACCES) {
                    fcntl(fd, F_GETLK, &get_lock);
                    printf("record locked by %d\n", get_lock.l_pid);
                }
                else
                    perror("unexpected lock error");
            }
        default:
            wait(NULL);
    }
    return 0;
}
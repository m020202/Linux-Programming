#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>

int main() {
    int fd;
    pid_t pid;
    char buf[10];

    fd = open("data", O_RDONLY);
    read(fd, buf, 10);
    fcntl(fd, F_SETFD, 1);

    switch (pid = fork()) {
        case -1:
            perror("failed");
            break;
        case 0:
            execl("/bin/ls", "ls", "-l", NULL);
            break;
        default:
            wait(0);
            int res = fcntl(fd, F_GETFD, 0);
            printf("%d", res);
    }

    return 0;
};

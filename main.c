#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd1, fd2;
    if ((fd1=open("data", O_RDWR)) == -1)
        perror("fd1");

    fd2 = fcntl(fd1, F_DUPFD);
    printf("%d", fd2);
    return 0;
};

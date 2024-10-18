#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1, fd2;
    if ((fd1=open("data", O_RDONLY)) == -1)
        perror("fd1");
    if ((fd2 = open("data2", O_WRONLY | O_CREAT, 0644)) == -1)
        perror("fd2");

    dup2(fd1, fd2);
    printf("%d\n", lseek(fd2, 0, SEEK_CUR));

    char buf[512];
    read(fd1, buf, 10);
    printf("%d\n", lseek(fd2, 0, SEEK_CUR));
    return 0;
};

#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd1, arg;
    if ((fd1=open("data", O_WRONLY | O_APPEND)) == -1)
        perror("fd1");

    if ((arg = fcntl(fd1, F_GETFL)) == -1) {
        printf("File status failed\n");
        return -1;
    }

    switch (arg & O_ACCMODE) {
        case O_WRONLY:
            printf("write-only mode");
            break;
        case O_RDONLY:
            printf("read-only-mode");
            break;
        case O_RDWR:
            printf("read-write");
            break;
        default:
            printf("No such mode");
    }
    if (arg & O_APPEND)
        printf(" with append flag set");

    return 0;
};

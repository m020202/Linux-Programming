#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    fd = open("data", O_WRONLY | O_CREAT, 0644);
    printf("%d\n", lseek(fd, 0, SEEK_END));

    return 0;
};

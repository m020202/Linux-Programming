#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd;

    fd = open("data", O_WRONLY | O_CREAT, 0644);
    printf("%d\n", fd);

    fd = open("data", O_WRONLY | O_CREAT | O_EXCL, 0644);
    printf("%d\n", fd);

    fd = open("data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("%d\n", fd);

    return 0;
};

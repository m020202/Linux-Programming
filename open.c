#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int main() {
    int fd;
    ssize_t nread;
    char buf[1024];

    if ((fd = open("test.txt", O_WRONLY | O_CREAT)) == -1) {
        printf("에러 발생");
    }

    write(fd, buf, 1024);

    close(fd);

    return 0;
}

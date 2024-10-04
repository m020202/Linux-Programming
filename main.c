#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int main() {
    int fd = open("test", O_RDWR, 0644);

    int offset = lseek(fd, (off_t) 100, SEEK_CUR);
    offset = lseek(fd, (off_t) 10, SEEK_CUR);
    printf("%d", offset);

    return 0;
}
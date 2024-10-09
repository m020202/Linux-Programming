#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int main() {
    int fd;

    fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        printf("Opening %s failed test.txt");
        return -1;
    }
    else {
        printf("Before dup2()\n");
        dup2(fd,1); // 출력 파일과 test.txt 가 같은 file table entry 를 가리키게 된다.
        printf("After dup2()\n");
    }

    close(fd);

    return 0;
}



#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int filestatus(int filedes) {
    int arg1;

    if ((arg1 = fcntl(filedes, F_GETFL)) == -1) {
        printf("file status failed\n");
        return -1;
    }

    switch (arg1 & O_ACCMODE) {
        case O_WRONLY :
            printf("write - only");
            break;
        case O_RDWR:
            printf("read - write");
            break;
        case O_RDONLY:
            printf("read - only");
            break;
        default:
            printf("NO SUCH MODE");
    }

    if (arg1 & O_APPEND) {
        printf("-append flag set");
    }

    printf("\n");
    return 0;
}

int main() {
    int fd1;

    if ((fd1 = open("test.txt", O_RDONLY, 0644)) == -1) {
        printf("에러 발생");
        return -1;
    }

    int fd2 = dup(fd1);

    // 현재 fd1의 파일 포지션 체크
    int cur1 = lseek(fd1, (off_t) 0, SEEK_CUR);
    printf("%d\n", cur1);

    int cur2 = lseek(fd2, (off_t) 10, SEEK_SET);

    // fd3의 파일 포지션 이동 후, fd1의 파일 포지션 체크
    cur1 = lseek(fd1, (off_t) 0, SEEK_CUR);
    printf("%d\n", cur1);

    // 파일 상태 확인
    filestatus(fd1);

    close(fd1);
    close(fd2);

    return 0;
}



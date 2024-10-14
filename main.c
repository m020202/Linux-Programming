#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>

int printpos(const char* string, int filedes);

int main() {
    int fd;
    pid_t pid;
    char buf[10];

    fd = open("data", O_RDONLY);
    read(fd, buf, 10);
    printpos("Before fork", fd);

    switch (pid = fork()) {
        case -1:
            perror("fork failed");
            break;
        case 0:
            printpos("Child before read", fd);
            read(fd, buf, 10);
            break;
        default:
            wait(0);
            printpos("Parent after wait", fd);
    }
};

int printpos(const char* string, int filedes) {
    off_t pos;

    if ((pos = lseek(filedes, 0, SEEK_CUR)) == -1)
        perror("lseek failed");
    printf("%s:%d\n", string, pos);
}


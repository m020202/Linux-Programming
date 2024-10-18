#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

int main() {
    int fd;
    fd = open("data2", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    umask(022);
    struct stat file_stat;
    stat("data2", &file_stat);
    printf("new author: %03o\n", file_stat.st_mode & 0777);

    return 0;
};

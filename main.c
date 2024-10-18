#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int copyfile(const char *name1, const char *name2) {
    int infile, outfile;
    ssize_t nread;
    char buffer[512];

    if ((infile = open(name1, O_RDONLY)) == -1)
        return -1;
    if ((outfile = open(name2, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
        close(infile);
        return -2;
    }

    while ((nread = read(infile, buffer, 512)) > 0) {
        if ((write(outfile, buffer, nread)) < nread){
            close(infile);
            close(outfile);
            return -3;
        }
    }

    close(infile);
    close(outfile);
    if (nread == -1) return -4;
    else return 0;
}

int main() {
    int fd;
    ssize_t n1, n2, n3;
    char buf1[512], buf2[512], buf3[512];

    if ((fd = open("data", O_RDONLY, 0644)) == -1)
        return -1;

    n1 = read(fd, buf1, 512);
    printf("%d", n1);

    close(fd);

    return 0;
};

#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int copyfile(const char *name1, const char *name2) {
    int infile, outfile;
    ssize_t nread;
    char buffer[3];

    if ((infile = open(name1, O_RDONLY)) == -1)
        return -1;
    if ((outfile = open(name2, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        close(infile);
        return -2;
    }

    while ((nread = read(infile, buffer, 3)) > 0){
        if (write(outfile, buffer, nread) < nread) {
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
    copyfile("test", "test2.txt");
    int fd = open("test2.txt", O_RDWR);
    int size = lseek(fd, (off_t) 0, SEEK_END);
    printf("%d", size);
    return 0;
}
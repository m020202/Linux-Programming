#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <sys/mount.h>
#include <sys/statvfs.h>
#include <stdlib.h>
#include <ulimit.h>

int copyFile(const char *name1, const char *name2) {
    int infile, outfile;
    char buf[512];
    ssize_t nread;

    if ((infile = open(name1, O_RDONLY))) {
        return -1;
    }
    if ((outfile = open(name2, O_WRONLY | O_CREAT | O_TRUNC, 0644))) {
        close(infile);
        return -2;
    }

    while ((nread = read(infile, buf, 512)) > 0) {
        if (write(outfile, buf, nread) < nread) {
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

};
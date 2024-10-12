#include <dirent.h>
#include <printf.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>


int main() {
    printf("Current PID: %d\n", getpid());
    printf("Parent PID %d\n", getppid());

    return 0;
}


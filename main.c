#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>

void func1() { printf("printf func1\n"); }
void func2() { printf("printf fucn2\n"); }
void func3() { printf("printf func3\n"); }
void func4() { printf("printf func4\n"); }

int main() {
    pid_t pid;
    atexit(func1);
    atexit(func2);
    atexit(func3);
    atexit(func4);
    if ((pid = fork()) < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Child process is called\n");
        printf("Child process calls exit\n");
        exit(0);
    }
    wait(NULL);
    printf("Parent process calls exit\n");
    exit(0);
};

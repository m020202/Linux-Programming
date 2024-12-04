#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/msg.h>

#define SEMPERM 0600
#define TRUE 1
#define FALSE 0

typedef union _semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;
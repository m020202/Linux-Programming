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

#define SHMKEY1 (key_t) 0x10
#define SHMKEY2 (key_t) 0x15
#define SEMKEY (key_t) 0x20

#define SIZ 4*BUFSIZ

struct databuf {
    int d_read;
    char d_buf[SIZ];
};

typedef union _semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arr;
} semun;
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

#define SHM_INFO_COUNT 4

typedef struct _shm_info {
    char str_ip[40];
    unsigned int int_id;
    unsigned int int_ip;
} SHM_INFO;
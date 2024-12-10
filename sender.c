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
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"


int main(int argc, char** argv) {
    int msqid;
    struct msg_entry entry;


    if ((msqid = msgget((key_t) 3836, QPERM | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    entry.mtype = 1;
    strcpy(entry.mtext,"hello world");

    if (msgsnd(msqid, &entry, MAXLEN, IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}
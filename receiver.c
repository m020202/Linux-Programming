#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shared_memory.h"

int main(int argc, char **argv) {
    int msqid;

    if((msqid = msgget((key_t)3836, QPERM | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    struct msg_entry entry;
    int msglen;
    while((msglen = msgrcv(msqid, &entry, MAXLEN, 0, IPC_NOWAIT)) > 0) {
        printf("LEN: %d\n", msglen);
        printf("%s\n", entry.mtext);
    }

    return 0;
}
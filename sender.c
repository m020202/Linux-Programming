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
#include "msg_header.h"



int main() {
    key_t key;
    int msgid;
    struct msg_entry msg;

    if ((msgid = msgget(IPC_PRIVATE, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(0);
    }

    msg.mtype = 1;
    strcpy(msg.mtext, "message type $1\n");
    if (msgsnd(msgid, &msg, 100, IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}
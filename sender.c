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

    if ((msgid = msgget((key_t) 3836, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(0);
    }

    for (int i = 10; i > 0; i--) {
        msg.mtype = 1;
        char message[100];
        sprintf(message, "Message Type $%d\n", i);
        strcpy(msg.mtext, message);
        if(msgsnd(msgid, &msg, 100, IPC_NOWAIT) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }
    return 0;
}
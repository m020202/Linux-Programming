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
#include "msg_header.h"

int main() {
    key_t key;
    int msgid;
    struct msg_entry msg;
    int len;

    key = ftok("msg_header.h", 1);
    if ((msgid = msgget(key, IPC_CREAT | 0644)) == -1) {
        perror("msgget");
        exit(1);
    }

    while((len = msgrcv(msgid, &msg, 100, 0, 0)) > 0) {
        printf("Received Message = %s\n", msg.mtext);
    }

}
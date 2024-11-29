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

#define MAXLEN 100
#define QPERM 0644

struct msg_entry {
    long mtype;
    char mtext[MAXLEN];
};

int main() {
    key_t key;
    int msgid;
    struct msg_entry msg;
    int msglen;

    key = ftok("msg_header.h", 2);
    msgid = msgget(key, IPC_CREAT | QPERM);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while((msglen = msgrcv(msgid, &msg, MAXLEN, 0,0)) > 0) {
        printf("Received Message = %s\n", msg.mtext);
    }
    return 0;
}
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

    key = ftok("msg_header.h", 1);
    msgid = msgget(key, QPERM | IPC_CREAT);

    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    msg.mtype = 1;
    strcpy(msg.mtext, "message type 1\n");
    if (msgsnd(msgid, &msg, MAXLEN, IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}
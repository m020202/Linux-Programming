#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ 128

struct msgbuf{
    long mtype;
    char mtext[MSGSZ];
};

int main(int argc, char **argv) {
    key_t key = ftok("test", 65);
    int msqid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;

    message.mtype = 1;
    strcpy(message.mtext, "Hello World!");
    msgsnd(msqid, &message, sizeof(message.mtext), 0);
    printf("Message sent: %s \n", message.mtext);

    msgrcv(msqid, &message, sizeof(message.mtext), 1, 0);
    printf("Message received: %s\n", message.mtext);

    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}

//
// Created by zcw on 11/25/19.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX 1024
#define KEY 5678

struct mymsg{
    long int type;
    char text[50];
}msg;

void main() {
    pid_t pidse;
    pid_t pidre;
    int msgid;
    int i = 1;
    msgid = msgget(KEY, 0666 | IPC_CREAT);
    if ((pidse = fork()) == 0) {
        for (i = 0; i < 999; i ++) {
            scanf("%s", msg.text);
            msg.type = 1;
            if (strcmp(msg.text, "exit") == 0) {
                msg.type = -1;
                exit(0);
            }
            msgsnd(msgid, &msg, MAX, 0);
            printf("message %s has sent \n", msg.text);
        }
        exit(0);
    }
    else {
        i = 1;
        if ((pidre = fork()) == 0) {
            while (i != -1) {
                msgrcv(msgid, &msg, MAX, 0, 0);
                printf("Message is : %s\n", msg.text);
                i = msg.type;
            }
            exit(0);
        } else {
            wait(0);
            wait(0);
            exit(0);
        }
    }
}
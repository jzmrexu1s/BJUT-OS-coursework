//
// Created by zcw on 11/18/19.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    pid_t pid0, pid1;
    int fd[2];
    // Create pipe
    pipe(fd);
    char buf[100];
    // Create child process 0
    pid0 = fork();
    // Child 0 goes here
    if (pid0 == 0) {
        for (int i = 0; i < 1000; i ++) {
            printf("b");
        }
        exit(0);
    }
    else if (pid0 < 0) {
        printf("Fork error");
        exit(1);
    }
    else {
        wait(NULL);
        // Create child process 1
        pid1 = fork();
        // Child 1 goes here
        if (pid1 == 0) {
            for (int i = 0; i < 1000; i ++) {
                printf("c");
            }
            exit(0);
        }
        else if (pid1 < 0) {
            printf("Fork error");
            exit(1);
        }
            // In father process
        else {
            wait(NULL);
            for (int i = 0; i < 1000; i ++) {
                printf("a");
            }
        }
    }
    return 0;
}


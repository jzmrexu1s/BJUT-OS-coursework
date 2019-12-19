//
// Created by zcw on 11/18/19.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("In child 1: \n");
        close(fd[0]);
        char s[] = "Child 1 is sending a message!\n";
        write(fd[1], s, strlen(s));
        exit(0);
    }
    else if (pid0 < 0) {
        printf("Fork error");
        exit(1);
    }
    else {
        // Create child process 1
        pid1 = fork();
        // Child 1 goes here
        if (pid1 == 0) {
            printf("In child 2: \n");
            close(fd[0]);
            char s[] = "Child 2 is sending a message!\n";
            write(fd[1], s, strlen(s));
            exit(0);
        }
        else if (pid1 < 0) {
            printf("Fork error");
            exit(1);
        }
        // Read in father process
        else {
            printf("In parent: \n");
            for (int i = 0; i < 2; i ++) {
                close(fd[1]);
                read(fd[0], buf, sizeof(buf));
                printf("message: %s", buf);
            }
        }
    }
    return 0;
}

//
// Created by zcw on 11/18/19.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void myThread1() {
    printf("Printing in pthread 1. \n");
}

void myThread2() {
    printf("Printing in pthread 2. \n");
}
int main() {
    int r1, r2;
    pthread_t t1, t2;
    r1 = pthread_create(&t1, NULL, (void*)myThread1, NULL);
    if (r1 != 0) {
        printf("Error occurs when creating pthread1. \n");
        exit(1);
    }
    r2 = pthread_create(&t2, NULL, (void*)myThread2, NULL);
    if (r2 != 0) {
        printf("Error occurs when creating pthread2. \n");
        exit(1);
    }
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

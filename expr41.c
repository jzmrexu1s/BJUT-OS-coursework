//
// Created by zcw on 11/18/19.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t n;
sem_t s;
sem_t e;
sem_t add;
sem_t mul;
sem_t d1;
sem_t d2;
// Writing position
int wr_pt = 0;
// Allow operate
int rd_pt = 0;//int o1_count = 0;
//int o2_count = 0;

int slot[2] = {0, 0};
int count = 0;


void *r1f(FILE* f) {
    // write
    int num;
    while (fscanf(f, "%d ", &num) != EOF) {
        // put in queue
        sem_wait(&d1);
        sem_wait(&e);
        sem_wait(&s);
        // Write to slot
        slot[wr_pt] = num;
        if (wr_pt == 0) {
            wr_pt = 1;
        }
        else{
            wr_pt = 0;
        }
        // release from queue
        sem_post(&s);
        sem_post(&n);
        sem_post(&d2);
    }
}

void *r2f(FILE* f) {
    // write
    int num;
    while (fscanf(f, "%d ", &num) != EOF) {
        // put in queue
        sem_wait(&d2);
        sem_wait(&e);
        sem_wait(&s);
        // Write to slot
        slot[wr_pt] = num;
        if (wr_pt == 0) {
            wr_pt = 1;
        }
        else {
            wr_pt = 0;
        }
        // release from queue
        sem_post(&s);
        sem_post(&n);
        sem_post(&d1);
    }
}

void *o1f() {
    // add (operate)
    int nums1[2];
    int o1_count = 0;
    while (count < 10) {
        // put in queue
        sem_wait(&add);
        sem_wait(&n);
        sem_wait(&s);
        nums1[0] = slot[0];
        sem_post(&s);
        sem_post(&e);

        sem_wait(&n);
        sem_wait(&s);
        nums1[1] = slot[1];

        printf("%d + %d = %d \n", nums1[0], nums1[1], nums1[0] + nums1[1]);
        count += 1;
        sem_post(&s);
        sem_post(&e);
        sem_post(&mul);


    }
    exit(0);
}

void *o2f() {
    int o2_count = 0;
    // multiply (operate)
    int nums2[2];
    while (count < 10) {
        // put in queue
        sem_wait(&mul);
        sem_wait(&n);
        sem_wait(&s);
        nums2[0] = slot[0];
        sem_post(&s);
        sem_post(&e);

        sem_wait(&n);
        sem_wait(&s);
        nums2[1] = slot[1];
        printf("%d * %d = %d \n", nums2[0], nums2[1], nums2[0] * nums2[1]);
        count += 1;
        sem_post(&s);
        sem_post(&e);
        sem_post(&add);

    }
    exit(0);
}

int main() {
    int r1, r2, o1, o2;
    pthread_t read1, read2, operate1, operate2;

    // n: prevent fetching from empty slot.
    sem_init(&n, 0, 0);
    // e: prevent put into full slot.
    sem_init(&e, 0, 2);
    // s: only one thread can visit the slot at the same time.
    sem_init(&s, 0, 1);

    sem_init(&add, 0, 1);
    sem_init(&mul, 0, 0);
    sem_init(&d1, 0, 1);
    sem_init(&d2, 0, 0);

    // read from file
    FILE *f1;
    FILE *f2;
    f1 = fopen("/home/zcw/CLionProjects/os/data1.txt", "r");
    f2 = fopen("/home/zcw/CLionProjects/os/data2.txt", "r");
    r1 = pthread_create(&read1, NULL, r1f, f1);
    if (r1 != 0) {
        printf("Error occurs when creating read1. \n");
        exit(1);
    }
    r2 = pthread_create(&read2, NULL, r2f, f2);
    if (r2 != 0) {
        printf("Error occurs when creating read2. \n");
        exit(1);
    }
    o1 = pthread_create(&operate1, NULL, o1f, NULL);
    if (o1 != 0) {
        printf("Error occurs when creating operate1. \n");
        exit(1);
    }
    o2 = pthread_create(&operate2, NULL, o2f, NULL);
    if (o2 != 0) {
        printf("Error occurs when creating operate2. \n");
        exit(1);
    }
    pthread_join(read1, NULL);
    pthread_join(read2, NULL);
    pthread_join(operate1, NULL);
    pthread_join(operate2, NULL);
    fclose(f1);
    fclose(f2);
    return 0;
}


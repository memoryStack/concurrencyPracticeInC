#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define THREAD_NUM 8

pthread_mutex_t fuelLock, waterLock;
int fuel = 50, water = 10;

void* routine(void* args) {
    
    if (rand()%2 == 0) {
        pthread_mutex_lock(&fuelLock);
        printf("got fuel lock\n");
        sleep(1);
        printf("trying to get water lock\n");
        pthread_mutex_lock(&waterLock);
        printf("got water lock\n");
    } else {
        pthread_mutex_lock(&waterLock);
        printf("got water lock\n");
        sleep(1);
        printf("trying to get fuel lock\n");
        pthread_mutex_lock(&fuelLock);
        printf("got fuel lock\n");
    }

    fuel += 50;
    water = fuel;
    printf("fuel: %d, water: %d\n", fuel, water);
    
    pthread_mutex_unlock(&fuelLock);
    pthread_mutex_unlock(&waterLock);
    return NULL;    
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    
    pthread_mutex_init(&fuelLock , NULL);
    pthread_mutex_init(&waterLock , NULL);
    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    printf("fuel: %d, water: %d\n", fuel, water);

    pthread_mutex_destroy(&fuelLock);
    pthread_mutex_destroy(&waterLock);
    return 0;
}

/*
    simple demonstration of deadlock.
    here threads would make a cycle on holding and waiting for locks.
    Note: for posix threads created by pthread.h library if we try to hold a lock
        multiple times then we would hit deadlock because a posix thread doesn't know 
        if it has the lock or not on which it is trying to get.
*/

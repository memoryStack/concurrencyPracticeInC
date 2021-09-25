#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int count = 0;
pthread_mutex_t mx;

void *func() {
    for(int i=0;i<1000000;i++) {
        pthread_mutex_lock(&mx);
        count++;
        pthread_mutex_unlock(&mx);
    }
}

int main(int argc, char *argv[]) {

    pthread_t threads[4];
    pthread_mutex_init(&mx, NULL);
    
    for(int i=0;i<4;i++){
        pthread_create(threads + i, NULL, &func, NULL);
    }

    // common mistake -> don't put the join instruction in the above for loop
    // because then the threads will be created and executed in sequential order
    // rather than concurrent
    for(int i=0;i<4;i++){
        pthread_join(threads[i], NULL);
    }

    printf("count is %d\n", count);

    return 0;
}

/*
    Learning TODOs: 
        1. find out how main threads wait/suspend it's execution when it calls 
            "join" on it's threads or calls "wait" or "sleep".
            wht is going on underneath.
*/

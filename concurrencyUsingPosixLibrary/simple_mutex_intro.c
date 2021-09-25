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
    pthread_t t1, t2, t3, t4;
    
    pthread_mutex_init(&mx, NULL);
    pthread_create(&t1, NULL, &func, NULL);
    pthread_create(&t2, NULL, &func, NULL);
    pthread_create(&t3, NULL, &func, NULL);
    pthread_create(&t4, NULL, &func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("count is %d\n", count);

    return 0;
}

/*
    Learning TODOs:
        1. understand how "lock" and "unlock" funcs are implemented to wait/sleep
            until the lock is released by other thread.
    
    Questions:
        1. looks like acquiring and releasing the lock is pretty expensive.
            can i benchmark this and compare it with the incorrect verrsion of this ?
*/

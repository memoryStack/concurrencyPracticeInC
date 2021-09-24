#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int count = 0;
pthread_mutex_t mx;

void *func() {
    sleep(1);
    printf("finished execution\n");
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t th[2];
    for(int i=0;i<2;i++){
        if (pthread_create(th+i, NULL, &func, NULL) != 0) {
            printf("failed to create thread\n");
        }
        pthread_detach(th[i]);
    }

    for(int i=0;i<2;i++){
        if(pthread_join(th[i], NULL)){
            // detached threads are not joinable. so we will get error at this point
            printf("failed to join the thread\n");
        }
    }

    pthread_exit(0);
    return 0;
}

/*
    we can detach the thread from the main process/thread.
    detached threads are not joinable. detached threads will clear their resources on their own.
    normal threads clear their resourses when pthread_join is successfully called upon them by main thread.
    ways to detach threads:
        1. create a attached thread and then detach it
        2. create a deattached thread directly only
*/

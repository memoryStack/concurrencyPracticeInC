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
    pthread_attr_t detachedThread;
    pthread_attr_init(&detachedThread);
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);

    for(int i=0;i<2;i++){
        if (pthread_create(th+i, &detachedThread, &func, NULL) != 0) {
            printf("failed to create thread\n");
        }
        pthread_detach(th[i]);
    }

    // it won't do anything. so let's ignore the below loop
    // for(int i=0;i<2;i++){
    //     if(pthread_join(th[i], NULL)){
    //         // detached threads are not joinable. so we will get error at this point
    //         printf("failed to join the thread\n");
    //     }
    // }

    pthread_attr_destroy(&detachedThread);
    pthread_exit(0);
    return 0;
}

/*
    we can detach the thread from the main process/thread.
    detached threads are not joinable. detached threads will clear their resources on their own.
    normal threads clear their resourses when pthread_join is successfully called upon them by main thread.
    ways to detach threads:
        1. create a attached thread and then detach it
        2. create a deattached thread directly only. this is done by using pthread_attr_t object

    TODO: learn more about the pthread_attr_t attributes which might help in optimizing the
            threads in some other desired way.
    
    Detached vs Joinable threads
        1. Create a detached thread when you know you won't want to wait for it with pthread_join().
            The only performance benefit is that when a detached thread terminates, its resources can be
            released immediately instead of having to wait for the thread to be joined before the resources can be released.
        2. It is 'legal' not to join a joinable thread; but it is not usually advisable because (as previously noted) 
            the resources won't be released until the thread is joined, so they'll remain tied up indefinitely (until the 
            program exits) if you don't join it.



*/

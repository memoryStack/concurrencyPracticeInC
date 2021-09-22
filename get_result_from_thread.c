#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int count = 0;
pthread_mutex_t mx;

void *func() {
    /*
        NOTE: never ever return reference to the local stack variable
            always return reference using the malloc.
    */
    int *result = malloc(sizeof(int));
    *result = 5;
    return (void *) result;
}

int main(int argc, char *argv[]) {

    pthread_t t1;

    pthread_create(&t1, NULL, &func, NULL);

    int* threadResult;
    pthread_join(t1, (void **) &threadResult);

    printf("thread produced result is %d\n", *threadResult);

    free(threadResult);

    return 0;
}

/*
    Exercise: here it took me around 1.5 hours to understand why pthread_join requires (void**)
        instead of just void* or single pointer. i am not writing anything here about it right now.
        let's come back to this later and see if i can remember/understand it on my own without using docs
    Note: here is a caveat, we are using "malloc" in func function and using "free"
        in main function which is not quite right from the design point of view. usually 
        malloc and free should be used in the same function. problem might occur because
        here we are trusting that the value "threadResult" holds is an address returned by malloc.
*/

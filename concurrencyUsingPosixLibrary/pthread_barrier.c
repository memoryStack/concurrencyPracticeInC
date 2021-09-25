#define _XOPEN_SOURCE 600 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// TODO: the linked pthread library can't identify the "pthread_barrier_t"
// maybe some other implementation of this library has it
// so skipping this for now. but will get back to this later
pthread_barrier_t barrier;

void* routine(void* args) {

}

int main(int argc, char *argv[]) {
	
	return 0;
}

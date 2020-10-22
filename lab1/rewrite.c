/*# Matthew Tolosa 
# Date: <9/25/20> (Friday: 2:15-5) 
# Title: Lab1 – Unix/Linux Commands & Overview of C 
# Description: This program shows a sample C program that goes through two processes */ 


/*(Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h> /*pthread*/
 

#define numThreads 2 
pthread_t threads[numThreads];

void *threadProcess(void *arg){
	int i, n; 
	n = (int)arg;
	for (i = 0; i<100; i++){
		printf("Thread with ID %d is printing iteration number %d\n", (int) pthread_self, i); //print the ID of the thread and what iteration it is on currently. 
		usleep(n);
	}
	return 0;
}

/* main function with command-line arguments to pass */

int main(int argc, char *argv[]) {
    int i, n; 
    n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking threads.\n");
    for (i = 0; i < numThreads; i++){ //iterate 2 times, since numThreads = 2
	pthread_create(&threads[i], NULL, threadProcess, (void *)(size_t)n);
    }
	
    for (i = 0; i < numThreads; i++){
	pthread_join(threads[i], NULL);
    }
} 






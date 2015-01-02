/***************************************************************************
 * Name:          John Curley 
 * Pawprint:      jmcgdd
 * Course:         CS 4520
 * Assignment#:    Lab 5
 *
 * File name:      CurleyLab5.c
 *
 * Question no:	   Programming project 3        
 *
 * Assumptions:    1) Let producer generate numbers between 0 and 100 only
 *		&		   2) Run the final program for 5 seconds with 2 producers 
 *	Precautions		  and 5 consumers 
 **************************************************************************/
#include "buffer.h"
buffer_item buffer[BUFFER_SIZE];
int inx = 0;
int outx = 0;
pthread_mutex_t mutexLock;
sem_t sem_empty;
sem_t sem_full;

//insert_item function
int insert_item(buffer_item item) {

	sem_wait(&sem_empty);
	pthread_mutex_lock(&mutexLock);
	
	//critical section
	buffer[inx] = item;
	inx = (inx+1)%BUFFER_SIZE;
	
	pthread_mutex_unlock(&mutexLock);
	sem_post(&sem_full);
	return 0;
		
}
//remove_item function
int remove_item(buffer_item *item) {
	sem_wait(&sem_full);
	pthread_mutex_lock(&mutexLock);
	
	//critical section
	if(outx >= 0){
		*item = buffer[outx];
		buffer[outx] = -1;
		outx = (outx+1)%BUFFER_SIZE;
	}
	else{
		return -1;
	}
	
	pthread_mutex_unlock(&mutexLock);
	sem_post(&sem_empty);
	return 0;
}
//producer thread function
void *producer(void *param) {
	buffer_item item;
	//infinite producer loop with built in deadlock prevention via insert_item
	while (1) {
		sleep(2);
		item = rand()%101;
		if (insert_item(item))
			printf("Error");
		else
			printf("Producer produced %d\n", item);
	}
		
	pthread_exit(0);
	return NULL;
}
//consumer thread function
void *consumer(void *param) {
	buffer_item item;
	//infinite consumer loop with built in deadlock prevention via remove_item
	while (1) {
		sleep(2);
		if (remove_item(&item))
			printf("Error");
		else
			printf("Consumer consumed %d\n", item);
	}
	
	pthread_exit(0);
	return NULL;
}
//main
int main(int argc, char *argv[]) {
	//Check to make sure correct number of command line inputs
	if(argc != 4){
		printf("\nError: must be exactly 3 command line inputs (# seconds to sleep, # producer threads, # consumer threads). Terminating program.\n");
		return -1;
	}
	
	//buffer initialization 
	buffer_item buff[BUFFER_SIZE];
	
	//mutex and semaphore initialization
	if(pthread_mutex_init(&mutexLock, NULL) != 0) {
		printf("\nSomething went wrong with the mutex initialization. Terminating.\n");
		return -1;
	}
	
	if(sem_init(&sem_empty, 0, BUFFER_SIZE) != 0) {
		printf("\nSomething went wrong with the empty semaphore initialization. Terminating.\n");
		return -1;
	}
	
	if(sem_init(&sem_full, 0, 0) != 0) {
		printf("\nSomething went wrong with the full semaphore initialization. Terminating.\n");
		return -1;
	}
	//Create producer threads
	int dummyInt = 0;
	int threadErr;
	int numProd = atoi(argv[2]);
	int numCons = atoi(argv[3]);
	pthread_t tid_p[numProd];
	pthread_attr_t attr_p;
	int i;
	
	//Create producer threads
	for(i=0;i<numProd;i++){
		//initialize attributes of pthread to default
		pthread_attr_init(&attr_p);
		//create pthread
		threadErr = pthread_create(&(tid_p[i]), &attr_p, producer, &dummyInt);
		if(threadErr != 0) {
			printf("\nThread could not be created. Terminating.\n");
			return -1;
		}
	}
	
	pthread_t tid_c[numCons];
	pthread_attr_t attr_c;
	int j;
	
	
	//Create consumer threads
	for(j=0;j<numCons;j++){
		//initialize attributes of pthread to default
		pthread_attr_init(&attr_c);
		//create pthread
		threadErr = pthread_create(&(tid_c[j]), &attr_c, consumer, &dummyInt);
		if(threadErr != 0) {
			printf("\nThread could not be created. Terminating.\n");
			return -1;
		}
	}
	
	//sleep for command line specified amount of time
	sleep(atoi(argv[1]));
	
	//After sleep, destroy locks and terminate program
	pthread_mutex_destroy(&mutexLock);
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	
	return 1;
	
}
/***************************************************************************
 * Name:          John Curley 
 * Userid:         jmcgdd/16013276
 * Course:         CS 4520
 * Assignment#:    Lab 4
 *
 * File name:      lb4_template.c
 *
 * Question no:	   5.37        
 *
 * Assumptions:    1) Which data is involved in race condition ?
 *		&		   2) When does the race condition occur ? 
 *	Precautions	   3) MAX_RESOURCES should defines the max number of resources
 * 				   4) NUM_PROCESSES should defines the no of threads to create
 *				   5) cc -pthread -lpthread lb5.c
 *				   6) Check instructions doc for additional instructions
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PROCESSES 10

#define MAX_RESOURCES 7

//global variable declaration for available_resources
int available_resources = MAX_RESOURCES;

//other global declarations
pthread_mutex_t mutexLock;
//function that thread runs
void *resourceFunc(void *param) {
	static randResourceNum;
	//lock critical section as soon as it is entered by a thread
	pthread_mutex_lock(&mutexLock);
	
	randResourceNum = rand()%(MAX_RESOURCES+1);
	decrease_count(randResourceNum);
	sleep(rand()%5);
	increase_count(randResourceNum);
	
	//unlock critical section as soon as current thread is done using it
	pthread_mutex_unlock(&mutexLock);
	
	pthread_exit(0);
}
//increase_count function
int increase_count(int count) {
	available_resources += count;
	printf("%d resources released and the available resources are : %d\n", count, available_resources);
	return 0;
}
//decrease_count function
int decrease_count(int count) {
	if (available_resources < count)
		return -1;
	else {
		available_resources -= count;
		printf("Request made for %d resources and the available resources are now : %d\n", count, available_resources);
		return 0;
	}
}
//main
int main(void) {
	pthread_t tid[NUM_PROCESSES];
	pthread_attr_t attr;
	int threadErr;
	int i;
	int dummyInt = 0;
	
	if(pthread_mutex_init(&mutexLock, NULL) != 0) {
		printf("\nSomething went wrong with the mutex initialization. Terminating.\n");
		return -1;
	}
	
	for(i=0;i<NUM_PROCESSES;i++){
		//initialize attributes of pthread to default
		pthread_attr_init(&attr);
		//create pthread
		threadErr = pthread_create(&(tid[i]), &attr, resourceFunc, &dummyInt);
		if(threadErr != 0) {
			printf("\nThread could not be created. Terminating.\n");
			return -1;
		}
	}
	
	for(i=0;i<NUM_PROCESSES;i++){
		pthread_join((tid[i]), NULL);
	}
	
	pthread_mutex_destroy(&mutexLock);
	
	printf("Available resources are: %d\n", available_resources);
	
	return 1;
}
	
/***************************************************************************
 * Name:           John Curley
 * Pawprint:       jmcgdd
 * Course:         CS 4520
 * Assignment#:    Lab 3
 *
 * File name:      lb3_template.c
 *
 * Question no:	   4.26        
 *
 * Assumptions:    1) compile & link with cc -pthread -lpthread lb4.c
 *		&		   2) Have an array to store max of 50 numbers
 * Precautions	   3)
 * 				   4)
 *				   5) 
 **************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 50

//define global variable
int *fibArray;

//define function that the thread runs
void *fibCalc(void *param);

//define main
int main(int argc, char **argv)
{
	fibArray = malloc(sizeof(int)*MAX_SIZE);
	pthread_t tid;
	pthread_attr_t attr;
	int inNum;
	int i;
	
	//Check to make sure correct number of command line inputs
	if(argc != 2){
		printf("\nError: must be exactly one command line input. Terminating program.\n");
		return -1;
	}
	
	inNum = atoi(argv[1]);
	
	//Check for failed atoi conversion
	if(!inNum){
		printf("\nError, command line input not recognized as or converted to a number. Or is 0\n\n");
		return -1;
	}
	
	//Check for negative input
	if(inNum < 0){
		printf("\nError, command line input number must be positive.\n\n");
		return -1;
	}
	
	//Check for input over 50
	
	//initialzie thread attributes to default
	pthread_attr_init(&attr);
	//Create the thread
	pthread_create(&tid, &attr, fibCalc, &inNum);
	//Wait for thread to finish
	pthread_join(tid, NULL);
	//Print the results from thread
	printf("\nFibonacci: ");
	for(i=0; i<inNum; i++){
		printf("%d ", fibArray[i]);
	}
	printf("\n");
	return 0;
}
//Thread function to place specific length of fibonacci sequence into global array
void *fibCalc(void *param)
{
	int i;
	int *arrayNum = param;
	//If input is 1, just place 1 into array
	if(*arrayNum == 1){
		fibArray[0] = 1;
		pthread_exit(0);
	}
	//Perform fibonacci sequence
	else{
		fibArray[0] = 1;
		fibArray[1] = 1;
		for(i=2; i<*arrayNum; i++){
			fibArray[i] = fibArray[i-2] + fibArray[i-1];
		}
		pthread_exit(0);
	}
}
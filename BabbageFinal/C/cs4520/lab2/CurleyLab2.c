/***************************************************************************
 * Name:			John Curley      
 * Userid:			jmcgdd       
 * Course:         CS 4520
 * Assignment#:    Assignment 2
 *
 * File name:      CurleyLab2.c
 *
 * Question no:	   3.22        
 *
 * Assumptions:    1) Link with -lrt when compiling
 *		&		   2)
 * Precautions	   3)
 * 				   4)
 *				   5) 
 **************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MAX_SIZE 100
int main(int argc, char **argv)
{
	//initializations
	int inNum;
	int *numAddr;
	int *numArray = malloc(sizeof(int)*MAX_SIZE);
	int fd;
	char *memName = "jmcgdd";
	int ftruncCheck;
	pid_t pid;
	
	//error checks
	if(argc != 2){
		printf("\nError, must have exactly one command line input.\n\n");
		return 1;
	}
	
	//Convert input to integer
	inNum=atoi(argv[1]);
	
	//Check for failed atoi conversion
	if(!inNum){
		printf("\nError, command line input not recognized as or converted to a number.\n\n");
		return 1;
	}
	
	//Check for negative input
	if(inNum < 0){
		printf("\nError, command line input number must be positive.\n\n");
		return 1;
	}
	
	//create a shared memory segment, fill the parameters
    fd = shm_open(memName, O_CREAT | O_RDWR, S_IRWXU);
	//check if shared memory segment is created successfully
	if(fd < 0){
		printf("\nError creating shared memory segment: [%s]\n\n",strerror(errno));
		shm_unlink(memName);
		return 1;
	}
	
	//allocate page size and check for errors, fill the parameters
    ftruncCheck = ftruncate(fd, sizeof(*numArray));
	if(ftruncCheck == -1){
		printf("\nError has occurred with ftruncate(): [%s]\n",strerror(errno));
	}
	//retrieve the address of shared memory segment, fill the parameters
    numArray = mmap(0 ,sizeof(*numArray), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	*numArray = inNum;
	
	//check if address valid
	if(numArray == NULL){
		printf("\nError has occurred with address of shared memory location. Terminating program. \n\n");
		shm_unlink(memName);
		return 1;
	}
	
	//create child process and write rest of the logic
    pid = fork();
	
	//pid should never be less than 0, error
	if(pid < 0){
		printf("\nError has occurred with ftruncate(): [%s]\n",strerror(errno));
		shm_unlink(memName);
		return 1;
	}
	//child process when pid = 0
	else if(pid == 0){
		int i = 0;
		//logic for Collatz conjecture
		while(*(numArray + i) != 1){
			if((*(numArray + i))%2 == 0){
				*(numArray + i + 1) = *(numArray + i)/2;
			}
			else{
				*(numArray + i + 1) = (3*(*(numArray + i))) + 1;
			}
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	//parent process for pid > 0
	else{
		wait(NULL);
		int i = 0;
		printf("\nCollatz result:");
		while(*(numArray + i) != 1){
			printf(" %d", *(numArray + i));
			i++;
		}
		printf(" %d\n\n", *(numArray + i));
	}
	
	//ensure you use this statement at each place your program exits
    shm_unlink(memName);
    return 0;
}

/********************************************************************************
 * Name:           John Curley
 * pawprint:        jmcgdd 
 * Course:         CS 4520
 * Assignment#:    Project
 *
 * File name:      consumer.c
 *
 * Question no:	   
 *
 * Assumptions:    1)
 *		&		   2)  
 * Precautions		  
 *********************************************************************************/

#include "project.h"


/* Global variables for consumer.c  */
   sem_t *MUTEXptr;   /* pointer to the MUTEX semaphore */
   sem_t *EMPTYptr;   /* pointer to the EMPTY semaphore */
   sem_t *FULLptr;    /* pointer to the FULL semaphore  */
   shr_mem_t *sp;     /* pointer to shared memory structure */
   static int sentFlag = 0;
  


/*******************************************************************/
/* Function to cleanup before exiting                              */
/*******************************************************************/
void cleanup_on_exit()
{
/* Only detach shared memory.  Parent will remove it from system */
/* Don't worry about semaphores.  Parent will delete them */
	shm_unlink("jmcgdd");

/* Clean up and exit */
    munmap(&sp,sizeof(shr_mem_t));
	return;
}


/**************************************************************************/
/* Function to be invoked by the OS if CTRL-C is pressed during execution */
/**************************************************************************/
void ctrl_c(int signum)
{
   perror("consumer: You have pressed CTRL_C\n");
   cleanup_on_exit();  /* Perform cleanup operations before exiting */
   exit(0);
}

void *ThreadRunner(void *arg)
{
    int currStrLine;
	int currId;
	int *currThread = arg;
	int fullTest;
	int mutexTest;
	int k;
    /* Consume items until the SENTINEL is found */
	while(sp->buff[sp->out].id != SENTINEL){
		/* wait for a full buffer */
		fullTest = sem_wait(FULLptr);
		/* wait for the mutex lock */
		mutexTest = sem_wait(MUTEXptr);
		/* get item id from buffer */
		currStrLine = (sp->buff[sp->out]).id;
		/* Note that an item has been consumed */
		printf("\tConsumer %d: Consumed\t%d at buffer[%d]\n", (*currThread)+1, currStrLine, sp->out);
	    if (sp->buff[sp->out].id != SENTINEL) {
			 /* .... place item string into string array .... */
			 strcpy(sp->strarray[sp->buff[sp->out].id - 1], sp->buff[sp->out].str);
			 /*The % BUFFSIZE ensures that the index doesn't go out of bounds
			 also this automatically points to 0 when index equals BUFFSIZE*/
			 /* increment buffer index*/
			 sp->out = (sp->out+1) % BUFFSIZE;
			 
		}
      //if sentinel is encountered, then put the item into the buffer and break 
	  //from the loop
		if (sp->buff[sp->out].id == SENTINEL) {
			sp->buff[sp->out].id = SENTINEL;
			/* release the mutex lock */
			sem_post(MUTEXptr);
			/* signal an empty buffer slot */
			sem_post(EMPTYptr);
			/* allow all threads to terminate by incrementing FULL semaphore. Does no harm as every thread will recognize
				the sentinel value and break its loop and therefore exiting the thread.*/
			sem_post(FULLptr);
			break;
		}
		/* release the mutex lock */
		sem_post(MUTEXptr);
		/* signal an empty buffer slot */
		sem_post(EMPTYptr);
		
    }
    return NULL;
}

/**************************************************************************/
/* Main Consumer Routine                                                  */
/**************************************************************************/
int main(int argc, char *argv[])
{

   //local decls
	int i;
   signal(SIGINT, ctrl_c);
   setbuf(stdout, NULL);
   setbuf(stderr, NULL);

    
    int fd = shm_open("jmcgdd", O_RDWR, S_IRWXU);
    //error checks
	if(fd < 0){
		printf("\nError creating shared memory segment: [%s]\n\n",strerror(errno));
		shm_unlink("jmcgdd");
		return 1;
	}

   sp = mmap(0, sizeof(*sp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	//error checks
	if(sp == NULL){
		printf("\nError has occurred with address of shared memory location. Terminating program. \n\n");
		shm_unlink("jmcgdd");
		return 1;
	}
   

   /* Get pointers to the semaphores created by the parent */
   MUTEXptr = sem_open(sp->MUTEXname, O_RDWR);
   EMPTYptr = sem_open(sp->EMPTYname, O_RDWR);
   FULLptr = sem_open(sp->FULLname, O_RDWR);

	//thread creation
	
	pthread_t tid[NUM_CONSUMERS];
	pthread_attr_t attr;
	int threadErr;
	int indexes[NUM_CONSUMERS];
	
	for(i=0;i<NUM_CONSUMERS;i++){
		//initialize attributes of pthread to default
		pthread_attr_init(&attr);
		//create pthread
		indexes[i] = i;
		threadErr = pthread_create(&(tid[indexes[i]]), NULL, ThreadRunner, &indexes[i]);
		if(threadErr != 0) {
			printf("\nThread could not be created. Terminating.\n");
			return -1;
		}
	}
	
	//wait till threads complete execution
	int j;
   for(j=0;j<NUM_CONSUMERS;j++){
		pthread_join((tid[j]), NULL);
	}
	
/* Write a termination message */
    sem_wait(MUTEXptr);      /* protect printf as a critical section */
    printf("Finished Consuming\n");
    sem_post(MUTEXptr);

   cleanup_on_exit();
   exit(0);
   return 0;
}

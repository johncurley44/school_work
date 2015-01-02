/********************************************************************************
 * Name:           John Curley
 * pawprint:       jmcgdd
 * Course:         CS 4520
 * Assignment#:    Project
 *
 * File name:      producer.c
 *
 * Question no:	   
 *
 * Assumptions:    1)
 *		&		   2)  
 * Precautions		  
 *********************************************************************************/

#include "project.h"


/* Global variables for producer.c */
   shr_mem_t *sp;     /* pointer to shared memory structure */
   sem_t *MUTEXptr;   /* pointer to the MUTEX semaphore */
   sem_t *EMPTYptr;   /* pointer to the EMPTY semaphore */
   sem_t *FULLptr;    /* pointer to the FULL semaphore  */


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
   perror("producer: You have pressed CTRL_C\n");
   cleanup_on_exit();  /* Perform cleanup operations before exiting */
   exit(0);
}

/**************************************************************************/
/* Function to produce one item in the buffer                             */
/**************************************************************************/
void produce_item(struct item *inItem)
{
	
	struct item *proItem = inItem;
   /* wait for a empty buffer */
	sem_wait(EMPTYptr);
   /* wait for the mutex lock */
	sem_wait(MUTEXptr);
   /* put item id into buffer */
	sp->buff[sp->in].id = proItem->id;
   /* Place associated string into buffer item string by copying it in
	  specified location*/
	strcpy(sp->buff[sp->in].str, proItem->str);
	
   printf("Producer: Produced\t%d at buffer[%d]\n", sp->buff[sp->in].id, sp->in);
   sp->in = (sp->in + 1) % BUFFSIZE;   /* increment buffer index */

   /* release the mutex lock */
   sem_post(MUTEXptr);
   /* signal a full buffer slot */
   sem_post(FULLptr);
   return;
   
}


/**************************************************************************/
/* Main producer routine                                                  */
/**************************************************************************/
int main(int argc, char *argv[])
{
   /* A variable of item used in processing */
	struct item tempItem;
	
/* Setup system environment */
   signal(SIGINT, ctrl_c);      /* specify routine to handle CTRL-C */
   setbuf(stdout, NULL);        /* turn off buffering of stdout */
   setbuf(stderr, NULL);        /* turn off buffering of stderr */

	int fd = shm_open("jmcgdd", O_RDWR, S_IRWXU);
	//error checking
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

	char tempStr[100];
	int lineNum;
	char lineContent[80];
   /* Read data and produce items until EOF */
   while (feof(stdin) != 1) 
      { 	/* read lines of data fron stdin */
			/* ... read new data item (id and string) from stdin ... */
			/* validate item id values for correctness */  
			fgets(tempStr, 100, stdin);//store line into temp char array
			sscanf(tempStr, "%d%[^\n]", &lineNum, lineContent);//extract line from the temp char array above
			
			//check line numbers here <0 & > 110 are invalid
			if(lineNum < 0 || lineNum > 110){
				printf("***ERR*** Producer ignoring new item with id=%d\n", lineNum);
			}
			//now store the line number and string in the item struct variable
			//call the produce_item function with the above item struct variable
			else{
				tempItem.id = lineNum;
				strcpy(tempItem.str, lineContent);
				produce_item(&tempItem);
			}
      }

/* At EOF ... */
/* Add a sentinal item in Buffer to signal end of data input */
    
    /* produce a sentinel value after EOF */
	tempItem.id = SENTINEL;
	strcpy(tempItem.str, "sentinel reached");
	produce_item(&tempItem);
	
/* Write a termination message */
    sem_wait(MUTEXptr);       /* protect printf as a critical section */
    printf("\nFinished Producing\n");
    sem_post(MUTEXptr);
	
	cleanup_on_exit();
   exit(0);
   return 0;
}

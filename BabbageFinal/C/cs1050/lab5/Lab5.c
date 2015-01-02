/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: La-di-da
 **/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defines BOOL as a data type so a boolean can be returned
typedef short BOOL;

//Global constants
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 10
#define MAX_FREQ 15
#define RAND_SIZE 16

//Global variables
int R_ARRAY[MAX_SIZE];
int F_ARRAY[MAX_FREQ];
//Function prototypes
int checkSize(int x);
void readInput(int size);
void printArray(int size);
int countNumber(int size, int n);
void frequency(int size);
void printHistogram(void);

int main(void)
{
	//Variable declaration
	int inSize = 0;
	int contLoop = TRUE;
	int searchNum = 0;
	int searchResult = 0;
	//While loop that will continue to ask for an array size until a valid number is entered
	while(contLoop == TRUE)
	{
		printf("\nEnter input size: ");
		scanf("%d", &inSize);
		printf("\n");
		//If valid array size is entered by user, sentinal value used to terminate while loop
		if(checkSize(inSize)==TRUE)
			contLoop = FALSE;
		else
			printf("Invalid input, size should be between 1-10\n");
	}
	readInput(inSize);
	printArray(inSize);
	printf("Enter a number to search: ");
	scanf("%d", &searchNum);
	searchResult = countNumber(inSize,searchNum);
	//Prints a statement dependent upon whether or not user-input is greater than 0
	if(searchResult>0)
		printf("\nNumber %d is present %d times in the array\n\n", searchNum, searchResult);
	else
		printf("\nNumber %d is not present in the array\n\n", searchNum);
	
	frequency(inSize);
	printHistogram();
}

/* Function Purpose: Performs error check for input size. Must be between 1 and 10.
 * Input params: Integer value
 * Return param: 1 for true, 0 for false
 **/
int checkSize(int inX)
{
	//Checks if number is a value from 1-10 inclusive, returns true or false depending
	if(inX > 0 && inX < 11)
		return TRUE;
	else
		return FALSE;
}

/* Function Purpose: Generates n random values from 0-15 and stores them in a global array
 * Input params: Size of array
 * Return param: void
 **/
void readInput(int aSize)
{
	srand(time(NULL));
	int count = 0;
	//Iterates through each location in random integer array, assigning random values
	for(count=0; count<aSize; count++)
	{
		R_ARRAY[count] = rand() % RAND_SIZE;
	}
}

/* Function Purpose: Prints the n random numbers stored in the global array
 * Input params: Size of array
 * Return param: void
 **/
void printArray(int size)
{
	int count = 0;
	printf("Stored numbers: ");
	//Iterates through each location in random int array and prints each individual value
	for(count=0; count<size; count++)
	{
		printf("%d ",R_ARRAY[count]);
	}
	printf("\n\n");
}
 
 /* Function Purpose: Takes a number aContains and counts how many times that number appears in global array
 * Input params: Size of array, integer for frequency check
 * Return param: Number of times frequency check integer appears in global array
 **/
int countNumber(int size, int aContains)
{
	int count = 0;
	int occurs = 0;
	//Iterates through each location in random int array and adds 1 to occurs for each value found equal to user-input search value
	for(count=0; count<size; count++)
	{
		if(R_ARRAY[count]==aContains)
			occurs++;
	}
	return occurs;
}

/* Function Purpose: Cumputes frequency of each number (0-15) stored in global array, stores frequency values in global array, F_ARRAY
 * Input params: Size of array
 * Return param: void
 **/
void frequency(int size)
{
	int count = 0;
	//Iterates through random int array, using the values to add one to the corresponding location in the frequency array
	for (count=0; count<size; count++)
	{
		F_ARRAY[R_ARRAY[count]]++;
	}
}

/* Function Purpose: Generates n random values from 0-15 and stores them in a global array
 * Input params: Size of array
 * Return param: void
 **/
void printHistogram(void)
{
	int count1 = 0;
	int count2 = 0;
	printf("Printing histogram:\n\n");
	//Goes through each location in frequency array
	for(count1=0; count1<MAX_FREQ; count1++)
	{
		//If location in frequency array is greater than 1, prints number associated with that location
		if(F_ARRAY[count1]>0)
		{
			printf("%d: ",count1);
			//Prints n asterixs where n is the value in current F_ARRAY location
			for(count2=0; count2<F_ARRAY[count1]; count2++)
			{
				printf("*");
			}
			printf("\n");
		}
	}
	printf("\n\n");
}
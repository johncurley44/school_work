/* John Curley - jmcgdd
   Lab Section: C
   Submission Code: Gonzo */

//Include standard input output, define constants and Loop controllers
#include <stdio.h>
#define SIZE 10
#define MAX 1000
#define CONTLOOP 1
#define STOPLOOP 0

// 
int getSize(void);
int validate(int input);
int GCD(int n1, int n2);

int main(void)
{
	int loopIter = getSize();
	int m, n, tempGCD, count;
	int validNum = 0;
	for(count = 1; count <= loopIter; count++)
	{
		do
		{
			printf("Please enter value for N1: ");
			scanf("%d", &n1);
			validNum = validate(n1);
			if(validNum == 0)
				printf("Incorrect value (0<N1<1000)\n");
		}
		while(validNum != 1);
		
		do
		{
			printf("Please enter value for N2: ");
			scanf("%d", &n2);
			validNum = validate(n2);
			if(validNum == 0)
				printf("Incorrect value (0<N2<1000)\n");
		}
		while(validNum != 1);
		
		tempGCD = GCD(n1,n2);
		printf("%d) GCD(%d, %d) = %d\n\n", count, n1, n2, tempGCD);
		
	}
}

//Retrieves number of GCD pairs from user, makes sure number between 0 and 10
int getSize(void)
{
	int sizeIn, loopCheck = 1;
	while(loopCheck == CONTLOOP)
	{
		printf("Please enter number of GCD pairs: ");
		scanf("%d",&sizeIn);
		if(sizeIn >= SIZE || sizeIn <= 0)
			printf("Please enter positive integer number (0<input<10)\n");
		else
			loopCheck = STOPLOOP;
	}
	
	return sizeIn;
}

//Makes sure 0<user input<MAX, returns 1 if valid, 0 if invalid
int validate(int input)
{
	if(input > 0 && input < MAX)
		return 1;
	else
		return 0;
}

//Implements Euclidean algorithm, checks to make sure first input greater or equal to second
int GCD(int N[], int length)
{
	int checkMod = 1;
	int checkMax = 0;
	int retGCD = 0;
	
	N[] = sortArray(N[], length);
	
	while(checkMod != STOPLOOP)
	{
		checkMod = n1 % n2;
		n1 = n2;
		n2 = checkMod;
	}
	
	return n1;
}

int sortArray(int inArray[], int length)
{
	int count, loc, temp;
	for(count = 1; count < length; count++)
	{
		for(loc = 0; loc < length - 1; loc++)
		{
			if(inArray[loc] > inArray[loc + 1])
			{
				temp = inArray[loc];
				inArray[loc] = inArray[loc + 1];
				inArary[loc + 1] = temp;
			}
		}
	}
	return inArray[];
}
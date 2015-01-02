/* John Curley - jmcgdd
   Lab Section: C
   Submission Code: Gonzo */

//Include standard input output, define constants and Loop controllers
#include <stdio.h>
#define SIZE 10
#define MAX 1000
#define CONTLOOP 1
#define STOPLOOP 0

// Function prototypes
int getSize(void);
int validate(int input);
int GCD(int m, int n);

int main(void)
{
	int loopIter = getSize();
	int m, n, tempGCD, count;
	int validNum = 0;
	for(count = 1; count <= loopIter; count++)
	{
		do
		{
			printf("Please enter value for M: ");
			scanf("%d", &m);
			validNum = validate(m);
			if(validNum == 0)
				printf("Incorrect value (0<M<1000)\n");
		}
		while(validNum != 1);
		
		do
		{
			printf("Please enter value for N: ");
			scanf("%d", &n);
			validNum = validate(n);
			if(validNum == 0)
				printf("Incorrect value (0<N<1000)\n");
		}
		while(validNum != 1);
		
		tempGCD = GCD(m,n);
		printf("%d) GCD(%d, %d) = %d\n\n", count, m, n, tempGCD);
		
	}
}

/* Function Purpose: Retrieves number of GCD pairs from user, makes sure number between 0 and 10
 * Input params: none
 * Return param: number of GCD pairs from user
 **/
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

/* Function Purpose: Makes sure 0<user input<MAX
 * Input params: one of the 2 values used in Euclidean algorithm
 * Return param: 1 to indicate valid, 0 to indicate invalid
 **/
int validate(int input)
{
	if(input > 0 && input < MAX)
		return 1;
	else
		return 0;
}

/* Function Purpose: Implements euclidean algorithm, does a check to make sure bigNum mod smallNum
 * Input params: 2 values to find GCD for
 * Return param: GCD number
 **/
int GCD(int m, int n)
{
	int checkMod = 1;
	int retGCD = 0;
	
	if(m < n)
	{
		int tempM = m;
		m = n;
		n = tempM;
	}
	
	while(checkMod != STOPLOOP)
	{
		checkMod = m % n;
		m = n;
		n = checkMod;
	}
	
	return m;
}

	



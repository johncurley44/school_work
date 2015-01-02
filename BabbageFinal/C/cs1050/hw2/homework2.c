/*John Curley - jmcgdd - 16013276
  Homework #2
  Lab Section: C */
  

#include <stdio.h>

//Function that determines if input integer is a prime, returns 1 for prime, 0 for not prime
int isPrime(int num1)
{
	//Declaration of variable
	int checkNum;
	//For loop checks division of input by every number but 1 and the input to see if prime
	for (checkNum = 2; checkNum < num1; checkNum++)
	{
		if (num1 % checkNum == 0 && num1 != checkNum)
			return 0;
	}		
	return 1;
}

//Determines and returns first digit of input
int pullDigit(int num2)
{
	//While input remains above 10, integer divides by ten so that last digit is ignored
	while(num2 >= 10)
	{
		num2 /= 10;
	}
	return num2;
}

//Determines both the minimum and maximum of three inputs, then returns the sum of those two
int sumOfExtremes(int aInt, int bInt, int cInt)
{
	//Declaration of variables
	int min = aInt;
	int max = aInt;
	//Finds maximum number of three inputs
	if(bInt > aInt && bInt > cInt)
		max = bInt;
	else if(cInt > aInt && cInt > bInt)
		max = cInt;
	//Finds minimum number of three inputs
	if(bInt < aInt && bInt < cInt)
		min = bInt;
	else if(cInt < aInt && cInt < bInt)
		min = cInt;
	
	return max + min;
}

//Determines both minimum and maximum of three inputs and returns product of the two
int productOfExtremes(int xInt, int yInt, int zInt)
{
	//Declaration of variables
	int min = xInt;
	int max = xInt;
	//Finds maximum of three inputs
	if(yInt > xInt && yInt > zInt)
		max = yInt;
	else if(zInt > xInt && zInt > yInt)
		max = zInt;
	//Finds minimum of three inputs	
	if(yInt < xInt && yInt < zInt)
		min = yInt;
	else if(zInt < xInt && zInt < yInt)
		min = zInt;
	
	return max * min;	
}

//Prints the three inputs, plus the result of sumOfExtremes and productOfExtremes of those three inputs
void printResults(int lInt, int mInt, int nInt)
{
	int sum1 = sumOfExtremes(lInt,mInt,nInt);
	int prod1 = productOfExtremes(lInt,mInt,nInt);
	printf("The results of %d, %d, and %d are %d and %d\n",lInt,mInt,nInt,sum1,prod1);
}

int main(void)
{
	//Declaration of variables used throughout main
	int yesNo1, yesNo2, yesNo3, count1, count2, count3, twoDigit,firstDigit, secondDigit, lastDigit, firstNum, sum1, checkNum;
	
	printf("\nPrime number results: \n");
	
	//Nested for loops that determine each combination of prime numbers up to 100 that when summed together plus 1 result in a prime number
	for(count1=2; count1 <= 100; count1++)
	{
		yesNo1 = isPrime(count1);
		if(yesNo1 == 1)
		{
			//Starting count2 at count1 prevents duplicates in output and reduce run time
			for(count2=count1; count2 <= 100; count2++)
			{
				yesNo2 = isPrime(count2);
				if(yesNo2 == 1)
				{
					yesNo3 = isPrime(count1+count2+1);
					if(yesNo3 == 1)
					{
						printResults(count1,count2,count1+count2+1);
					}
				}
			}
		}
	}
	
	printf("\nPull digit results: \n");
	
	//Checks each number from 500 to 600 to see if the first two digits, combined to one number, plus the third digit, result in a prime number
	for(count3=500; count3 <= 600; count3++)
	{
		firstDigit = pullDigit(count3);
		//Determines a new number if the first digit was removed
		twoDigit = count3 - firstDigit*100;
		//Checks to see if second digit is 0
		if(twoDigit < 10)
		{
			secondDigit = 0;
		}
		else
		{
			secondDigit = pullDigit(twoDigit);
		}
		//Gets last digit from mod command
		lastDigit = twoDigit % 10;
		//Makes first two digits into one number
		firstNum = firstDigit*10 + secondDigit;
		//Adds first two digits as one number and last digit
		sum1 = firstNum + lastDigit;
		checkNum = isPrime(sum1);
		if(checkNum == 1)
		{
			printResults(firstNum,lastDigit,sum1);
		}
	}
	return 0;
}
	
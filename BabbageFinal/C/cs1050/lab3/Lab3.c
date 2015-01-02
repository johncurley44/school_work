/* John Curley
 * 9/18/2012
 * Lab C - Matt England
 * SC: Collywobbles
 **/
 
 #include <stdio.h>

 
 int main(void)
 {
	//Variable declaration
	int i, n;
	int inVal, total;
	double meanVal;
	int inCheck = 0, maxVal = 0, minVal = 0;
	
	// Function that returns 1 if input is a valid number, 0 if not
	int error_check(int checkNum)
	{
		if (checkNum < 0 || checkNum > 100)
			return 0;
		else
			return 1;
	}
	
	//Takes in input size and checks to make sure value is greater than 0
	do
	{
		printf("\nEnter the input size: ");
		scanf("%d",&n);
		if(n <= 0)
		{
			inCheck = 0;
			printf("Invalid input, input size should be positive and greater than zero\n");
		}
		else
		{
			inCheck = 1;
			printf("\nPlease input %d positive inputs:\n\n",n);
		}
	}
	while(inCheck == 0);
	
	//Loops n times checking for max and min value and adding all inputs to total
	for(i = 0; i < n; i++)
	{
		printf("Enter a positive integer: ");
		scanf("%d",&inVal);
		//Uses error_check function to make sure value is between 0 and 100
		if (error_check(inVal) == 1)
		{
			total+=inVal;
			//Assigns current input value to maximum value if current input is greater than current maximum value
			if(inVal > maxVal)
				maxVal = inVal;
			//Assigns current input value to minimum value if current input is less than current minimum value
			if(inVal < minVal)
				minVal = inVal;
			//Changes print statement if last valid input value was just entered
			if(i == n-1)
				printf("Input finished, commencing calculations\n\n");
			else
				printf("Please enter %d additional positive integers\n\n",n-i-1);
		}
		//If input isn't a valid number, displays that, then subtracts from the for loop counter to keep the loop going
		else
		{
			printf("Invalid number, number should be between 0-100\n\n");
			i--;
		}
	}
	
	//Mean calculation from total and n.
	meanVal = (double) total/n;
	printf("Mean of the entered numbers was %.2lf\n",meanVal);
	printf("Largest entered number was %d\n",maxVal);
	printf("Smallest entered number was %d\n\n",minVal);
	
	return 0;
}
	
		
	
	
	
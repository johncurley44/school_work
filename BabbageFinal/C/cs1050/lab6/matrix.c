/* John Curley jmcgdd
 * Lab Section: C
 * Submission Code: Surfeit	*/
 
 #include <stdio.h>
 #include <stdlib.h>
 
 #define MAX 10
 #define CONTLOOP 1
 #define ENDLOOP 0
 
 int validate(void);
 void init(int array[][MAX], int R, int C);
 void print(int array[][MAX], int R, int C);
 void product(int a[][MAX], int b[][MAX], int c[][MAX], int m, int n);
 void search (int matrix[][MAX], int target, int m, int n);
 void multiply(int array[][MAX], int x, int R, int C);
 
 int main(void)
 {
	int arrayMain1[MAX][MAX] = {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	int arrayMain2[MAX][MAX] = {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	int arrayMain3[MAX][MAX] = {{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
	int target = 0, mVal = 0, nVal = 0;
	
	printf("\nPlease enter a value for M: ");
	mVal = validate();
	printf("\nPlease enter a value for N: ");
	nVal = validate();
	init(arrayMain1,mVal,nVal);
	init(arrayMain2,nVal,mVal);
	
	printf("Matrix A: \n");
	print(arrayMain1,mVal,nVal);
	printf("Matrix B: \n");
	print(arrayMain2,nVal,mVal);
	
	product(arrayMain1,arrayMain2,arrayMain3,mVal,nVal);

	
	printf("Multiplication of the Matrices (C = A * B): \n");
	print(arrayMain3,mVal,nVal);
	
	printf("Please enter target value: ");
	scanf("%d",target);
	search(arrayMain3,target,mVal,mVal);
	
 }
 
 int validate(void)
 {
	int checkLoop = CONTLOOP;
	int checkVal = 0;
	while(checkLoop == CONTLOOP)
	{
		scanf("%d", &checkVal);
		if(checkVal>0 && checkVal<10)
			checkLoop = ENDLOOP;
		else
			printf("valid input must be between 1 - 10\n");
	}
	return checkVal;
 }
 
 void init(int array[][MAX], int R, int C)
 {
	int count1 = 0;
	int count2 = 0;
	for(count1=0;count1<R;count1++)
	{
		for(count2=0;count2<C;count2++)
		{
			array[count1][count2]=rand() % 10;
		}
	}
	
 }
 
 void print(int array[][MAX], int R, int C)
 {
	int count1 = 0;
	int count2 = 0;
	for(count1=0;count1<R;count1++)
	{
		for(count2=0;count2<C;count2++)
		{
			printf("%d ",array[count1][count2]);
		}
		printf("\n");
	}
 }
 
 void product(int a[][MAX], int b[][MAX], int c[][MAX], int m, int n)
 {
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	for(count1=0;count1<m;count1++)
	{
		for(count2=0;count2<m;count2++)
		{
			for(count3=0;count3<n;count3++)
			{
				c[count1][count2] += (a[count1][count3]*b[count3][count2]);
			}
		}
	}
}

void search (int matrix[][MAX], int target, int m, int n)
{
	int count1 = 0;
	int count2 = 0;
	int check = 0;
	for(count1=0;count1<m;count1++)
	{
		for(count2=0;count2<n;count2++)
		{
			if(matrix[count1][count2]==target)
			{
				printf("%d found at index [%d][%d]\n",target,count1,count2);
				check++;
			}
		}
	}
	if(check == 0)
		printf("%d was not found in the array\n",target);
	multiply(matrix,target,m,n);
}

void multiply(int array[][MAX], int x, int R, int C)
{	
	int count1 = 0;
	int count2 = 0;
	for(count1=0;count1<R;count1++)
	{
		for(count2=0;count2<C;count2++)
		{
			array[count1][count2]*=x;
		}
	}
	printf("Matrix C * %d\n",x);
	print(array,R,C);
}
			
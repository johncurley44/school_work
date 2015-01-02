/* John Curley
 * Prelab 1 */
 
 
  //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define PRELABFILE "prelab1.txt"
 #define ROWS 4
 #define COLUMNS 4
 #define LINES 4
 #define TRUE 1
 #define FALSE 0

/*enum LINENUM{
	line1 = 1;
	line2 = 2;
	line3 = 3;
	line4 = 4;
}*/

void findMin(int inArray[ROWS][COLUMNS], int minArray[LINES]);
void findMax(int inArray[ROWS][COLUMNS], int maxArray[LINES]);
void findSum(int minArray[LINES], int maxArray[LINES], int sumArray[LINES]);
void print(int minArray[LINES], int maxArray[LINES], int sumArray[LINES]);
void findNum(int inArray[ROWS][COLUMNS]);

int main(int argc, char** argv){
	FILE *fptr;
	int i, j;
	int numArray[ROWS][COLUMNS];
	int minArray[LINES], maxArray[LINES], sumArray[LINES];
	fptr = fopen(PRELABFILE,"r");
	
	for(i=0;i<ROWS;i++){
	
		for(j=0;j<COLUMNS;j++){
			fscanf(fptr,"%d",&numArray[i][j]);
		}
	}
	
	findMin(numArray,minArray);
	findMax(numArray,maxArray);
	findSum(minArray,maxArray,sumArray);
	print(minArray, maxArray, sumArray);
	findNum(numArray);
	
	
}

void findMin(int inArray[ROWS][COLUMNS],int minArray[LINES]){
	int i, j;
	
	for(i=0;i<ROWS;i++){
	minArray[i] = 10000;
		for(j=0;j<COLUMNS;j++){
			if(minArray[i] > inArray[i][j]){
				minArray[i] = inArray[i][j];
			}
		}
	}
}

void findMax(int inArray[ROWS][COLUMNS],int maxArray[LINES]){
	int i, j;
	for(i=0;i<ROWS;i++){
	maxArray[i] = 0;
		for(j=0;j<COLUMNS;j++){
			if(inArray[i][j] > maxArray[i]){
				maxArray[i] = inArray[i][j];
			}
		}
	}
}

void findSum(int minArray[LINES], int maxArray[LINES], int sumArray[LINES]){
	int i;
	for(i = 0; i<LINES; i++){
		sumArray[i] = minArray[i]+maxArray[i];
	}
}

void print(int minArray[LINES], int maxArray[LINES], int sumArray[LINES]){
	int i = 0;
	printf("\n");
	for(i=0;i<LINES;i++){
		printf("Line %d - min is %d; max is %d; sum of the two is %d\n", i+1, minArray[i], maxArray[i], sumArray[i]);
	}
}

void findNum(int inArray[ROWS][COLUMNS]){
	int i, j, searchNum;
	int found = FALSE;
	printf("Enter the target number you are looking for: \n");
	scanf("%d", &searchNum);
	for(i=0;i<ROWS;i++){
		for(j=0;j<COLUMNS;j++){
			if(inArray[i][j] == searchNum){
				printf("%d is in row %d, column %d\n", searchNum, i+1, j+1);
				found = TRUE;
			}
		}
	}
	if(found == FALSE){
		printf("Target number not found\n\n");
		findNum(inArray);
	}
}
	
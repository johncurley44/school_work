/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* prelab11.c
*/
//Preprocess Commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definitions
 #define MAX_NUM_STR 25

int compareSmallerOnLeft(int num1, int num2);
int compareSmallerOnRight(int num1, int num2);
void random_quick_sort(int* arr, int start, int end, int(*compare)(int, int));
int random_partition(int* arr, int start, int end, int(*compare)(int, int));
/* Function Purpose: Read a file of integers, creates sorted array with quicksort, creates balanced BST, prints all
 * Input params: argc - number of variables read from command line, argv - holds strings of command line inputs
 * Return param: some int
 **/
int main(int argc, char **argv){
	FILE* fPtr;
	//Checks to make sure command line contains only one other argument
	if(argc != 2){
		printf("One and only one command line arguments are allowed, terminating. \n\n");
		return 1;
	}
	//Opens files
	fPtr = fopen(argv[1], "r");
	//Checks to make sure files were found
	if(fPtr == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	//Creates some temporarty strings to hold values from fgets
	char tempStr[MAX_NUM_STR];
	char tempDataStr[MAX_NUM_STR];
	char elemStr[MAX_NUM_STR];
	int i = 0, compareChoice = 0, k;
	//Takes the first number in the file, which is the total number of elements to be sorted
	fgets(elemStr, MAX_NUM_STR, fPtr);
	int elemNum = atoi(strtok(elemStr, " "));
	//Mallocs space enough for the number of integers in file
	int *arr = malloc(sizeof(int)*(elemNum));
	//Reads numbers to be sorted into arr pointer
	while(fgets(tempStr, MAX_NUM_STR, fPtr)){
		strcpy(tempDataStr, strtok(tempStr, " "));
		*(arr+i) = atoi(tempDataStr);
		i++;
	}
	fclose(fPtr);
	//Ask user how they would like to sort
	printf("Do you want to sort with smaller values on the left (1) or right (2)? ");
	scanf("%d", &compareChoice);
	if(compareChoice==1) random_quick_sort(arr, 0, elemNum-1, compareSmallerOnLeft);
	else if(compareChoice==2) random_quick_sort(arr, 0, elemNum-1, compareSmallerOnRight);
	else printf("Invalid Selection");
	for(k=0;k<elemNum;k++){
		printf("%d ", *(arr+k));
	}
	printf("\n");
	free(arr);
	return 0;
	
}

int compareSmallerOnLeft(int num1, int num2){
	if(num1 == num2) return 0;
	if(num1<num2) return 1;
	if(num2<num1) return -1;
}
int compareSmallerOnRight(int num1, int num2){
	if(num1 == num2) return 0;
	if(num1<num2) return -1;
	if(num2<num1) return 1;
}

/* Function Purpose: Recursively creates a sorted array using quicksort
 * Input params: arr - integer array, start - first element or section to sort, end - last element of section to sort
 * Return param: none
 **/
void random_quick_sort(int *arr, int start, int end, int(*compare)(int, int)){
	int pivot;
	//Base case
	if(start>end){
		return;
	}
	//Calls partition function to determine pivot point and sort based on pivot point
	pivot = random_partition(arr, start, end, compare);
	//Recursively calls upon self to sort entire array
	random_quick_sort(arr, start, pivot-1, compare);
	random_quick_sort(arr, pivot+1, end, compare);
}
/* Function Purpose: Chooses a pivot at random, rearranges array into two parts based on the pivot, nums<pivot on left, nums>pivot on right
 * Input params: arr - integer array, start - first element or section to sort, end - last element of section to sort
 * Return param: position of pivot after rearranging
 **/
int random_partition(int* arr, int start, int end, int(*compare)(int, int)){
    srand(time(NULL));
	int j;
	//Chooses random pivot point
    int rndInd = start + rand() % (end-start+1);
    int pivot = *(arr+rndInd);
	//Swaps randomly chosen pivot with the end value
    int temp = *(arr+rndInd);
	*(arr+rndInd) = *(arr+end);
	*(arr+end) = temp;
    rndInd = end;
    int i = start -1;
	//Cycles through each element
    for(j=start; j<end; j++)
    {
        //If current element<=pivot value, move that value to the left side of the array and keep track of last position filled with a value<=pivot
		if(compare(*(arr+j), pivot) >= 0)
        {
			temp = *(arr+(++i));
			*(arr+i) = *(arr+j);
			*(arr+j) = temp;
        }
    }
	//Swap first value>pivot with pivot saved to the end of the array
	temp = *(arr+i+1);
	*(arr+i+1) = *(arr+rndInd);
	*(arr+rndInd) = temp;
	//Return the position of the pivot value
    return i+1;
}

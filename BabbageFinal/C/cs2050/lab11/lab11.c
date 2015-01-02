/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* Lab 11
*/
//Preprocess Commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definitions
 #define MAX_NUM_STR 25
//Function Prototypes
int compareSmallerOnLeft(int num1, int num2);
int compareSmallerOnRight(int num1, int num2);
void random_quick_sort(int* arr, int start, int end, int(*compare)(int, int));
int random_partition(int* arr, int start, int end, int(*compare)(int, int));
void padWithSpaces(int num);
void padWithHyphens(int num);
void print_as_Tree(int *arr, int depth, int start, int end, void(*padder)(int));
int b_search(int *arr, int data, int start, int end, int(*compare)(int, int));

/* Function Purpose: Read in a file of numbers, sort them, print them as trees, search for a number and print results
 * Input params: 
 * Return param:
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
	int i = 0, k, compareChoice = 0, padChoice = 0, targetNum = 0, result = 0;
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
	
	//Ask user how they would like to sort, does so accordingly
	printf("Do you want to sort with smaller values on the left (1) or right (2)? ");
	scanf("%d", &compareChoice);
	//Sorts with smaller numbers on right or left depending on user input
	if(compareChoice==1) random_quick_sort(arr, 0, elemNum-1, compareSmallerOnLeft);
	else if(compareChoice==2) random_quick_sort(arr, 0, elemNum-1, compareSmallerOnRight);
	else printf("Invalid Selection");
	
	//Ask user if they want tree padded with hyphens or spaces, does so accordingly
	printf("Do you want to pad with hypens (1) or with spaces (2)?");
	scanf("%d", &padChoice);
	//Prints with hyphens or spaces, depending on user input
	if(padChoice == 1) print_as_Tree(arr, 0, 0, elemNum-1, padWithHyphens);
	else if(padChoice == 2) print_as_Tree(arr, 0, 0, elemNum-1, padWithSpaces);
	else printf("Invalid Selection");
	
	//Ask user for a number to search for, then do so and display result
	printf("What number would you like to search for? ");
	scanf("%d", &targetNum);
	//Calls b_search for smaller numbers on right or left, depending on previous input
	if(compareChoice==1) result = b_search(arr, targetNum, 0, elemNum-1, compareSmallerOnLeft); 
	else if(compareChoice==2) result = b_search(arr, targetNum, 0, elemNum-1, compareSmallerOnRight); 
	else printf("Invalid Selection");
	//Prints a message based on whether or not number was found
	if(result==1) printf("%d was found in the array.\n", targetNum);
	else if(result==0) printf("%d was not found in the array.\n", targetNum);
	else printf("Bad value returned from b_search\n");
	
	printf("\n");
	free(arr);
	return 0;
	
}
/* Function Purpose: Compares 2 numbers, returns input based on results
 * Input params: 2 numbers
 * Return param: 1 if first number less than second, -1 if second>first, 0 if equal
 **/
int compareSmallerOnLeft(int num1, int num2){
	if(num1 == num2) return 0;
	if(num1<num2) return 1;
	if(num2<num1) return -1;
}
/* Function Purpose: Compares 2 numbers, returns input based on results
 * Input params: 2 numbers
 * Return param: -1 if first number less than second, 1 if second>first, 0 if equal
 **/
int compareSmallerOnRight(int num1, int num2){
	if(num1 == num2) return 0;
	if(num1<num2) return -1;
	if(num2<num1) return 1;
}

/* Function Purpose: Divides and conquers for quicksort
 * Input params: integer array, starting and ending position of array to be looked at, and function pointer for a comparison function
 * Return param: void
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
/* Function Purpose: Chooses a pivot at random, rearranges array into two parts based on the pivot, nums sorted either descending or ascending based on function pointer input
 * Input params: arr - integer array, start - first element or section to sort, end - last element of section to sort, compare - function pointer that determines ascending or descending order
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
        //Moves current value to fit ascending or descending order if necessary
		if(compare(*(arr+j), pivot) >= 0)
        {
			temp = *(arr+(++i));
			*(arr+i) = *(arr+j);
			*(arr+j) = temp;
        }
    }
	//places pivot back in middle of array
	temp = *(arr+i+1);
	*(arr+i+1) = *(arr+rndInd);
	*(arr+rndInd) = temp;
	//Return the position of the pivot value
    return i+1;
}
/* Function Purpose: ouputs num spaces
 * Input params: num - number of spaces desired
 * Return param: void
 **/
void padWithSpaces(int num){
	int i;
	for(i=0;i<num;i++){
		printf(" ");
	}
}
/* Function Purpose: outputs num hyphens
 * Input params: num - number of hyphens desired
 * Return param: void
 **/
void padWithHyphens(int num){
	int i;
	for(i=0;i<num;i++){
		printf("-");
	}
}
/* Function Purpose: Prints a sorted int array as a BTree
 * Input params: arr - sorted int array, depth - depth of value on tree, start - starting location of array, end - ending location of array, 
 * 					padder - func. ptr. that determines how the depth will be shown
 * Return param: void
 **/
void print_as_Tree(int *arr, int depth, int start, int end, void(*padder)(int)){
	//Base case
	if ((end-start)<0)
	{
		return;
	}
	int mid = (start+end)/2;
	//Recursively splits array and prints mid points so that printed values take the form of a tree
	print_as_Tree(arr, depth+4, start, mid-1, padder);
	padder(depth);
	printf("%d\n", *(arr+mid));
	print_as_Tree(arr, depth+4, mid+1, end, padder);
}
/* Function Purpose: Searches a sorted array for some number
 * Input params: arr - sorted int array, data - number to search for, start - starting location of array,
					end - ending location of array, compare - func. ptr. that determines whether array is ascending or descending
 * Return param: 1 if data is found in arr, 0 if not
 **/
int b_search(int *arr, int data, int start, int end, int(*compare)(int, int)){
	int mid = (start+end)/2;
	//Base case
	if(end < start){
		return 0;
	}
	//Determines if the value will be to the left or right of midpoint, 
	// 	creates subarray using recursion until value is found or all possible values have been inspected
	if(compare(*(arr+mid), data) < 0){
		return b_search(arr, data, start, mid-1, compare);
	}
	else if(compare(*(arr+mid), data) > 0){
		return b_search(arr, data, mid+1, end, compare);
	}
	else if(compare(*(arr+mid), data)==0){
		return 1;
	}
}
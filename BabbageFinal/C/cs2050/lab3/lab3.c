/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 3 - 2/12/13
 */
 
//Preprocess commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 //Global constants
 #define SIZE 100
 //Function prototypes
 int createarray(int** array, FILE *ptr);
 void sortarray(int* array, int size);
 int bsearcharray(int *array, int target, int size);
 void printarray(int* array, int size);
 
 /* Function Purpose: Execute all functions to produce a sorted integer array from a file, 
 *					  then ask user to input an int to search, return index or "not found"
 * Input params: argc, argv, number of input arguments and array pointer of input arguments
 * Return param: some integer
 **/
 int main(int argc, char **argv){
	FILE *fptr;
	int num_sentences, shift_length, index, target;
	char* num;
	num = malloc(4*sizeof(char));
	
	//1. Checks to make sure command line contains only one other argument (file name)
	if(argc != 2){
		printf("Only one command line argument allowed, terminating. \n\n");
		return 1;
	}
	
	//Opens file
	fptr = fopen(argv[1], "r");
	
	//Checks to make sure file was found
	if(fptr == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	//2. Declare int*array
	int* array;
	//3. Call of createarray and printarray
	int size = createarray(&array, fptr);
	printf("\nThe size of the array is %d\n---------------------------\n", size);
	printarray(array, size);
	//4. Sorting of array by sortarray and printed again by printarray
	sortarray(array, size);
	printf("---------------------------\nThe new sorted array\n---------------------------\n");
	printarray(array, size);
	//5. Asks user to input a target number, then uses bsearcharray to binary search for number. Prints index if found, or declares not found
	printf("Enter a number to search for: ");
	scanf("%d", &target);
	index = bsearcharray(array, target, size);
	if(index >=0){
		printf("\nThe target is found at index %d\n\n", index);
	}
	else{
		printf("\nThe target was not found\n\n");
	}
	//Free malloc'd pointer, close file.
	free(array);
	fclose(fptr);
	return 0;
 }
 /* Function Purpose: Creates an array of ints from a file. Also find the number of integers in the file to malloc required space.
 * Input params: array pointer and file to read from
 * Return param: number of integers found in the file
 **/
 int createarray(int** array, FILE *ptr){
	int tempSize = 0, endMarker = 0, count = 0, tempNum = 0, i;
	int tempPtr[SIZE];
	//Goes through file until the end of file and counts the number of ints.
	while(endMarker != EOF){
		endMarker = fscanf(ptr, "%d", &tempNum);
		tempPtr[count] = tempNum;
		tempSize++;
		count++;
	}
	//Rewinds file pointer to initial integer
	rewind(ptr);
	//Mallocs the exact amount of memory required.
	*array = malloc((tempSize-1)*sizeof(int));
	//Scans entire file and copies integers into int array.
	for(i=0;i<(tempSize-1);i++){
		fscanf(ptr, "%d", &tempNum);
		(*(*array+i))=tempNum;
	}
	return (tempSize-1);
}
/* Function Purpose: Sorts the array using insertion sort
 * Input params: integer array and size of array
 * Return param: none
 **/
void sortarray(int* array, int size){
	int i, j, save, save2;
	int curr_i;
	//Looks at each element of array
	for(i=1; i<size; i++){
		j = i-1;
		//Cycles through all the elements before the ith element to find sorted location for the original ith element
		while(*(array+j+1)>*(array+j)&&j>=0){
				save = *(array+j);
				*(array+j) = *(array+j+1);
				*(array+j+1) = save;
				j--;
		}
	}
}
/* Function Purpose: Uses binary searching to find some integer in an array
 * Input params: integer array, target serach value, and size of integer array
 * Return param: index of found value, or -1 if not found
 **/
int bsearcharray(int *array, int target, int size){
	int low, high, middle;
	low = 0;
	high = size -1;
	//Continues until the low value is greater than the high value, which would indicate the value was not found
	while(low <= high){
		middle = (low+high)/2;
		//Changes low index value if current middle is greater than search value
		if(*(array+middle)>target){
			low = middle+1;
		}
		//Changes high index value if current middle is less than search value
		else if(*(array+middle)<target){
			high = middle-1;
		}
		//If current middle value equals search value, returns its index
		else{
			return middle;
		}
	}
	//returns -1 if search value was never found
	return -1;
}
/* Function Purpose: Prints entire array of integers
 * Input params: integer array and size of integer array
 * Return param: none
 **/
void printarray(int* array, int size){
	int i;
	//Cycles through each element of array, prints
	for(i=0;i<size;i++){
		printf("%d\n",*(array+i));
	}
	printf("\n");
}
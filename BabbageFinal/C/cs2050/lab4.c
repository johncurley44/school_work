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
 int createArray(int** array, FILE *ptr);
 void mergeSort(int array[], int low, int high);
 void merge(int array[], int low, int middle, int high);
 int binarySearch(int array[], int key, int low, int high);
 void print_arr(int array[], int index, int size);

 /* Function Purpose: Calls functions to test
 * Input params: Number of command prompt inputs and array of those inputs
 * Return param: some int
 **/
 int main(int argc, char **argv){
	FILE *fptr;
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
	//Declare array
	int* array;
	//uses createArray to fill array
	int size = createArray(&array, fptr);
	//sorts array using mergeSort
	mergeSort(array, 0, size - 1);
	print_arr(array, 0, size - 1);
	//Asks for user input to search for number in sorted array using binary search
	printf("\nSearch for key: ");
	int key, index;
	scanf("%d", &key);
	index = binarySearch(array, key, 0, size-1);
	//Prints key if found or different message if it is not
	index != -1 ? printf("Key found at index %d\n\n", index) : printf("Key was not found.\n\n");
	//Free up malloc'd space for array
	free(array);
	return 0;
	
}
 /* Function Purpose: Creates an array of ints from a file. Also find the number of integers in the file to malloc required space.
 * Input params: array pointer and file to read from
 * Return param: number of integers found in the file
 **/
 int createArray(int** array, FILE *ptr){
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
/* Function Purpose: Splits array into subarrays until length(array) = 1 using recursion, calls merge
 * Input params: array of numbers, a low and high position in array for splitting
 * Return param: void
 **/
void mergeSort(int array[], int low, int high){
	int currSize = high - low + 1;
	//ends function when low index reaches high index
	if(low>=high){
		return;
	}
	//Uses recursion to split array into two parts and then each of those into two more parts until each array has 1 element
	else{
		int mid = ((high+low)/2);
		mergeSort(array, low, mid);
		mergeSort(array, mid+1, high);
		merge(array, low, mid, high);
	}
}	
/* Function Purpose: Merges two sorted arrays into one sorted array
 * Input params: array of numbers, a low, middle, and high position in array for sorting
 * Return param: void
 **/		
void merge(int array[], int low, int middle, int high){		
		int helpArray[high-low+1];
		int i;
		//Copies array into helpArray
		for(i = low; i <= high; i++){
			helpArray[i] = array[i];
		}
		int helperLeft = low;
		int helperRight = middle + 1;
		int current = low;
		//Continues until left index reaches past midpoint, or right index goes out of bounds
		while(helperLeft <= middle && helperRight <= high){
			//Places left element into array if largest of two, increments left index
			if(helpArray[helperLeft] > helpArray[helperRight]){
				array[current] = helpArray[helperLeft];
				helperLeft++;
			}
			//Places right element into array if largest of two, increments right index
			else if(helpArray[helperRight] > helpArray[helperLeft]){
				array[current] = helpArray[helperRight];
				helperRight++;
			}
			//increments current location of array no matter what
			current++;
		}
		//Once both helperLeft and helperRight have reached limits as in while loop above, either the right
		// or left half will still have elements needing to be added. The following two while loops do so.
		while(helperLeft <= middle){
			array[current] = helpArray[helperLeft];
			helperLeft++;
			current++;
		}
		while(helperRight <= high){
			array[current] = helpArray[helperLeft];
			helperRight++;
			current++;
		}
}
/* Uses binary searching methods to find a number in an array sorted in descending order
 * Input params: array of numbers, a number to search for, and a low and high position number for the array
 * Return param: index of number if found, -1 if not
 **/
int binarySearch(int array[], int key, int low, int high){
	//If current location in pointer is greater than the given end location, returns -1 to indicate number not found
	int mid = (low+high)/2;
	if(low>high){
		return -1;
	}
	//Divides array in half, uses recursion to re-search
	else if(key < array[mid]){
		low = mid + 1;
		return binarySearch(array, key, low, high);
	}
	else if(key > array[mid]){
		high = mid -1;
		return binarySearch(array, key, low, high);
	}
	//returns index if number is found
	else{
		return mid;
	}
}
/* Function Purpose: Prints one element at a time using recursion
 * Input params: array of numbers, index to print, total size of array
 * Return param: void
 **/
void print_arr(int array[], int index, int size){
	//stops function once index as reached the bounds of array	
	if(index>size){
		return;
	}
	//otherwise, prints current element, and uses recursion with the next index
	else{
		printf("%d\n", array[index]);
		print_arr(array, index+1, size);
	}
}

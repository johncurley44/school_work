/* John Curley
 * Prelab 4 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 int searchArray(int *array, int target, int start, int end);
 int factorial(int n);
 
 int main(void){
	int *array = malloc(5*sizeof(int));
	int i;
	for(i=0; i<5; i++){
		*(array+i) = i+1;
	}
	int target = 2;
	int start = 0;
	int end = 4;
	int index = searchArray(array, target, start, end);
	printf("Index of %d:  %d\n", target, index);
	int facNum = 10;
	printf("Factorial of %d:  %d\n", facNum, factorial(facNum));
 }
 //Ascending binary search
 int searchArray(int *array, int target, int start, int end){
	//If current location in pointer is greater than the given end location, returns -1 to indicate number not found
	int mid = (end+start)/2;
	if(start>end){
		return -1;
	}
	//Divides array in half
	
	else if(target > *(array+mid)){
		start = mid + 1;
		return searchArray(array, target, start, end);
	}
	else if(target < *(array+mid)){
		end = mid -1;
		return searchArray(array, target, start, end);
	}
	else{
		return mid;
	}
	
 }
 
 int factorial(int n){
	if(n >= 1)
		return n*factorial(n-1);
	else
		return 1;
}
/*
* Name: John Curley	 - jmcgdd
* CS3050  
* Machine Problem 3 - 10/18/2013
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100
#define MAX_NUM_STRING 
#define FALSE 0
#define TRUE 1
void max_heapify(int heap[], int heapval, int heapsize);
void build_max_heap(int heap[], int heapsize);
void print_heap(int heap[], int heapsize);
int insert(int heap[], int heapsize, int newNum);
int extract_max(int heap[], int heapsize);
void heap_change_key(int heap[], int heapPos, int newNum, int heapsize);
void heap_delete(int heap[], int heapPos, int heapsize);

int main(int argc, char **argv)
{
	FILE *input = NULL;
	int array_size = 0, numVer = 0, i;
	//Checks to make sure file was part of input
	if(argc != 2){
		printf("CurleyMachineProb3 <input-file>\n");
		return 1;
	}
	input = fopen(argv[1], "r");
	//if for Failure to open file, return error
	if(input == NULL){
		printf("File can not be opened.\n");
		return 2;
	}
	//Scanned value from file, to be inspected to determine if int or character
	int curVal;
	//the key to be inserted when 'I' is found
	int insertKey;
	//the location of the key to change and the new value of the key
	int changeLoc, newKey;
	//the location of the key to be deleted
	int deleteLoc;
	//temp charater storage to determine which function to perform
	char isChar = ' ';
	//Reads each line of file, stores the numbers in an array of edges
	int heapsize, extracted;
	fscanf(input, "%d", &heapsize);
	int inHeap[2*heapsize];
	for(i=0;i<heapsize;i++){
		fscanf(input, "%d",&inHeap[i+1]);
	}
	
	build_max_heap(inHeap, heapsize);
	
	while(!feof(input)){
		fscanf(input, "%c", &isChar);
		//printf("isalpha : %d\n", isalpha(isChar));
		if(isalpha(isChar) != FALSE && !feof(input)){
			//If file calls to extract max
			if(isChar == ('E')){
				extracted = extract_max(inHeap, heapsize);
				heapsize--;
			}
			//If file calls to insert a new key
			else if(isChar == ('I')){
				fscanf(input, "%d", &insertKey);
				heapsize = insert(inHeap, heapsize, insertKey);
				max_heapify(inHeap, heapsize+1, heapsize);
			}
			//If file calls to change a specific key
			else if(isChar == ('C')){
				fscanf(input, "%d", &changeLoc);
				fscanf(input, "%d", &newKey);
				heap_change_key(inHeap, changeLoc, newKey, heapsize);
			}
			//If file calls for a key to be deleted
			else if(isChar == ('D')){
				fscanf(input, "%d", &deleteLoc);
				heap_delete(inHeap, deleteLoc, heapsize);
				heapsize--;
			}
			//not a correct character
			else{
				printf("input character not E, I, C, or D\n\n");
			}
		}
		else{
		}	
	}
	//final heap
	print_heap(inHeap, heapsize);
	
}

//max_heapify works by looking at one element of a heap, and assuming that the binary trees on its left and right are max heaps,
//	but that the element may be smaller than its children, which would mean the entire heap is not a max heap. The algorithm then
//	floats the examined element down so that it is larger than all of its children.
void max_heapify(int heap[], int heapPos, int heapsize){
	int l = 2*heapPos;
	int r = 2*heapPos + 1;
	int largest;
	int temp;
	if(l <= heapsize && heap[l] > heap[heapPos]){
		largest = l;
	}
	else{
		largest = heapPos;
	}
	if(r<=heapsize && heap[r]>heap[largest]){
		largest = r;
	}
	if (largest != heapPos){
		temp = heap[heapPos];
		heap[heapPos] = heap[largest];
		heap[largest] = temp;
		max_heapify(heap, largest, heapsize);
	}
}
//build_max_heap simply takes a heap and max_heapifies elements 1-floor(n/2), thus making it a valid max heap.
void build_max_heap(int heap[], int heapsize){
	int i;
	for(i=heapsize/2; i > 0; i--){
		max_heapify(heap, i, heapsize);
	}
}
//This is just a print function that prints the final heap
void print_heap(int heap[], int heapsize){
	int i;
	printf("Heap :");
	for(i=1;i<=heapsize;i++){
		printf("%d ", heap[i]);
	}
	printf("\n");
}
//insert takes a new value and inserts it into the maximum heap so that it remains a maximum heap. It does this by inspecting heap
//	elements starting with the final value then checking each value at the previous value's index divided by 2 (floor). When the max
//	heap requirement that heap[i] <= heap[i/2] is obtained, the function inserts the new value in the observed location.
int insert(int heap[], int heapsize, int newNum){
	heapsize = heapsize + 1;
	int i = heapsize;
	while(i>1 && newNum > heap[i/2]){
		heap[i] = heap[i/2];
		i = i/2;
	}
	heap[i] = newNum;
	return heapsize;
}
//extract_max simply removes the first value of the heap (the max) and adjusts heap accordingly by moving the final value to the
//	beginning of the heap, then using the max_heapify function to place it appropriately within the heap to uphold max heap requirements
int extract_max(int heap[], int heapsize){
	int v = heap[1];
	heap[1] = heap[heapsize];
	heapsize = heapsize - 1;
	max_heapify(heap, 1, heapsize);
	return v;
}
//heap_change_key changes the value at a specified location to a new value. If the new value is greater than the old value, then it
//	is moved higher on the tree until it obeys the max heap requirements. If the new value is less than the old value, then the new 
//	value is immediately replaced by the new, and a max_heapify is called to move it down the tree until it obeys the max heap 
//	requirements.
void heap_change_key(int heap[], int heapPos, int newNum, int heapsize){
	if(newNum > heap[heapPos]){
		while(heapPos>1 && newNum > heap[heapPos/2]){
			heap[heapPos] = heap[heapPos/2];
			heapPos = heapPos/2;
		}
		heap[heapPos] = newNum;
	}
	else if(newNum < heap[heapPos]){
		heap[heapPos] = newNum;
		max_heapify(heap, heapPos, heapsize);
	}
}
//heap_delete simply removes a value at a specified position. It does this by reducing the size of the heap by one and changing the
//	deleted value to the last value in the heap using heap_change_key. This esentially moves the deleted value outside of the max
//	heap section of the number array.
void heap_delete(int heap[], int heapPos, int heapsize){
	heapsize--;
	heap_change_key(heap, heapPos, heap[heapsize+1], heapsize+1);
}
/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 9 - 4/16/2013
 */
 
  //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 //Definitions
 #define MAX_NUM_STR 25
 //tree struct definition
 typedef struct tree{
	int data;
	struct tree *left;
	struct tree *right;
 }b_tree;
//Function prototypes
void r_quicksort(int* arr, int start, int end);
int r_partition(int* arr, int start, int end);
b_tree *array_to_Tree(int *arr, int start, int end);
b_tree *create_Tree_Node(int data);
void print_in_Order(b_tree *X);
void freeTree(b_tree *root);
void displayTree(b_tree *root, int depth);
void padding(char toPrint, int numTimes);
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
	int i = 0, j, k;
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
	//Prints the array as read from file
	printf("Original Array: \n");
	for(j=0;j<elemNum;j++){
		printf("%d ", *(arr+j));
	}
	//Quicksorts the array, then prints in sorted order
	r_quicksort(arr, 0, elemNum-1);
	printf("\n\nSorted Array:\n");
	for(k=0;k<elemNum;k++){
		printf("%d ", *(arr+k));
	}
	printf("\n");
	//Creates balance BST from sorted array, displays tree and prints it in order
	b_tree *mainTree = array_to_Tree(arr, 0, elemNum-1);
	displayTree(mainTree, 0);
	printf("In order print:\n");
	print_in_Order(mainTree);
	//Frees each node in BST
	freeTree(mainTree);
	//Frees malloced integer array from earlier
	free(arr);
	return 0;
}
/* Function Purpose: Recursively creates a sorted array using quicksort
 * Input params: arr - integer array, start - first element or section to sort, end - last element of section to sort
 * Return param: none
 **/
void r_quicksort(int *arr, int start, int end){
	int pivot;
	//Base case
	if(start>end){
		return;
	}
	//Calls partition function to determine pivot point and sort based on pivot point
	pivot = r_partition(arr, start, end);
	//Recursively calls upon self to sort entire array
	r_quicksort(arr, start, pivot-1);
	r_quicksort(arr, pivot+1, end);
}
/* Function Purpose: Chooses a pivot at random, rearranges array into two parts based on the pivot, nums<pivot on left, nums>pivot on right
 * Input params: arr - integer array, start - first element or section to sort, end - last element of section to sort
 * Return param: position of pivot after rearranging
 **/
int r_partition(int* arr, int start, int end){
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
		if(*(arr+j) <= pivot)
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
/* Function Purpose: Turn a SORTED array of ints into a balanced BST
 * Input params: arr - integer array, start - first location, end - last location
 * Return param: root of BST
 **/
b_tree *array_to_Tree(int *arr, int start, int end){
		//Base Case for recursion
		if((end-start)<0){
			return NULL;
		}
		//Calculates midpoint of array
		int mid = (start+end)/2;
		//Creates a new node based on the midpoint
		b_tree *newNode = create_Tree_Node(*(arr+mid));
		//Uses recursion to cycle through entire tree
		newNode->left = array_to_Tree(arr, start, mid-1);
		newNode->right = array_to_Tree(arr, mid+1, end);
		return newNode;
}
/* Function Purpose: Mallocs space for a new b_tree node
 * Input params: data - integer to place into node
 * Return param: pointer to the new node
 **/
b_tree *create_Tree_Node(int data){
	//Malloc space for node
	b_tree *newNode = malloc(sizeof(b_tree));
	//Set the data equal to input, left and right pointers to null
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
/* Function Purpose: Prints a BST in-order
 * Input params: root of a BST
 * Return param: none
 **/
void print_in_Order(b_tree *X){
	//Copies BST root pointer into new pointer to traverse with
	b_tree *p = X;
	//Base Case
	if(!p){
		return;
	}
	//Recursion used to start at left most, lowest number, print in order
	print_in_Order(p->left);
	printf("%d ", p->data);
	print_in_Order(p->right);
}
/* Function Purpose: Frees all nodes in the given tree
 * Input params: root - the root of the tree to be freed
 * Return param: none
 **/
void freeTree(b_tree *root){
	//If null, exits function call
	if(!root){
		return;
	}
	//Recursively traverses left nodes, then right
	freeTree(root->left);
	freeTree(root->right);
	//Frees each node's memory
	free(root);
}
// Recursive function used with printTree. Provided for you; do not modify. You should
// not call this function directly. Instead, call printTree.
void displayTree(b_tree* root, int depth)
{
	if (root == NULL)
	{
		padding(' ', depth);
		printf("-\n");
		return;
	}

	displayTree(root->left, depth+4);
	padding(' ', depth);
	printf("%d\n", root->data);
	displayTree(root->right, depth+4);
}
// Prints out a character repeatedly. Provided for you; do not modify.
void padding(char toPrint, int numTimes)
{
	int i;
	for (i = 0; i < numTimes; i++)
		printf("%c", toPrint);
}

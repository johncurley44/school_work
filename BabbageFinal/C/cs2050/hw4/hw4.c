/*
* Name: John Curley	 - jmcgdd
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* HW4 - 5/6/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

// def BST node struct
typedef struct node_struct {
	int data;
	struct node_struct* left;
	struct node_struct* right;
} Node;

// prototypes
int isValidID(int* array, int arraySize, int data);
Node* createNode(int data);
Node* bstInsert(Node* root, int data);
Node* sortedArrayToBalancedBst(int* array, int startIndex, int endIndex);
int getBstHeight(Node* root);
// helper function prototypes
void bsort1(int values[], int numValues);
void padding(char ch, int n);
void displayTree(Node* root, int depth);

int main(int argc, char **argv)
{

	FILE *in = NULL;
	int num_read, array_size = 0;
		
	if(argc != 2){
		printf("hw4 <input-file>\n");
		return 1;
	}
	
	in = fopen(argv[1], "r");

	if(in == NULL){
		printf("File can not be opened.\n");
		return 2;
	}
	
	// declare the array
	int array[MAX_SIZE];	

	// read from the second line to get each element of the array
	while(!feof(in)){
		fscanf(in, "%d", &num_read);
		if(isValidID(array, array_size, num_read) == 0) {
			array[array_size] = num_read;
			array_size++;
			printf("%d added to array\n", num_read);
		}
		else if(isValidID(array, array_size, num_read) == 1) {
			printf("ERROR - %d bad ID. Not in range [0, 99].\n", num_read);
		}
		else if(isValidID(array, array_size, num_read) == 2) {
			printf("ERROR - %d bad ID. Duplicate.\n", num_read);
		}		
	}
	fclose(in);
	
	Node *root1 = NULL, *root2 = NULL, *root3 = NULL;

	int i;
	// task1: construct a bst from the unsorted array
	printf("=== task1: construct a bst from the unsorted array ===\n");
	for (int i = 0; i < array_size; i++) {
		root1 = bstInsert(root1, array[i]);
	}
	displayTree(root1, 0);
	printf("Height of bst1 is %d\n", getBstHeight(root1));

	// task2: sort the array and use the sorted array to construct a bst, each time taking an element in order
	printf("=== task2: sort the array and use the sorted array to construct a bst ===\n");
	bsort1(array, array_size);
	for (i = 0; i < array_size; i++) {
		root2 = bstInsert(root2, array[i]);
	}
	displayTree(root2, 0);
	printf("Height of bst2 is %d\n", getBstHeight(root2));	
	
	// task3: use the sorted array to construct a balanced bst
	printf("=== task3: use the sorted array to construct a balanced bst ===\n");
	root3 = sortedArrayToBalancedBst(array, 0, array_size-1);
	displayTree(root3, 0);
	printf("Height of bst3 is %d\n", getBstHeight(root3));	
	
	return 0;
}

/* This function will examine the ID field and verify that the ID entered is valid.  
 * To be a valid ID:
 * 1). it must be an integer value between 00 and 99 (inclusive), and
 * 2). it doesn't exist in the array
 * Parameters:
 * array - the int array of existing IDs
 * arraySize - the size of the array
 * data - the ID to be verified
 * Returns:
 * 0 - data is valid; 1 - data is too ; 2 - data is a duplicate
 */
int isValidID(int* array, int arraySize, int data) {
	int i;
	//Returns 1 if the data is outside the allowed range
	if(data < 0 || data > 99){
		return 1;
	}
	//Returns 2 if the data is a duplicate from the array
	for(i=0; i<arraySize; i++){
		if(*(array+i) == data){
			return 2;
		}
	}
	//Returns 0 if valid value
	return 0;
}

/* This function mallocs space for a node, copies the data provided into the data field of the node, and returns a pointer to the node. 
 * Since the newly created node does not have any children, you need to set its children to NULL.
 * Parameters: 
 * data - the integer value used to construct a new node
 * Returns:
 * the pointer to the new node
 */
Node* createNode(int data) {
	//Mallocs newNode
	Node* newNode = malloc(sizeof(Node));
	//Sets data and left and right pointers to values/NULL
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/* This function takes data to form a new node, adds the node to the BST, and returns a pointer to the new BST.
 * Before and after you execute the function, BST should always satisfy: node->left->data <= node->data < node->right->data
 * Parameters: 
 * root - the pointer to the original root node of a bst
 * data - the integer value used to construct the to-be-inserted node
 * Returns:
 * the pointer to the root node of the new bst
 */
Node* bstInsert(Node* root, int data) {
	
	Node* curNode = root;
	Node* newNode = createNode(data);
	Node* prevNode = NULL;
	//If first node, returns node just created
	if(!curNode){
		return newNode;
	}
	//Loops until NULL in proper location
	while(curNode){
		//If the new node number<observed node, go to left
		if(newNode->data < curNode->data){
			prevNode = curNode;
			curNode = curNode->left;
		}
		//New node number>=observed, go to right
		else{
			prevNode = curNode;
			curNode = curNode->right;
			//prevNode->right = curNode;
		}
	}
	//Sets pointers to new nodes
	if(prevNode->data > newNode->data){
		prevNode->left = newNode;
	}
	else{
		prevNode->right = newNode;
	}
	return root;
	
}

/* This function takes a sorted array with a range and returns a balanced BST.
 * Hint: think about how we did binary search. Each time take the middle element to form the node. Construct its children recursively.
 * Parameters: 
 * array - the array provides the data fields of nodes of bst. Assume it's already sorted.
 * startIndex & endIndex - only elements in the range defined by them (inclusive) will used to construct the bst
 * Returns:
 * the pointer to the root of the balanced bst
 */
Node* sortedArrayToBalancedBst(int* array, int startIndex, int endIndex) {
		//Base Case
		if((endIndex-startIndex)<0){
			return NULL;
		}
		//Calculates midpt of array
		int mid = (startIndex+endIndex)/2;
		//Creates a new node based on the midpt
		Node* newNode = createNode(*(array+mid));
		//Uses recursion to cycle through tree
		newNode->left = sortedArrayToBalancedBst(array, startIndex, mid-1);
		newNode->right = sortedArrayToBalancedBst(array, mid+1, endIndex);
		return newNode;

}

/* This function returns the height of a BST
 * Parameters: 
 * root - the pointer to the root node of a bst
 * Returns:
 * the height of the bst. An empty bst (root is NULL) has a height of 0.
 */
int getBstHeight(Node* root) {
	//Returns 0 for base case
	if(!root){
		return 0;
	}
	//Double binary search to get height
	int leftNode = getBstHeight(root->left);
	int rightNode = getBstHeight(root->right);
	//Increments counters when traversing left or right, eventually returns total height
	if(leftNode > rightNode){
		return leftNode + 1;
	}
	else{
		return rightNode + 1;
	}
}


/* helper function to sort an array */
void bsort1(int values[], int numValues)
{
	
	int swapped = 0;
	int i;
	int temp;

	do
	{
		swapped = 0;
		
		for (i = 1; i < numValues; i++)
		{
			
			if (values[i - 1] > values[i])
			{
				// swap values
				temp = values[i];
				values[i] = values[i - 1];
				values[i - 1] = temp;

				swapped = 1;
			}
		}
	} while(swapped);

}

/* helper functions to print a bst; You just need to call displayTree when visualizing a bst */
void padding(char ch, int n){
    int i;
    for (i = 0; i < n; i++)
        printf("%c%c%c%c", ch, ch ,ch, ch);
}

void displayTree(Node* root, int depth){
    if (root == NULL) {
        padding (' ', depth);
        printf("-\n");
    }
    else {
        displayTree(root->right, depth+1);
        padding(' ', depth);
        printf ( "%d\n", root->data);
        displayTree(root->left, depth+1);
    }
}






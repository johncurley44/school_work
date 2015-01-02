/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* HW3
* IF BONUS COMPLETED, COMMENT HERE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data structure for a binary search tree.
typedef struct tree {
	int data;
	struct tree* left;
	struct tree* right;
} Tree;

// Data structure for a linked list.
typedef struct list {
	int data;
	struct list* next;
} List;

// Prototypes
Tree* createTreeNode(int data);
Tree* insertToTree(Tree* root, int data);
void reflectTree(Tree* root);
int searchTree(Tree* root, int data);
int getBstHeight(Tree* root);
void freeTree(Tree* root);

List* createListNode(int data);
List* flattenTreeToList(Tree* root);
void freeList(List* head);

// These functions have already been implemented for you.
void printTree(Tree* root);
void printList(List* head);
void padding(char toPrint, int numTimes);
void displayTree(Tree* root, int depth);

// Main function. 
int main(int argc, char** argv)
{
	FILE* fPtr;
	char tempStr[5], tempDataStr[5];
	int tempData, searchNum, searchResult, endMarker = 0;
	Tree* mainTree = NULL;
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
	
	// Read and parse lines from file; creates tree nodes, inserts them
	
	while(fgets(tempStr, 50, fPtr)){
		strcpy(tempDataStr, strtok(tempStr, " "));
		tempData = atoi(tempDataStr);
		mainTree = insertToTree(mainTree, tempData);
	}
		
	//Closes file
	fclose(fPtr);
	//Gets height of tree and prints
	printf("\nOriginal Tree has height: %d\n\n", getBstHeight(mainTree));
	//Prints original tree
	printTree(mainTree);
	//Asks user to input number to search for, indicates if found
	printf("\nEnter a number to search for: ");
	scanf("%d", &searchNum);
	searchResult = searchTree(mainTree, searchNum);
	if(searchResult == 1){
		printf("\nTarget found in tree\n\n");
	}
	else{
		printf("Target not found in tree\n\n");
	}
	//Creates singly linked list from tree, prints as list
	List* mainList = flattenTreeToList(mainTree);
	printf("Flattened list: \n\n");
	printList(mainList);
	//Reflects tree and prints it
	reflectTree(mainTree);
	printf("\nReflected Tree: \n\n");
	printTree(mainTree);
	//Frees tree and list allocated
	freeTree(mainTree);
	freeList(mainList);

	return 0;
}

// Creates a new tree node with the given data.
//
// INPUT: data - The data to fill the tree node with.
// OUTPUT: Returns a new Tree object, allocated with malloc.
Tree* createTreeNode(int data)
{
	//Mallocs new Tree, sets data to input data, left and right pointers to null
	Tree* newTree = malloc(sizeof(Tree));
	newTree->data = data;
	newTree->left = NULL;
	newTree->right = NULL;
	return newTree;
}

// Inserts the value provided into the given tree. Should
// follow the rule that smaller values are inserted into the
// left side of the tree; all other values are inserted into the
// right side of the tree.
//
// INPUT: root - The root of a tree to insert into, or
//               NULL if no tree yet exists.
//        data - The data to be inserted into the tree.
//
// OUTPUT: Returns the root of a tree containing the
//         newly inserted value.
Tree* insertToTree(Tree* root, int data)
{
	Tree* curNode = root;
	Tree* newNode = createTreeNode(data);
	Tree* prevNode = NULL;
	//If there are no nodes yet, return node just created
	if(!curNode){
		return newNode;
	}
	//Loop continues until NULL in proper location
	while(curNode){
		//If the new node number is less than observed node, go to left
		if(newNode->data < curNode->data){
			prevNode = curNode;
			curNode = curNode->left;
		}
		//New node number greater or equal, go to right
		else{
			prevNode = curNode;
			curNode = curNode->right;
			//prevNode->right = curNode;
		}
	}
	//Sets pointers to new nodes accordingly
	if(prevNode->data > newNode->data){
		prevNode->left = newNode;
	}
	else{
		prevNode->right = newNode;
	}
	return root;
}

// Searches the given tree for the value provided.
//
// INPUT: root - The root of a tree to search through.
//        data - The data to search for.
//
// OUTPUT: Returns 1 if the data is found in the tree,
//         or -1 otherwise.
int searchTree(Tree* root, int data)
{
	Tree *curNode = root;
	//If root is null, return error statement
	if(!curNode){
		printf("\nRoot = NULL\n");
		return -1;
	}
	//Until Null node encountered
	while(curNode){
		//traverses tree based on input data
		if(data < curNode->data){
			curNode = curNode->left;
		}
		else if(data > curNode->data){
			curNode = curNode->right;
		}
		else{
			return 1;
		}
	}
	return -1;
}

// Determines the height of the tree. (Remember that a tree's
// height is the longest path from the root of the tree until
// reaching a leaf node.)
//
// INPUT: root - The root of the tree to find the height of.
// OUTPUT: Returns the height of the tree. A NULL tree should
//         be considered as having as a height of 0.
int getBstHeight(Tree* root)
{
	//Returns 0 for base case
	if(!root){
		return 0;
	}
	//Double binary search to find height
	int leftNode = getBstHeight(root->left);
	int rightNode = getBstHeight(root->right);
	//Increments respective counter when traversing left or right, eventually returns total height
	if(leftNode > rightNode){
		return leftNode + 1;
	}
	else{
		return rightNode + 1;
	}
}

// Creates a new list node with the given data.
//
// INPUT: data - The data to fill the list node with.
// OUTPUT: Returns a new List object, allocated with malloc.
List* createListNode(int data)
{
	//Mallocs new list node, sets data to input, sets next pointer to null
	List* newList = malloc(sizeof(List));
	newList->data = data;
	newList->next = NULL;
	return newList;
}

// Turns a Tree into a List in sorted order.
//
// INPUT: root - The root of a Tree which will be flattened.
// OUTPUT: Returns a pointer to the head of a list, which contains
//         the values of the tree in sorted order.
//
// NOTE: You should not be performing any actual "sorting" aside from
//       taking advantage of the order of the tree. Do not add the nodes
//       from the tree to the list in some random order and then sort the
//       list.
List* flattenTreeToList(Tree* root)
{
	List* newList;
	static List* listHead = NULL;
	List* prev = NULL;
	static List* currList = NULL;
	//Returns head when recursion reaches null node
	if(!root){
		return listHead;
	}
	//Recursively traverses left nodes
	listHead = flattenTreeToList(root->left);
	//Creates new List node to add
	newList = createListNode(root->data);
	//If first list node, makes it the current list node and the head list node
	if(!listHead){
		currList = newList;
		listHead = currList;
	}
	//If not first node
	else{
		//Traverses to end of list, saving previous node each step
		while(currList){
			prev = currList;
			currList = currList->next;
		}
		//Connects previous pointer to new list node
		prev->next = newList;
		//Sets current list to the recently appended list
		currList = newList;
	}
	//Recursively traverses right nodes
	listHead = flattenTreeToList(root->right);
	return listHead;
}

// Frees all nodes in the given tree.
//
// INPUT: root - The root of the tree to be freed.
void freeTree(Tree* root)
{
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

// Frees all nodes in the given list.
//
// INPUT: list - The head of a list to be freed.
void freeList(List* head)
{
	//If null, exits function call
	if(!head){
		return;
	}
	//Recursively traverses list
	freeList(head->next);
	//Frees each node's memory
	free(head);
}

// Reflects a tree such that the sortedness of the tree
// is exactly reversed: a tree sorted left-to-right will
// become sorted right-to-left, and vice versa.
//
// INPUT: root - The root of a tree to reverse.
void reflectTree(Tree* root)
{
	//Switches left and right nodes
	Tree* saveLeft = root->left;
	root->left = root->right;
	root->right = saveLeft;
	//If there is a node to the left, uses recursion to flip its subordinate nodes
	if(root->left){
		reflectTree(root->left);
	}
	//If there is a node to the right, uses recursion to flip its subordinate nodes
	if(root->right){
		reflectTree(root->right);
	}
}

// Prints out a tree. The tree is displayed horizontally; its root is at the left,
// with its branches spreading out to the right (up, on the screen) and left (down,
// on the screen). Provided for you; do not modify.
void printTree(Tree* root)
{
	displayTree(root, 0);
}

// Prints out a linked list. Provided for you; do not modify.
void printList(List* head)
{
	while (head != NULL)
	{
		printf("%d -> ", head->data);
		head = head->next;
	}

	printf("NULL\n");
}

// Recursive function used with printTree. Provided for you; do not modify. You should
// not call this function directly. Instead, call printTree.
void displayTree(Tree* root, int depth)
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

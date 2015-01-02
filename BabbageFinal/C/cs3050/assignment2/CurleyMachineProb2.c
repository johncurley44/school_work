/*
* Name: John Curley	 - jmcgdd
* CS3050
* Machine Problem 2 - 9/25/2013
* 
*/

/* 	ALGORITHM EXPLANATION:	My algorithm uses a DFS similar to that of a topological sort. However, instead of detecting back edges (cycles) and quitting,
 *		my algorithm builds the array of sorted vertices and saves each vertex's location to an integer as part of the Vertex structure. Then,
 * 		it looks at each vertex and uses a reversed adjacency list to determine if every vertex with an incoming edge shares at least one of the incoming edges
 *		with a vertex with a lower NUM value. In my algorithm, the NUM value is essentially the locate value of each vertex, which corresponds with that vertex's
 *		location in the modified topologically sorted array. If at any time a vertex has at least one incoming edge, but none from vertices with a lower NUM value,
 *		the while loop stops and "NO" will be printed. Otherwise, all vertices obey the constraint and "YES" is printed.
 * 	
 * 	
 *	LINEAR EXPLANATION:		This algorithm runs in linear time. The DFS walk takes exactly |V| + |E| to run as the outside for loop (the one outside my function)
 *		guarentees that every vertex is looked at and the inner while loop guarentees that the entire adjacency matrix is looked at (each edge). Additionally,
 * 		the part of my algorithm that determines whether or not incoming edges are from vertices with lower NUM values can take up to |V| + |E| due to
 *		potentially observing every vertex and each adjacent vertex. Even so, this algorithm will worst case scenario still run in linear time at 2(|V| + |E|).
 * 	
 *
 **/
 
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000
#define FALSE 0
#define TRUE 1
#define WHITE 0
#define BLACK 1
#define GRAY 2

//Edge struct, contains 2 vertices as ints
typedef struct edge {
	int v1;
	int v2;
} Edge;
//Vertex struct with vertex value, color, deg, and locate as integers and a pointer to next vertex for lists
typedef struct vertex{
	int ver;
	int color;
	int deg;
	int locate;
	struct vertex* next;
}Vertex;

//Function Prototypes

Vertex* createVertex(int verVal);
void addVertexToAdjList(Vertex* adjList[], Edge inEdge);
void addVertexToAdjListReverse(Vertex* adjList[], Edge inEdge);
int walkDFS(Vertex* adjList[], Vertex* listForWalk[], int u, Vertex* buildList[], int numVer);
void printAdjList(Vertex* adjList[], int adjSize);
void freeVerArray(Vertex* head);

//Main program that constructs a full adjacency list from file of edges, then tests to see if it is a simple cycle graph
int main(int argc, char **argv)
{
	FILE *input = NULL;
	int array_size = 0, numVer = 0, i;
	Edge tempEdge;
	int isSimple = FALSE;
	int simpCheckDeg = 0;
	//Checks to make sure file was part of input
	if(argc != 2){
		printf("CurleyMachineProb2 <input-file>\n");
		return 1;
	}
	input = fopen(argv[1], "r");
	//if for Failure to open file, return error
	if(input == NULL){
		printf("File can not be opened.\n");
		return 2;
	}
	// declare the array or edges
	Edge edgeArray[MAX_SIZE];	
	//Reads each line of file, stores the numbers in an array of edges
	while(!feof(input)){
		fscanf(input, "%d", &tempEdge.v1);
		//Makes numVer (number of vertices) equal to the largest numbered vertex
		if(tempEdge.v1 > numVer){
			numVer = tempEdge.v1;
		}
		fscanf(input, "%d", &tempEdge.v2);
		//Makes numVer (number of vertices) equal to the largest numbered vertex
		if(tempEdge.v2 > numVer){
			numVer = tempEdge.v2;
		}
		edgeArray[array_size] = tempEdge;
		array_size++;		
	}
	fclose(input);
	Vertex *adjList[numVer]; 
	Vertex *adjListReverse[numVer];
	Vertex *listForWalk[numVer];
	Vertex *buildList[numVer];
	//Malloc space for each adjList pointer needed. Set som values equal to default values.
	for(i=0;i<numVer;i++){
		adjList[i] = malloc(sizeof(Vertex));
		adjList[i]->ver = 0;
		adjListReverse[i] = malloc(sizeof(Vertex));
		adjListReverse[i]->ver = 0;
		listForWalk[i] = malloc(sizeof(Vertex));
		listForWalk[i]->ver = i+1;
		listForWalk[i]->color = WHITE;
		listForWalk[i]->deg = 0;
		buildList[i] = malloc(sizeof(Vertex));
	}
	//Adds the vertices from the edge list to adjacency list and reverse adjacency list
	for(i=0;i<array_size;i++){
		addVertexToAdjList(adjList, edgeArray[i]);
		addVertexToAdjListReverse(adjListReverse, edgeArray[i]);
	}
	
	//Call the DFS walk function to do walk/check for constraints and build a modified topologically sorted (ignoring back edges) array
	//	DFS will be called a total of |V| + |E| times because the for statement here ensures every vertex is called exactly once,
	//	and the recursive statement in the walkDFS function ensures every edge is checked from the adjacency list.
	int vertCount = 0;
	for(i=0;i<numVer;i++){
		if(listForWalk[i]->color == WHITE){
			vertCount = walkDFS(adjList, listForWalk, i, buildList, numVer);
		}
	}
	
	int shouldCont = TRUE;
	int total = 0;
	//Goes through each vertex and looks at the reversed adjacency list to check and see if every vertex with incoming edges has at least one from a smaller NUM value
	//	the NUM value here is represented by the location of the vertex in the array formed from the walkDFS function.
	while(shouldCont == TRUE){
		//checks every vertex
		for(i=0;i<numVer;i++){
			Vertex *curr = adjListReverse[(buildList[i]->ver)-1];
			int checkVal = 0, wrongWay = 0;
			//While there are incoming edges to explore still
			while(curr && (curr->ver > 0)){
				//If incoming vertex's NUM is lower (positioned earlier in array) than the current vertex
				if((listForWalk[(curr->ver)-1]->locate) < (listForWalk[(buildList[i]->ver)-1]->locate)){
					checkVal++;
				}
				//If the incoming vertex's NUM is higher
				else{
					wrongWay++;
				}
				//Go to next adjacent vertex
				curr = curr->next;
			}
			//If the vertex has no incoming vertices, or has at least one incoming vertex with a smaller NUM, add one to a total tracker
			if(checkVal > 0 || wrongWay == 0){
				shouldCont = TRUE;
				total++;
			}
			//If a vertex is found to have incoming edge(s) but none of the NUMS are smaller, stop calculating, quit
			else{
				shouldCont = FALSE;
			}
		}
		shouldCont = FALSE;
	}		
	// Check to see if graph is orderable by the modified topological sort with the given constraint 
	//	(each vertex with an incoming edge must have at least one predecessor with a "lesser num value"
	
	//If every vertex is reachable from a source (each vertex with incoming edge has a NUM less than at least one incoming vertex)
	if(total == numVer){
		printf("\nYES\n\n");
	}
	//If not every incoming vertex satisfied the constraint.
	else{
		printf("\nNO\n\n");
	}
	//Frees the allocated memory
	freeVerArray(adjList[0]);
	freeVerArray(listForWalk[0]);
	freeVerArray(adjListReverse[0]);
	freeVerArray(buildList[0]);
	
}

/* Function Purpose: Creates Vertex and sets its vertex value
 * Input params: int verVal - value of vertex
 * Return param: new Vertex structure pointer
 **/
Vertex* createVertex(int verVal){
	Vertex* newVer = malloc(sizeof(Vertex));
	newVer->ver = verVal;
	newVer->next = NULL;
	return newVer;
}

/* Function Purpose: Adds the two vertices from an edge to an adjacency list 
 * Input params: Vertex* adjList[]- adjacency list pointer, Edge inEdge - edge structure with two vertices values (ints)
 * Return param: void
 **/
void addVertexToAdjList(Vertex* adjList[], Edge inEdge){
	Vertex* curVer;
	Vertex* prevVer = NULL;
	Vertex* saveHead = NULL;
	int quitFlag = FALSE;
	//Sets location values for adjacency array (loc 0 in array is for vertex value = 1)
	int v1Loc = inEdge.v1-1;
	//Creates vertices for the two vertices in the edge input
	Vertex* newVer = createVertex(inEdge.v2);
	
	/*Start looking at the first adjacent vertex to Edge.v1*/
	
	curVer = adjList[v1Loc];
	//Adds Edge.v2 to adjacency list for Edge.v1	
	while(quitFlag == FALSE){
		//initial vertex setting of each value equal to 0, so if still blank, fills with new vertex
		if(curVer->ver == 0){ 
			adjList[v1Loc] = newVer;
			adjList[v1Loc]->deg++;
			quitFlag = TRUE;
		}
		
		//there is at least one vertex already in the current element in the adjacency list
		else if(curVer->ver > 0){
			//if there is another vertex in the list, move on to next vertex in list
			if(curVer->next){
				prevVer = curVer;
				curVer = curVer->next;
			}
			//if this is the last vertex in the list, add new vertex to adjacency list
			else{
				curVer->next = newVer;
				adjList[v1Loc]->deg++;
				quitFlag = TRUE;
			}	
		}
		//Prints if issue in logic 
		else{
			printf("Problem in code");
		}
	}
	
}
/* Function Purpose: Adds the two vertices from an edge to an adjacency list (reverse order to look at sources)
 * Input params: Vertex* adjList[]- adjacency list pointer, Edge inEdge - edge structure with two vertices values (ints)
 * Return param: void
 **/
void addVertexToAdjListReverse(Vertex* adjList[], Edge inEdge){
	Vertex* curVer;
	Vertex* prevVer = NULL;
	Vertex* saveHead = NULL;
	int quitFlag = FALSE;
	//Sets location values for adjacency array (loc 0 in array is for vertex value = 1)
	int v2Loc = inEdge.v2-1;
	//Creates vertices for the two vertices in the edge input
	Vertex* newVer = createVertex(inEdge.v1);
	
	/*Start looking at the first adjacent vertex to Edge.v2*/
	
	curVer = adjList[v2Loc];
	//Adds Edge.v1 to adjacency list for Edge.v2	
	while(quitFlag == FALSE){
		//initial vertex setting of each value equal to 0, so if still blank, fills with new vertex
		if(curVer->ver == 0){ 
			adjList[v2Loc] = newVer;
			adjList[v2Loc]->deg++;
			quitFlag = TRUE;
		}
		
		//there is at least one vertex already in the current element in the adjacency list
		else if(curVer->ver > 0){
			//if there is another vertex in the list, move on to next vertex in list
			if(curVer->next){
				prevVer = curVer;
				curVer = curVer->next;
			}
			//if this is the last vertex in the list, add new vertex to adjacency list
			else{
				curVer->next = newVer;
				adjList[v2Loc]->deg++;
				quitFlag = TRUE;
			}	
		}
		//Prints if issue in logic 
		else{
			printf("Problem in code");
		}
	}
	
}
/* Function Purpose: Performs a DFS walk of adj. list to form modified topological sorted array
 * Input params: Vertex* adjList[] - adjacency list head pointer, Vertex* listForWalk[] - list of vertices to check for simple graph, int u - vertex location to start, 
 *					Vertex* buildList[] - modified topologically sorted array, int numVer - total number of vertices in graph
 * Return param: int vertCount - number of vertices that have been visited by walk 
 **/
int walkDFS(Vertex* adjList[], Vertex* listForWalk[], int u, Vertex* buildList[], int numVer){
	int static vertCount = 0;
	int static loc = 1;
	listForWalk[u]->color = GRAY;
	Vertex *curr = adjList[u];
	//For each adjacent vertex of listForWalk[u]
	while(curr && (curr->ver > 0)){
		//If unvisited, recursively call
		if(listForWalk[(curr->ver)-1]->color == WHITE){
			vertCount = walkDFS(adjList, listForWalk, (curr->ver)-1, buildList, numVer);	
		}
		curr = curr->next;
	}
	//Make vertex color black
	listForWalk[u]->color = BLACK;
	//Save vertex's location in buildList array
	listForWalk[u]->locate = numVer - loc;
	buildList[numVer - (loc)] = listForWalk[u];
	loc++;
	return vertCount;
}
/* Function Purpose: Prints the adjacency list
 * Input params: Vertex* adjList[] - adjacency list head pointer, int adjSize - number of vertices in adjacency list (length of array)
 * Return param: void
 **/
void printAdjList(Vertex* adjList[], int adjSize){
	//Copies head into p to traverse
	Vertex* p;
	int i;
	printf("Vertex     Adj list\n");
	//Traverse each address in adj list and print
	for(i=0;i<adjSize;i++){
		printf("\n%-2d-------> ", i+1);
		for(p = adjList[i]; p != NULL; p = p->next){
			printf("%-1d--> ", p->ver);
		}
	}
	printf("\n\n");
}

/* Function Purpose: Frees memory of Vertex* values recursively
 * Input params: Vertex* head - head of some Vertex array
 * Return param: void
 **/
void freeVerArray(Vertex* head){
	//Recursively clears list
	if(head->next){
		freeVerArray(head->next);
		free(head);
	}
}
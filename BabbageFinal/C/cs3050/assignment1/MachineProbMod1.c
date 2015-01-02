/*
* Name: John Curley	 - jmcgdd
* CS3050
* Machine Problem 1 - 9/3/2013
* 
*/

/* ALGORITHM EXPLANATION:
 * 	My algorithm will start by reading in a file containing a list of vertices as edge. It stores each of these
 * 	edges in an Edge struct that contains 2 vertices as integers. These edges are then stored in an array of
 * 	and passed into a function that adds vertices to an adjacency list. It does so by looking at one edge,
 *	adding the first vertex to the second's adj. list and vice versa. It also keeps track of the degree of each
 *	vertex. My algorithm then adds each vertex to a separate list to keep track of vertex properties during a 
 *  walk. The walk is a BFS that works by looking at some vertex at the head of an adjacency list for a specific vertex, 
 *  then checking to see if it has been visited, if so it goes to next vertex, if not, the program starts to 
 *	look at a new vertex's adjacency list (new vertex is the current vertex being observerd in previous vertex's
 *  adjacency list). The walk also keeps track of number of visited vertices. A check is then performed to see
 *	if every vertex is visited (cycle) and every vertex has degree = 2 (simple).
 * 	
 *	LINEAR EXPLANATION:
 * 	This algorithm is implemented in linear time because the walk is structured in a way that it only visits
 *	each vertex in the adjacency list once because of the visited check (Black or white). Therefore, because 
 *	the algorithm is only run over {V,E}, without overlapping, the algorithm runs in linear time.
 *
 **/


 
 //look for better way than setting =-99 to start, implement walk function???

 
 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define FALSE 0
#define TRUE 1
#define WHITE 0
#define BLACK 1

//Edge struct, contains 2 vertices as ints
typedef struct edge {
	int v1;
	int v2;
} Edge;
//Vertex struct with vertex value, color and deg as integers and a pointer to next vertex for lists
typedef struct vertex{
	int ver;
	int color;
	int deg;
	struct vertex* next;
}Vertex;

//Function Prototypes

Vertex* createVertex(int verVal);
void addVertexToAdjList(Vertex* adjList[], Edge inEdge);
int walkBFS(Vertex* adjList[], Vertex* listForWalk[]); 
void printAdjList(Vertex* adjList[], int adjSize);
void freeVerArray(Vertex* head);

//Main program that constructs a full adjacency list from file of edges, then tests to see if it is a simple cycle graph
int main(int argc, char **argv)
{
	FILE *in = NULL;
	int array_size = 0, numVer = 0, i;
	Edge tempEdge;
	int isSimple = FALSE;
	int simpCheckDeg = 0;
	//Checks to make sure file was part of input
	if(argc != 2){
		printf("hw4 <input-file>\n");
		return 1;
	}
	in = fopen(argv[1], "r");
	//if for Failure to open file, return error
	if(in == NULL){
		printf("File can not be opened.\n");
		return 2;
	}
	// declare the array or edges
	Edge edgeArray[MAX_SIZE];
	//Reads each line of file, stores the numbers in an array of edges
	while(!feof(in)){
		fscanf(in, "%d", &tempEdge.v1);
		//Makes numVer (number of vertices) equal to the largest numbered vertex
		if(tempEdge.v1 > numVer){
			numVer = tempEdge.v1;
		}
		fscanf(in, "%d", &tempEdge.v2);
		//Makes numVer (number of vertices) equal to the largest numbered vertex
		if(tempEdge.v2 > numVer){
			numVer = tempEdge.v2;
		}
		edgeArray[array_size] = tempEdge;
		array_size++;		
	}
	fclose(in);
	Vertex *adjList[numVer]; 
	Vertex *listForWalk[numVer];
	//Malloc space for each adjList pointer and listForWalk pointer, make first vertex in each location equal to that number
	for(i=0;i<numVer;i++){
		adjList[i] = malloc(sizeof(Vertex));
		adjList[i]->ver = -99;
		listForWalk[i] = malloc(sizeof(Vertex));
		listForWalk[i]->ver = i+1;
		listForWalk[i]->color = WHITE;
		listForWalk[i]->deg = 0;
	}
	//Adds the vertices from the edge list to adjacency list
	for(i=0;i<array_size;i++){
		addVertexToAdjList(adjList, edgeArray[i]);
	}
	printAdjList(adjList, numVer);
	
	//Call the BFS walk function to do walk/check for cycle
	int vertCount = walkBFS(adjList, listForWalk);

	/*Check for Simple Graph*/
	
	//If every vertex has been visited
	if(vertCount==numVer){
		//Check each vertex to see if degree is two
		for(i=0;i<numVer;i++){
			if(adjList[i]->deg == 2){
				simpCheckDeg++;
			}
		}
		//If every vertex has degree 2 and has been visited, graph is a simple cycle
		if(simpCheckDeg == numVer){
			printf("\nYES\n");
		}
		//If any vertex has degree != 2, not simple
		else{
			printf("\nNO\n");
		}
	}
	//If not every vertex was visited in walk, graph not a cycle
	else{
		printf("\nNO\n");
	}
	//Frees the allocated memory
	freeVerArray(adjList[0]);
	freeVerArray(listForWalk[0]);
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
	int quitFlag1 = FALSE, quitFlag2 = FALSE;
	//Sets location values for adjacency array (loc 0 in array is for vertex value = 1)
	int v1Loc = inEdge.v1-1;
	int v2Loc = inEdge.v2-1;
	//Creates vertices for the two vertices in the edge input
	Vertex* newVer1 = createVertex(inEdge.v1);
	Vertex* newVer2 = createVertex(inEdge.v2);
	
	/*Start looking at the first adjacent vertex to Edge.v1*/
	
	curVer = adjList[v1Loc];
	//Adds Edge.v2 to adjacency list for Edge.v1	
	while(quitFlag1 == FALSE){
		//initial vertex setting of each value equal to -99, so if still blank, fills with new vertex
		if(!curVer){ 
			adjList[v1Loc] = newVer2;
			adjList[v1Loc]->deg++;
			quitFlag1 = TRUE;
		}
		
		//there is at least one vertex already in the current element in the adjacency list
		else{
			//if there is another vertex in the list, move on to next vertex in list
			if(curVer->next){
				prevVer = curVer;
				curVer = curVer->next;
			}
			//if this is the last vertex in the list, add new vertex to adjacency list
			else{
				curVer->next = newVer2;
				adjList[v1Loc]->deg++;
				quitFlag1 = TRUE;
			}	
		}
		/*Prints if issue in logic 
		else{
			printf("Problem in code");
		}*/
	}
	
	/*Start looking at the first adjacent vertex to Edge.v2*/
	
	curVer = adjList[v2Loc];
	//Adds Edge.v1 to adjacency list for Edge.v2
	while(quitFlag2 == FALSE){
		//initial vertex setting of each value equal to -99, so if still blank, fills with new vertex
		if(!curVer){ 
				adjList[v2Loc] = newVer1;
				adjList[v2Loc]->deg++;
				quitFlag2 = TRUE;
		}
		//there is at least one vertex already in the current element in the adjacency list
		else{
			//if there is another vertex in the list, move on to next vertex in list
			if(curVer->next){
				prevVer = curVer;
				curVer = curVer->next;
			}
			//if this is the last vertex in the list, add new vertex to adjacency list
			else{
				curVer->next = newVer1;
				adjList[v2Loc]->deg++;
				quitFlag2 = TRUE;
			}
		}
		/*Prints if issue is in logic
		else{
			printf("Problem in code: spot in adjacency list still null, even though attempted to fill.");
		}*/
	}
}

int walkBFS(Vertex* adjList[], Vertex* listForWalk[]){
	int goOn = TRUE;
	int vertCount = 1;
	int u = 0;
	//Sets initial vertex color to black (visited)
	listForWalk[u]->color = BLACK;
	Vertex *curr;
	while(goOn == TRUE){
		//Sets current vertex to check
		curr = adjList[u];
		//While current vertex in adjacency list has not been visited
		while(curr && listForWalk[(curr->ver)-1]->color == BLACK){
			curr = curr->next;
		}
		//If end of current vertex's adjacency list has been reached, stop
		if(!curr){
			goOn = FALSE;
		}
		else{
			//Set new vertex to the currently observed vertex (-1 to use in array)
			u = (curr->ver) - 1;
			//Set the new vertex color to black (visited)
			listForWalk[u]->color = BLACK;
			//Add to vertCount to keep track of total vertices visited
			vertCount++;
		}
	}
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
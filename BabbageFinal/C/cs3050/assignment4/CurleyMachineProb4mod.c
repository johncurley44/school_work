/*
* Name: John Curley	 - jmcgdd
* CS3050  
* Machine Problem 4 - 11/12/2013
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100000
#define MAX_NUM_STRING 10
#define FALSE 0
#define TRUE 1

//Edge struct, contains 2 vertices as ints
typedef struct edge {
	int v1;
	int v2;
	int weight;
} Edge;
//Vertex struct with vertex value, color, deg, and locate as integers and a pointer to next vertex for lists
typedef struct vertex{
	int ver;
	int color;
	int deg;
	int dist;
	struct vertex* next;
}Vertex;
//Function prototypes
void printEdgeList(Edge edgeList[], int edgeSize);
void addVertexToAdjList(Vertex* adjList[], Edge inEdge);
Vertex* createVertex(int verVal);
void enqueue(Vertex* queueHead, Vertex* queueTail, Vertex ver);
Vertex* dequeue(Vertex* queueHead, Vertex* queueTail);
void freeVerArray(Vertex* head);

int main(int argc, char **argv)
{ 	
	FILE *input = NULL;
	int array_size = 0, numVer = 0, i, j;
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
	//Variable declarations
	int uVer = 0, vVer = 0, weight = 0;
	int currPos = 0;
	Edge edgeArray[MAX_SIZE];
	Edge tempEdge;
	Vertex vertexArray[MAX_SIZE];
	Vertex changedVers[MAX_SIZE];
	Vertex predVer[MAX_SIZE];
	Vertex *adjList[numVer]; 
	Vertex *queueHead = NULL;
	Vertex *queueTail = NULL;
	Vertex *tempVer;
	int edgeSize = 0;
	int nwcFlag = FALSE;
	//Reads each line of file, stores the numbers in an array of edges, keeps track of total number of vertices
	while(!feof(input)){
		fscanf(input, "%d", &tempEdge.v1);
		fscanf(input, "%d", &tempEdge.v2);
		fscanf(input, "%d", &tempEdge.weight);
		if(tempEdge.v1 > numVer){
			numVer = tempEdge.v1;
		} 
		if(tempEdge.v2 > numVer){
			numVer = tempEdge.v2;
		}
		edgeArray[currPos] = tempEdge;
		currPos++;
	}
	//number of edges
	edgeSize = currPos;
	fclose(input);
	//Creates/initializes adjlist pointer array
	for(i=0;i<numVer;i++){
		adjList[i] = malloc(sizeof(Vertex));
		adjList[i]->ver = 0;
	}
	//Initialize vertex array using values stored in edges
	//	All distances are set to 0 when no single source is given.
	for(i=0; i<edgeSize; i++){
		vertexArray[edgeArray[i].v1-1].ver = edgeArray[i].v1;
		vertexArray[edgeArray[i].v1-1].dist = 0;
		vertexArray[edgeArray[i].v2-1].ver = edgeArray[i].v2;
		vertexArray[edgeArray[i].v2-1].dist = 0;
		addVertexToAdjList(adjList, edgeArray[i]);
	}
	
	//Enqueue the first vertex (arbitrary when not a single source)
	enqueue(queueHead, queueTail, vertexArray[0]);
	//Until the queue of vertices that were changed last iteration is empty
	while(queueHead != NULL){
		tempVer = dequeue(queueHead, queueTail);
		//Check every edge outgoing from the recently changed vertex instead of every vertex
		while(adjList[tempVer->ver-1]){
			//RELAX function, when the next vertex distance is greater than the current vertex distance and the weight of the traveled edge, change the distance of the next vertex
			if(vertexArray[edgeArray[j].v2-1].dist > (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight)){
				vertexArray[edgeArray[j].v2-1].dist = (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight);
				predVer[edgeArray[j].v2-1] = vertexArray[edgeArray[j].v1-1];
				//enqueue the vertex that had it's distance changed
				enqueue(queueHead, queueTail, *adjList[tempVer->ver-1]);
			}
		}
	}
	//One last check. If RELAX passes again, it means that there must be a NWC, so print and quit.
	for(j=0; j<edgeSize; j++){
		if(vertexArray[edgeArray[j].v2-1].dist > (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight)){
			printf("NWC exists - YES\n\n");
			nwcFlag = TRUE;
		}
	}
	//If a NWC was not found, print and quit.
	if(nwcFlag == FALSE){
		printf("NWC does not exist - NO\n\n");
	}
	
	//Frees the allocated memory
	freeVerArray(adjList[0]);
}

/* Function Purpose: Prints the edge list for testing purposes.
 * Input params: list of edges and size of that list
 * Return param: void
 **/
void printEdgeList(Edge edgeList[], int edgeSize){
	//Copies head into p to traverse
	int i;
	printf("u    v    weight\n");
	//Traverse each address in adj list and print
	for(i=0;i<edgeSize;i++){
		printf("\n%d   %d    %d", edgeList[i].v1, edgeList[i].v2, edgeList[i].weight);
	}
	printf("\n\n");
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
/* Function Purpose: Adds a vertex to the queue
 * Input params: Vertex* queueHead - head of the queue, Vertex* queueTail - tail of the queue, Vertex ver - vertex to add to queue
 * Return param: void
 **/
void enqueue(Vertex* queueHead, Vertex* queueTail, Vertex ver){
	if(queueTail == NULL){
		queueHead = &ver;
		queueTail = &ver;
	}
	else{
		queueTail->next = &ver;
	}
}
/* Function Purpose: Removes a vertex from the queue
 * Input params: Vertex* queueHead - head of the queue, Vertex* queueTail - tail of the queue
 * Return param: new head of queue
 **/
Vertex* dequeue(Vertex* queueHead, Vertex* queueTail){
	if(queueHead == NULL){
		printf("Problem");
	}
	queueHead = queueHead->next;
	if(queueHead==NULL){
		queueTail = NULL;
	}
	return queueHead;
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
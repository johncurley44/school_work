/*
* Name: John Curley	 - jmcgdd
* CS3050
* Machine Problem 1 - 9/3/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50
#define FALSE 0
#define TRUE 1

typedef struct edge {
	int v1;
	int v2;
} Edge;

typedef struct vertex{
	int ver;
	struct vertex* next;
}Vertex;

//Function Prototypes

Vertex* createVertex(int verVal);
Vertex* addVertexToAdjList(Vertex* adjList[], Edge inEdge);

int main(int argc, char **argv)
{
	
	FILE *in = NULL;
	int array_size = 0, numVer = 0, i;
	Edge tempEdge;
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
		printf("%d and %d added to array\n", tempEdge.v1, tempEdge.v2);		
	}
	fclose(in);
	
	Vertex *adjList[numVer];
	Vertex *headVertex = malloc(sizeof(Vertex));
	for(i=0;i<numVer;i++){
		addVertexToAdjList();
		
		
		
		
		
	//FREE EVERTHING
	
	
	
		
		
}

Vertex* createVertex(int verVal){
	Vertex* newVer = malloc(sizeof(Vertex));
	newVer->ver = verVal;
	newVer->next = NULL;
	return newVer;
}

Vertex* addVertexToAdjList(Vertex* adjList[], Edge inEdge){
	Vertex* curVer;
	curVer = adjList[0];
	Vertex* nextVer;
	Vertex* prevVer = NULL;
	int quitFlag1 = FALSE, quitFlag2 = FALSE;
	
	Vertex* newVer1 = createVertex(inEdge.e1);
	Vertex* newVer2 = createVertex(inEdge.e2);
	
	//Adds Edge.e2 to adjacency list for Edge.e1	
	while(quitFlag1 == FALSE){
		//Fills the spot in the adjacency list array with vertex if empty
		if(adjList[inEdge.e1]==NULL){
			adjList[inEdge.e1] = newVer1;
		}
		
		//Error check to make sure vertex was properly placed in adj. list array if originally empty
		if(adjList[inEdge.e1] != NULL){
			//Start looking at the first adjacent vertex to Edge.e1
			curVer = adjList[inEdge.e1]->next;
			//If current adjacent vertex does not equal second vertex in edge and there is another adjacent vertex to first vertex in edge
			if(curVer->ver != inEdge.e2 && curVer->next != NULL){
				//Move on to next adjacent vertex
				prevVer = curVer;
				curVer = curVer->next;
			}
			//If current adjacent vertex does not equal second vertex in edge and there are no more listed adjacent vertices
			else if(curVer->ver != inEdge.e2 && curVer->next == NULL){
				//Add the second vertex in the edge to the adjacency list of first vertex in edge, quit
				curVer->next = newVer2;
				quitFlag1 = TRUE;
			}
			//second number in edge already in adj. list, quit
			else{
				quitFlag1 = TRUE;
			}
		}
		//Error printed if adjList location still empty
		else{
			printf("Problem in code: spot in adjacency list still null, even though attempted to fill.");
		}
	}
	//Adds Edge.e1 to adjacency list for Edge.e2
	while(quitFlag2 == FALSE){
	
	}
	
	
	
	
}
			
		/*if((curVer->ver) != verVal){
			//if there is another vertex to examine
			if(curVer->next){
				prevVer = curVer;
				curVer = curVer->next;
			}
			else{
				//Sets the next vertex to new vertex in adj list
				curVer->next = newVer;
				quitFlag = TRUE;
			}
		}
		//If current adj list vertex does equal to the vertex trying to add, do not add it, exit
		else{
			quitFlag = TRUE;
		}
	}
	return head;*/
	
	
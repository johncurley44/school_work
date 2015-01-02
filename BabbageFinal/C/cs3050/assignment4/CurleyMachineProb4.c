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

void printEdgeList(Edge edgeList[], int edgeSize);


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
	
	int uVer = 0, vVer = 0, weight = 0;
	int currPos = 0;
	Edge edgeArray[MAX_SIZE];
	Edge tempEdge;
	Vertex vertexArray[MAX_SIZE];
	Vertex predVer[MAX_SIZE];
	int edgeSize = 0;
	int nwcFlag = FALSE;
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
	edgeSize = currPos;
	fclose(input);
	//printEdgeList(edgeArray, edgeSize);
	
	for(i=0; i<edgeSize; i++){
		vertexArray[edgeArray[i].v1-1].ver = edgeArray[i].v1;
		vertexArray[edgeArray[i].v1-1].dist = 0;
		vertexArray[edgeArray[i].v2-1].ver = edgeArray[i].v2;
		vertexArray[edgeArray[i].v2-1].dist = 0;
		//predVer[edgeArray[i].v1-1] = NULL;
		//predVer[edgeArray[i].v2-1] = NULL;
	}
	
	for(i=0; i<numVer; i++){
		for(j=0; j<edgeSize; j++){
			if(vertexArray[edgeArray[j].v2-1].dist > (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight)){
				vertexArray[edgeArray[j].v2-1].dist = (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight);
				predVer[edgeArray[j].v2-1] = vertexArray[edgeArray[j].v1-1];
			}
		}
	}
	for(j=0; j<edgeSize; j++){
		if(vertexArray[edgeArray[j].v2-1].dist > (vertexArray[edgeArray[j].v1-1].dist)+(edgeArray[j].weight)){
			printf("NWC exists - YES\n\n");
			nwcFlag = TRUE;
		}
	}
	if(nwcFlag == FALSE){
		printf("NWC does not exist - NO\n\n");
	}
}

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
		
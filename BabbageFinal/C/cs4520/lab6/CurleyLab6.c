/********************************************************************************
 * Name:           John Curley
 * Userid:         jmcgdd 16013276
 * Course:         CS 4520
 * Assignment#:    Lab 6
 *
 * File name:      CurleyLab6.c
 *
 * Question no:	   9.39      
 *
 * Assumptions:    1) Use this string : 1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6
 *		&		   2)  
 * Precautions		  
 *********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

//structure to store important information
typedef struct
{
    int occupied;//is the frame occupied ?
    int turnOfEntry;//when did the page occupy the frame?
    int frameNo;//frame number
    int lastUsed;//when was it last used
}frame;

//use above struct to create array of structure depending on number of frames like frame1, frame2 etc..
frame frame1[1];
frame frame2[2];
frame frame3[3];
frame frame4[4];
frame frame5[5];
frame frame6[6];
frame frame7[7];

int randomPageRef[20] = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};

//Set frame values to 0
void rezeroFrames(frame frames[], int numFrames){
	int i;
	for(i=0;i<numFrames;i++){
		frames[i].occupied = 0;
		frames[i].turnOfEntry = 0;
		frames[i].frameNo = 0;
		frames[i].lastUsed = 0;
	}
}
//have individual methods for each algorithm

//FIFO algorithm
int fifo_paging(int numFrames, frame frameArray[]) {

	int i, j;
	int flag, fullCount;
	int pageFaults = 0;
	int firstInLoc = -1;
	int firstInTime = 9999;
	
	fullCount = 0;
	for(i=0;i<20;i++){
		//Reset Variables
		flag = FALSE;
		j=0;
		//Check for the page already in a frame in memory
		while(flag == FALSE && j<numFrames){
			if(frameArray[j].frameNo == randomPageRef[i]){
				flag = TRUE;
			}
			j++;
		}
		//Reset Variables
		j=0;
		//If page not yet in memory, check for any empty spots, page fault if one found
		while(fullCount<numFrames && flag == FALSE && j<numFrames){
			if(frameArray[j].occupied == FALSE){
				frameArray[j].frameNo = randomPageRef[i];
				frameArray[j].turnOfEntry = i;
				frameArray[j].occupied = TRUE;
				fullCount++;
				pageFaults++;
				flag = TRUE;
			}
			j++;
		}
		//Reset Variables
		j=0;
		firstInTime = 9999;
		//If page is not yet in memory and no empty spots in memory, then find the first frame in
		while(flag == FALSE && j<numFrames){
			if(frameArray[j].turnOfEntry < firstInTime){
				firstInTime = frameArray[j].turnOfEntry;
				firstInLoc = j;
			}
			j++;
		}
		//If the page is not in memory and there are no open spots, swap it with the first frame in
		if(flag == FALSE){
			frameArray[firstInLoc].frameNo = randomPageRef[i];
			frameArray[firstInLoc].turnOfEntry = i;
			frameArray[firstInLoc].occupied = TRUE;
			flag = TRUE;
			pageFaults++;
		}
	}
	
	return pageFaults;
	
}	

//LRU algorithm
int lru_paging(int numFrames, frame frameArray[]){

	int i, j;
	int flag, fullCount;
	int pageFaults = 0;
	int leastRecentLoc = -1;
	int lastTimeUsed = 9999;
	
	fullCount = 0;
	for(i=0;i<20;i++){
		//Reset variables
		flag = FALSE;
		j=0;
		//Check for the page already in a frame in memory
		while(flag == FALSE && j<numFrames){
			if(frameArray[j].frameNo == randomPageRef[i]){
				frameArray[j].lastUsed = i;
				flag = TRUE;
			}
			j++;
		}
		//Reset Variables
		j=0;
		//If page not yet in memory, check for any empty spots, page fault if one found
		while(fullCount<numFrames && flag == FALSE && j<numFrames){
			if(frameArray[j].occupied == FALSE){
				frameArray[j].frameNo = randomPageRef[i];
				frameArray[j].lastUsed = i;
				frameArray[j].occupied = TRUE;
				fullCount++;
				pageFaults++;
				flag = TRUE;
			}
			j++;
		}
		//Reset Variables
		j=0;
		lastTimeUsed = 9999;
		//If page is not yet in memory and no empty spots in memory, then find the least recently used frame
		while(flag == FALSE && j<numFrames){
			if(frameArray[j].lastUsed < lastTimeUsed){
				lastTimeUsed = frameArray[j].lastUsed;
				leastRecentLoc = j;
			}
			j++;
		}
		//If the page is not in memory and there are no open spots, swap it with the least recently used frame
		if(flag == FALSE){
			frameArray[leastRecentLoc].frameNo = randomPageRef[i];
			frameArray[leastRecentLoc].lastUsed = i;
			frameArray[leastRecentLoc].occupied = TRUE;
			flag = TRUE;
			pageFaults++;
		}
	}
	
	return pageFaults;
}

//Optimal algorithm
int opt_paging(int numFrames, frame frameArray[]){
	int i, j, k, l;
	int flag, fullCount;
	int pageFaults = 0;
	int firstInTime = 9999;
	int nextUsed = 0;
	int frameLocToReplace = 0;
	int usedFlagTrueCounter = 0;
	int usedFlag[numFrames];
	fullCount = 0;
	for(i=0;i<20;i++){
		//Reset variables
		flag = FALSE;
		j=0;
		//Check for the page already in a frame in memory
		while(flag == FALSE && j<numFrames){
			if(frameArray[j].frameNo == randomPageRef[i]){
				flag = TRUE;
			}
			j++;
		}
		//Reset variables
		j=0;
		//If page not yet in memory, check for any empty spots, page fault if one found
		while(fullCount<numFrames && flag == FALSE && j<numFrames){
			if(frameArray[j].occupied == FALSE){
				frameArray[j].frameNo = randomPageRef[i];
				frameArray[j].turnOfEntry = i;
				frameArray[j].occupied = TRUE;
				fullCount++;
				pageFaults++;
				flag = TRUE;
			}
			j++;
		}
		//Reset variables
		j=0;
		nextUsed = 0;
		frameLocToReplace = -1;
		for(l=0;l<numFrames;l++){
			usedFlag[l] = FALSE;
		}
		usedFlagTrueCounter = 0;
		//If page is not yet in memory and no empty spots in memory, then find the frame that will be used again last of the frames in memory
		while(flag == FALSE && j<numFrames){
			//Search remaining pages in array to find which of the frames will be used last
			for(k=i;k<20;k++){
				//Find the location of the last used page, keep track if pages are found in array again or not
				if(frameArray[j].frameNo == randomPageRef[k]){
					if(nextUsed < k){
						frameLocToReplace = j;
					}
					usedFlag[j] = TRUE;
					usedFlagTrueCounter++;
					//Breaks the loop here to keep the location of the first appearance of a page in the array
					break;
				}
			}	
			j++;
		}
		//Find first in as tie breaker (if there is a number that was not used again in the random array)
		if(usedFlagTrueCounter < numFrames){
			j=0;
			firstInTime = 9999;
			//Run FIFO to find the first used
			while(flag == FALSE && j<numFrames){
				//Only examines the frames that were not found again in the random array
				if(usedFlag[j] == FALSE && frameArray[j].turnOfEntry < firstInTime){
					firstInTime = frameArray[j].turnOfEntry;
					frameLocToReplace = j;
				}
				j++;
			}
		}
		//Swap the determined frame with the current page if there wasn't a blank spot and it wasn't already in memory. 
		//	The swapped frame will be either a frame that was not found again in the array (based on FIFO if more than one) or
		//	whichever page is found last
		if(flag == FALSE){
			frameArray[frameLocToReplace].frameNo = randomPageRef[i];
			frameArray[frameLocToReplace].turnOfEntry = i;
			frameArray[frameLocToReplace].occupied = TRUE;
			flag = TRUE;
			pageFaults++;
		}
	}
		return pageFaults;
}

//main
int main(void){
	int faults[7];
	int i;
	
	//Set all frame values to 0
	rezeroFrames(frame1, 1);
	rezeroFrames(frame2, 2);
	rezeroFrames(frame3, 3);
	rezeroFrames(frame4, 4);
	rezeroFrames(frame5, 5);
	rezeroFrames(frame6, 6);
	rezeroFrames(frame7, 7);
	
	//Calls for FIFO
	faults[0] = fifo_paging(1, frame1);
	faults[1] = fifo_paging(2, frame2);
	faults[2] = fifo_paging(3, frame3);
	faults[3] = fifo_paging(4, frame4);
	faults[4] = fifo_paging(5, frame5);
	faults[5] = fifo_paging(6, frame6);
	faults[6] = fifo_paging(7, frame7);
	for(i=0;i<7;i++){
		printf("Page faults for FIFO for %d no of frames is: %d\n", i+1, faults[i]);
	}
	
	//Reset all frame values to zero
	rezeroFrames(frame1, 1);
	rezeroFrames(frame2, 2);
	rezeroFrames(frame3, 3);
	rezeroFrames(frame4, 4);
	rezeroFrames(frame5, 5);
	rezeroFrames(frame6, 6);
	rezeroFrames(frame7, 7);
	
	//Calls for LRU
	faults[0] = lru_paging(1, frame1);
	faults[1] = lru_paging(2, frame2);
	faults[2] = lru_paging(3, frame3);
	faults[3] = lru_paging(4, frame4);
	faults[4] = lru_paging(5, frame5);
	faults[5] = lru_paging(6, frame6);
	faults[6] = lru_paging(7, frame7);
	for(i=0;i<7;i++){
		printf("Page faults for LRU for %d no of frames is: %d\n", i+1, faults[i]);
	}
	
	//Reset all frame values to zero
	rezeroFrames(frame1, 1);
	rezeroFrames(frame2, 2);
	rezeroFrames(frame3, 3);
	rezeroFrames(frame4, 4);
	rezeroFrames(frame5, 5);
	rezeroFrames(frame6, 6);
	rezeroFrames(frame7, 7);
	
	//Calls for Optimal
	faults[0] = opt_paging(1, frame1);
	faults[1] = opt_paging(2, frame2);
	faults[2] = opt_paging(3, frame3);
	faults[3] = opt_paging(4, frame4);
	faults[4] = opt_paging(5, frame5);
	faults[5] = opt_paging(6, frame6);
	faults[6] = opt_paging(7, frame7);
	for(i=0;i<7;i++){
		printf("Page faults for OPT for %d no of frames is: %d\n", i+1, faults[i]);
	}
	
}
/*
* Name: John Curley
* Lab section: B
* TA: Zhi Zhou - Seth Weisman
*
* Bonus Completed
*/
//Preprocess Commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_NAME 30
#define TRUE 1
#define FALSE 0
//Function Prototypes
int countLinesInFile(FILE* fPtr);
int findPlayerByName(char** names, char* target, int size);
int findMVP(int* goals, int* assists, int size);
void printPlayers(int* goals, int* assists, char** names, int size);
void allocateMemory(int** goals, int** assists, char*** names, int size);
void sortPlayersByGoals(int* goals, int* assists, char** names, int size);
void writeToFile(FILE* fPtr, int* goals, int* assists, char** names, int size);
void readLinesFromFile(FILE* fPtr, int* goals, int* assists, char** names, int numLines);

// Bonus function
void bonusSortPlayersByBoth(int* goals, int* assists, char** names, int size);

// Main function receives two command line arguments. The first is the name
// of the input file; the second is the name of the output file. If either one
// is missing, or the input file cannot be opened, the program should print an
// error message and end.
//
// You are responsible for making the output of your program match the sample
// output. That means you must determine the appropriate algorithm on your own;
// TAs will not provide a step-by-step list of functions to call, or how to
// achieve the proper output. It is recommended that you implement main after
// implementing some of the other functions; this may help you to see the purpose
// of main more clearly.
int main(int argc, char** argv)
{
	FILE* fPtrIn;
	FILE* fPtrOut;
	//Checks to make sure command line contains only two other arguments
	if(argc != 3){
		printf("Two and only two command line arguments are allowed, terminating. \n\n");
		return 1;
	}
	
	//Opens files
	fPtrIn = fopen(argv[1], "r");
	fPtrOut = fopen(argv[2], "w");
	//Checks to make sure files were found
	if(fPtrIn == NULL || fPtrOut == NULL){
		printf("Could not find both files, terminating.\n\n");
		return 1;
	}
	
	//Declare pointers for goals, assists, and names
	char** names;
	int* goals;
	int* assists;
	int mvpIndex, targetIndex;
	//Uses countLinesInFile() to assign the numeber of lines to int size
	int size = countLinesInFile(fPtrIn);
	//Allocates memory to store player information
	allocateMemory(&goals, &assists, &names, size);
	//Reads from input file and assigns them to player information pointers
	readLinesFromFile(fPtrIn, goals, assists, names, size);
	//Prints initial list as read from input file
	printf("\nRead the following %d players from the file..\n\n", size);
	printPlayers(goals, assists, names, size);
	//Sorts player information by goals scored and assists, re-stores in goals, assists, and names
	bonusSortPlayersByBoth(goals, assists, names, size);
	//Prints new, sorted player list
	printf("\n------ Bonus ------\n\n");
	printPlayers(goals, assists, names, size);
	//Finds and prints MVP
	mvpIndex = findMVP(goals, assists, size);
	printf("\nMVP was %s with %d points\n\n", *(names+mvpIndex), (*(goals+mvpIndex)+*(assists+mvpIndex)));
	//Asks for user input on player to find, case sensitive
	char* targetPlayer = malloc(MAX_NAME*sizeof(char));
	printf("Enter a player to find: ");
	scanf("%s", targetPlayer);
	targetIndex = findPlayerByName(names, targetPlayer, size);		
	//Only attempts to print player info if searched player found
	if(targetIndex != -1){
		printf("%s has %d goals and %d assists\n\n", *(names+targetIndex), *(goals+targetIndex), *(assists+targetIndex));
	}
	else{
		printf("Error, player not found\n\n");
	}
	//Writes sorted information to file
	writeToFile(fPtrOut, goals, assists, names, size);
	//Frees malloced memory
	free(targetPlayer);
	free(goals);
	free(assists);
	fclose(fPtrIn);
	fclose(fPtrOut);
	return 0;
}

// Counts how many lines are in the file provided. After counting,
// this function should rewind the file for future use.
//
// INPUT: fPtr - A pointer to a file opened in read mode.
// RETURNS: The number of lines in the file.
int countLinesInFile(FILE* fPtr)
{
	int contLoop = TRUE, lineTotal = 0;
	char* lineCountStr = malloc(MAX_LINE*sizeof(char));
	//Counts the lines in the file using fgets and NULL
	while(contLoop == TRUE){
		if(fgets(lineCountStr, MAX_LINE, fPtr) != NULL){
			lineTotal++;
		}
		else{
			contLoop = FALSE;
		}
	}
	//Rewinds file to original position
	rewind(fPtr);
	free(lineCountStr);
	return lineTotal;
}

// Finds a player by their name.
//
// INPUT: names  - A pointer to the strings containing the player names.
//        target - The name of the player to find.
//        size   - The number of players to search through.
// RETURNS: The index of the player if found; -1 otherwise.
int findPlayerByName(char** names, char* target, int size)
{
	int i;
	//Searches name array, uses strcmp to see if name matches
	for(i=0; i<size; i++){
		if(strcmp(target, *(names+i))==0){
			return i;
		}
	}
	return -1;
}

// Finds the most valuable player (MVP) of the players. (The MVP has the greatest goals + assists total.)
//
// INPUT: goals   - An array containing the number of goals scored per player.
//        assists - An array containing the number of assists per player.
//        size    - The number of players in each array.
// RETURNS: The index of the MVP. You may assume that size > 0 and therefore, there will always be
//          an MVP. In the event of a tie, you may return any of the players in the tie.
int findMVP(int* goals, int* assists, int size)
{
	int* totalPts = malloc(size*sizeof(int));
	int i, currMVP;
	int currMax = 0;
	//Checks each player, adds goals and assists, saves player as mvp is he has highest total points
	for(i=0; i<size; i++){
		*(totalPts+i) = *(goals+i) + *(assists+i);
		if(*(totalPts+i) > currMax){
			currMax = *(totalPts+i);
			currMVP = i;
		}
	}
	return currMVP;
	free(totalPts);
}

// Prints the players names along with their goals and assists.
// YOU MUST USE FORMATTED OUTPUT IN THIS FUNCTION. Failing to do so
// will result in a loss of half of the points for this function.
// Players should be printed out as follows:
//
// Name          Goals   Assists
// Backes        4       2
// Pietrangelo   3       1
//
// You must include the column headers in your output. THIS FUNCTION,
// AND MAIN, SHOULD BE THE ONLY OUTPUT-PRODUCING FUNCTIONS IN YOUR PROGRAM.
// If other functions produce output, you will lose half of the points for
// those functions. It is very important not to produce errant output!
//
// INPUT: goals   - An array containing the number of goals per player.
//        assists - An array containing the number of assists per player.
//        names   - An array containing the names of each player.
//        size    - The number of players in each array.
void printPlayers(int* goals, int* assists, char** names, int size)
{
	printf("Name          Goals   Assists\n");
	int i;
	//Prints each player's info
	for(i=0; i<size; i++){
		printf("%-14s%-8d%d\n", *(names+i), *(goals+i), *(assists+i));
	}
}

// Allocates memory for the player names, their goals, and their assists.
// HINT: Allocating the memory for the goals and assists is straightforward;
// allocating memory for the names is going to be very similar to lab 2, with
// an extra dereference to account for the fact that we are using a char***.
//
// INPUT: goals   - A pointer to a variable which should contain the malloced memory for goals.
//        assists - A pointer to a variable which should contain the malloced memory for assists.
//        names   - A pointer to a variable which should contain the malloced memory for names.
//        size    - The number of players to malloc memory for.
void allocateMemory(int** goals, int** assists, char*** names, int size)
{
	int i;
	//malloc memory for goal and assist int arrays
	*goals = malloc(size*sizeof(int));
	*assists = malloc(size*sizeof(int));
	//mallocs memory for array of strings
	*names = malloc(size*sizeof(char*));
	//mallocs memory for characters in each string
	for(i=0; i<size; i++){
		*(*names+i) = malloc(MAX_NAME*sizeof(char));
	}
}

// Sorts the players according to the number of goals they've scored, in descending order.
// You must use insertion sort or selection sort for this function.
// USE OF ANY OTHER SORTING FUNCTION WILL RESULT IN NO POINTS FOR THIS FUNCTION.
// Keep in mind that moving an entry in one array will require you to
// move entries in the other two arrays, to keep player information synchronized.
// (There are a few ways to accomplish this with names, some easier than others.)
//
// INPUT: goals   - An array containing the number of goals per player.
//        assists - An array containing the number of assists per player.
//        names   - An array containing the names of each player.
//        size    - The number of players in each array.
void sortPlayersByGoals(int* goals, int* assists, char** names, int size)
{
	int i, j, currMin, tempGoals, tempAssists;
	char* tempName = malloc(MAX_NAME*sizeof(char));
	//Insertion sort basic algorithm
	for(i=0; i<size-1; i++){
		currMin = i;
		for(j=i+1; j<size; j++){
			if(*(goals+j)>*(goals+currMin)){
				currMin = j;
			}
		}
		//If new high scorer found, swaps name of the player along with goals and assists
		if(currMin != i){
			tempGoals = *(goals+i);
			tempAssists = *(assists+i);
			strcpy(tempName, *(names+i));
			*(goals+i) = *(goals+currMin);
			*(assists+i) = *(assists+currMin);
			strcpy(*(names+i), *(names+currMin));
			*(goals+currMin) = tempGoals;
			*(assists+currMin) = tempAssists;
			strcpy(*(names+currMin), tempName);
			
		}
	}
	free(tempName);
				
}

// Writes the player information to the given file, in the same order as the input file.
// You should not call this function until after you have sorted the player information,
// so that the information appears in sorted order in the output file.
//
// INPUT: fPtr    - A pointer to a file to write to.
//        goals   - An array containing the number of goals per player.
//        assists - An array containing the number of assists per player.
//        names   - An array containing the names of each player.
//        size    - The number of players in each array.
void writeToFile(FILE* fPtr, int* goals, int* assists, char** names, int size)
{
	int i;
	//Writes each bit of information from each player to file
	for(i=0; i<size; i++){
		fprintf(fPtr, "%s %d %d\n", *(names+i), *(goals+i), *(assists+i));
	}
	rewind(fPtr);
}

// Reads the player information from the given file. Information is in the following format:
// 
// [name] [goals] [assists]
// Backes 1 5
// Pietrangelo 2 7
//
// YOU MAY NOT USE FSCANF IN THIS FUNCTION! Doing so will result in no points. Instead you
// must use fgets in combination with the strtok function in order to break the line into
// pieces. You can read about strtok online or in your textbook; email your TA with any
// questions.
//
// INPUT: fPtr    - A pointer to a file to read from.
//        goals   - An array to be filled with the number of goals per player.
//        assists - An array to be filled with the number of assists per player.
//        names   - An array to be filled with the names of each player.
//        size    - The number of players in each array.
void readLinesFromFile(FILE* fPtr, int* goals, int* assists, char** names, int numLines)
{
	char* line = malloc(MAX_LINE*sizeof(char));
	int i;
	char* goalStr = malloc(MAX_NAME*sizeof(char));
	char* assistStr = malloc(MAX_NAME*sizeof(char));
	//Reads and saves each line from input file to arrays
	for(i=0; i<numLines; i++){
		fgets(line, MAX_LINE, fPtr);
		strtok(line, " ");
		strcpy(*(names+i), line);
		goalStr = strtok(NULL, " ");
		assistStr = strtok(NULL, " \n");
		*(goals+i) = atoi(goalStr);
		*(assists+i) = atoi(assistStr);
	} 
	free(line);
	rewind(fPtr);
}

// BONUS FUNCTION - worth 5 extra points. You may only receive points for the bonus
// if you have implemented all other functions with no major flaws. This is up to the
// discretion of your TA.
//
// This function sorts the players according to two fields - goals and assists.
// Players should be sorted according to their goals scored first, then they will
// be sorted by the number of assists they have scored as a second criteria. Example:
//
// Tarasenko 5 5
// Berglund 5 2
// Pietrangelo 2 7
// Perron 2 6
// McDonald 2 4
// Redden 2 0
// Backes 1 5
// 
// Note that within each grouping of players with the same number of goals,
// they are subsequently sorted by the number of assists. If two players have
// the same number in each category, you may place them in any order.
//
// Unlike the other sort function, you may use any type of sort algorithm to
// implement this function. Note that this does not excuse you from implementing
// the other sort function with the proper algorithm. It will probably be easiest
// to simply call the other sort function from within this one, and then perform
// the sub-sort afterwards.
void bonusSortPlayersByBoth(int* goals, int* assists, char** names, int size)
{
	//Sorts players using original insertion sort function
	sortPlayersByGoals(goals, assists, names, size);
	//Prints players using original sort
	printf("\nSorted player list..\n\n");
	printPlayers(goals, assists, names, size);
	int i, j, currMin, tempGoals, tempAssists;
	char* tempName = malloc(MAX_NAME*sizeof(char));
	//Second insertion sort to sort by assists as well
	for(i=0; i<size; i++){
		currMin = i;
		for(j=i+1; j<size; j++){
			//First checks to see if goals are at least the same or higher
			if(*(goals+j)>=*(goals+currMin)){
				//Then, if assists higher, sorts accordingly
				if(*(assists+j)>*(assists+currMin)){
					currMin = j;
				}
			}
		}
		//If a change is found, rearranges all stats for players involved
		if(currMin != i){
			tempGoals = *(goals+i);
			tempAssists = *(assists+i);
			strcpy(tempName, *(names+i));
			*(goals+i) = *(goals+currMin);
			*(assists+i) = *(assists+currMin);
			strcpy(*(names+i), *(names+currMin));
			*(goals+currMin) = tempGoals;
			*(assists+currMin) = tempAssists;
			strcpy(*(names+currMin), tempName);
		}
	}
	free(tempName);
}
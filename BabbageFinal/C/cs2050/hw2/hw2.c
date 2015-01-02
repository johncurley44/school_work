/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
*/
//preprocess statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_NAME 30
#define TRUE 1
#define FALSE 0

typedef struct player {
	char name[MAX_NAME]; // The name of the player.
	int goals;           // The number of goals the player has scored.
	int assists;         // The number of assists the player has.
	struct player* next; // A pointer to the next player in the linked list, or NULL if no player follows this one.
} Player;

//Function prototypes
Player* createPlayer(char* name, int goals, int assists);
Player* insertPlayerInSortedOrderByName(Player* head, char* name, int goals, int assists);
void printPlayers(Player* head);
int getLengthOfList(Player* head);
Player* mergeSortByGoals(Player* head);
Player* merge(Player* left, Player* right);
Player* findPlayerByName(Player* head, char* name);
Player* removePlayer(Player* head, char* name);
void freeList(Player* head);

int main(int argc, char** argv)
{
	char tempName[MAX_NAME], tempStr[MAX_LINE], remPlayer[MAX_NAME];
	int tempAssists, tempGoals;
	Player* head = NULL;
	FILE* fptr;
	//Check input arguments
	if(argc != 2){
		printf("Only one command line argument allowed, terminating. \n\n");
		return 1;
	}

	// Open input file
		fptr = fopen(argv[1], "r");
	//Checks to make sure file was found
		if(fptr == NULL){
			printf("Could not find file, terminating.\n\n");
			return 1;
		}
	// Read and parse lines from file; add players to linked list as they are read in
		while(fgets(tempStr, MAX_LINE, fptr)){
			strcpy(tempName, strtok(tempStr, " "));
			tempGoals = atoi(strtok(NULL, " "));
			tempAssists = atoi(strtok(NULL, " "));
			head = insertPlayerInSortedOrderByName(head, tempName, tempGoals, tempAssists); 
		}
			
	// Close input file
		fclose(fptr);
	// Print how many players are in file - use getLengthOfList, do NOT count while reading
		printf("\nThere are %d players in the file\n\n", getLengthOfList(head));
	// Print list
		printPlayers(head);
	// Re-sort list by goals
		head = mergeSortByGoals(head);
	// Print list again after sorting
		printf("\nSorted list: \n\n");
		printPlayers(head);
	// Ask user to search and display result
		printf("\nEnter a name to search for and remove: ");
		scanf("%s", remPlayer);
		head = findPlayerByName(head, remPlayer);
	// Remove player that was searched for
		head = removePlayer(head, remPlayer);
	// Print list again after removing player
		printf("\nList after removing %s:\n\n", remPlayer);
		printPlayers(head);
		
		freeList(head);
}

// Creates a Player with the given name, number of goals,
// and number of assists. The Player should be dynamically
// allocated (use malloc!).
//
// INPUT:  name    - A string to use as the player's name.
//         goals   - The number of goals the player has scored.
//         assists - The number of assists the player has.
//
// OUTPUT: A pointer to a dynamically allocated Player. Freeing
//         the memory allocated by this function is the responsibility
//         of the caller.
Player* createPlayer(char* name, int goals, int assists)
{
	Player* newBlue = malloc(sizeof(Player));
	strcpy(newBlue->name, name);
	newBlue->goals = goals;
	newBlue->assists = assists;
	newBlue->next = NULL;
	return newBlue;
}

// Inserts a Player into the linked list in sorted order by name, in
// ascending order (A-Z). The new head of the list, or the original head
// of the list if unchanged, is returned by the function.
//
// INPUT:  head    - The current head of the linked list. 
//         name    - A string to use as the player's name.
//         goals   - The number of goals the player has scored.
//         assists - The number of assists the player has.
//
// OUTPUT: A pointer to the head of the linked list.
//
// NOTE: You may implement this function recursively or iteratively.
Player* insertPlayerInSortedOrderByName(Player* head, char* name, int goals, int assists)
{
	Player* curBlue;
	curBlue = head;
	Player* nextBlue;
	Player* prevBlue = NULL;
	Player* newBlue = createPlayer(name, goals, assists);
	int insertSuccess = FALSE;
	//If first in list, return the new node
	if(curBlue == NULL){
		return newBlue;
	}
	//If not first in list
	else{
		//Loops until end of list or the element has been inserted
		while(curBlue != NULL && insertSuccess == FALSE){
			//If the current players name in list is closer to A
			if((curBlue->name)[0] < name[0]){
				//If there is another player after current
				if(curBlue->next != NULL){
					//Moves onto next player
					prevBlue = curBlue;
					curBlue = curBlue->next;
				}
				else{
					//Sets next player to the new player
					curBlue->next = newBlue;
					insertSuccess = TRUE;
				}
			}
			//If the current players name in list is further from A
			else{
				//If current blue is not the first player in the list
				if(prevBlue != NULL){
					//Has previous player's "next" node point to the new player to be inserted
					prevBlue->next = newBlue;
					//Has the new player's "next" node point to the player that was currently being looked at
					newBlue->next = curBlue;
					insertSuccess = TRUE;
				}
				//If current blue IS the first player in list
				else{
					//Has the new player's "next" point to the current player being looked at
					newBlue->next = curBlue;
					//Makes the new Blue the head of the list
					head = newBlue;
					insertSuccess = TRUE;
				}
			}
		}
		return head;		
	}
}

// Prints all of the Players in the linked list. Players should be printed as follows:
//
// Name             Goals   Assists
// Pietrangelo      3       7
// ...
// Steen            5       2
//
// INPUT: head - The head of the linked list.
//
// NOTE: You must implement this function iteratively or you will receive no points.
// NOTE: You must use formatted output for this function or you will receive no points.
void printPlayers(Player* head)
{
	//Copies head into p to traverse
	Player* p;
	printf("Name                Goals    Assists\n");
	//Traverse each address in list and prints each element of Player
	for(p = head; p != NULL; p = p->next){
		printf("%-20s%-9d%d\n", p->name, p->goals, p->assists);
	}
}

// Determines the length of the linked list.
//
// INPUT:  head - The head of the linked list.
// OUTPUT: The number of elements in the linked list.
//
// NOTE: You may implement this function recursively or iteratively.
int getLengthOfList(Player* head)
{
	int count = 0;
	Player *p = head;
	//Iterates through list and counts number of players
	while(p){
		count++;
		p=p->next;
	}
	return count;
}

// Recursively sorts the linked list by number of goals, in ascending order.
//
// INPUT:  head - The head of the linked list.
// OUTPUT: A pointer to the new head of the linked list.
//
// HINT: You may call getLengthOfList in this function to determine the size
//       of the list, then use that information to split the list into two parts.
//       You need to actually split the list into two parts, by having two Player*
//       variables and appropriately splitting the list with a NULL value.
//
// NOTE: You must implement this function recursively or you will receive no points.
Player* mergeSortByGoals(Player* head)
{
	Player* f_Half = head;
	Player* l_Half = NULL;
	Player* f_Half_Head = head;
	int curLen = getLengthOfList(head);
	int i;
	//If the list is only one player long, return head
	if(curLen == 1){
		return head;
	}
	//If the list is at least 2 players long
	else{
		//Moves the f_Half to the appropriate player
		for(i=0; i<(curLen/2-1); i++){
			f_Half=f_Half->next;
		}
		//Sets the head of the soon to be second list to the appropriate player
		l_Half = f_Half->next;
		//Breaks the single list into two
		f_Half->next = NULL;
		//Recursive calls to eventually create lists of length 1
		f_Half = mergeSortByGoals(f_Half_Head);
		l_Half = mergeSortByGoals(l_Half);
		//Merges lists
		head = merge(f_Half, l_Half);
	} 
	return head;
}

// Merges the two linked lists provided according to the players' number of goals, 
// in ascending order. 
//
// INPUT:  left  - The first linked list to merge.
//         right - The second linked list to merge.
//
// OUTPUT: A pointer to the head of the merged linked list.
//
// NOTE: You must implement this function iteratively or you will receive no points.
Player* merge(Player* left, Player* right)
{
	Player* final = NULL;
	Player* head = NULL;
	//if else that finds which head has the least goals
	if(left->goals <= right->goals){
		head = left;
		left = left->next;
	}
	else{
		head = right;
		right = right->next;
	}
	final = head;
	//While there are elements in each list
	while(right && left){
		//Places left into list if less than right
		if(left->goals < right->goals){
			final->next = left;
			left = left->next;
		}
		//Places right into list if less than left
		else{
			final->next = right;
			right = right->next;
		}
		final = final->next;
	}
	//If there are players in the right list but not left, addes them to final list
	while(right && !left){
		final->next = right;
		right = right->next;
		final = final->next;
	}
	//If there are players in the left list but not the right, adds them to final list
	while(left && !right){
		final->next = left;
		left = left->next;
		final = final->next;
	}
	return head;
}

// Searches the list for a player according to their name.
//
// INPUT:  head - The head of the linked list.
//         name - The name of the player to search for.
// OUTPUT: A pointer to the player, or NULL if not found.
//
// NOTE: You may implement this function recursively or iteratively.
Player* findPlayerByName(Player* head, char* name)
{
	Player* curPlayer;
	curPlayer = head;
	//While there is still a player to be looked at in the list
	while(curPlayer){
		if(strcmp(curPlayer->name, name) == 0){
			printf("Player %s has %d goals and %d assists\n\n", curPlayer->name, curPlayer->goals, curPlayer->assists);
			return head;
		}
		//If the current player is different, change current player to next
		else{
			curPlayer = curPlayer->next;
		}
	}
	printf("Player %s not found\n\n", name);
	return head;

}

// Removes a player from the list according to their name.
//
// INPUT:  head - The head of the linked list.
//         name - The name of the player to remove.
// OUTPUT: A pointer to the new head of the linked list.
//
// NOTE: You may implement this function recursively or iteratively.
// NOTE: If you are unable to find the player in the list, you do not
//       need to indicate this in any way. Simply remove the player if found.
Player* removePlayer(Player* head, char* name)
{
	Player* curPlayer;
	Player* prevPlayer = NULL;
	curPlayer = head;
	//While there is still a player to be looked at in the list
	while(curPlayer){
		//If the current player is the same as the target player
		if(strcmp(curPlayer->name, name) == 0){
			//If the current player is the only player in the list, removes it and returns NULL
			if(curPlayer->next == NULL && curPlayer == head){
				free(curPlayer);
				return NULL;
			}
			//If the current player is the last in the list, but not the only in the list, removes it and returns head
			else if(curPlayer->next == NULL && curPlayer != head){
				prevPlayer->next = NULL;
				free(curPlayer);
				return head;
			}
			//If the current player is the head of the list, but not the only in the list, removes it, changes head and returns it
			else if(curPlayer == head && curPlayer->next){
				head = curPlayer->next;
				free(curPlayer);
				return head;
			}
			//If the current player is somewhere in the middle of a list, removes it, redirects previous pointer, returns head
			else{
				prevPlayer->next = curPlayer->next;
				free(curPlayer);
				curPlayer = prevPlayer->next;
				return head;
			}
		}
		//If the current player is not the same player as name, switches current Player to next and makes previous player equal to the former current player
		else{
			prevPlayer = curPlayer;
			curPlayer = curPlayer->next;
		}
	}
	return head;
}

// Frees the memory in use by the list by recursively freeing each node
// in the list.
//
// INPUT: head - The head of the linked list.
//
// NOTE: You must implement this function recursively or you will receive no points.
void freeList(Player* head)
{
	//recursively frees all players
	if(head->next){
		freeList(head->next);
		free(head);
	}
}

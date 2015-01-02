/* John Curley
 * Prelab 6 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define MAX_LINE 50
 #define MAX_MODEL 20
 #define TRUE 1
 #define FALSE 0
 
 typedef struct car{
	char* model;
	int year;
	struct car* next;
} Car;

Car* insertInSortedOrder(Car* head, char* model, int year);
int updateCar(Car* head, char* targetModel, int newYear);
Car* createCar(char* model, int year);
void print(Car X);


int main(int argc, char** argv){
	FILE* fPtr;
	//Checks to make sure command line contains only two other arguments
	if(argc != 2){
		printf("One and only one command line arguments are allowed, terminating. \n\n");
		return 1;
	}
	
	//Opens files
	fPtr = fopen(argv[1], "r");
	//Checks to make sure files were found
	if(fPtr == NULL){
		printf("Could not file, terminating.\n\n");
		return 1;
	}
	
	char* tempLine = malloc(MAX_LINE*sizeof(char));
	char* tempModel = malloc(MAX_MODEL*sizeof(char));
	Car* curHead = NULL;
	int tempYear, updateInt;
	while(fgets(tempLine, MAX_LINE, fPtr) != NULL){
		if(tempLine){
			strcpy(tempModel, strtok(tempLine," ,\n"));
			tempYear = atoi(strtok(NULL," ,\n"));
			printf("tempYear: %d\n", tempYear);
			curHead = insertInSortedOrder(curHead, tempModel, tempYear);
		}
		else{
			printf("Error, templine not read\n\n");
			return -1;
		}
	}
	print(*curHead);
	updateInt = updateCar(curHead, "Ford", 2003);
	if(updateInt == -1){
		printf("Update failed, model not found.\n");
	}
	else{
		printf("\n\nUpdated list: \n\n");
		print(*curHead);
	}
	return 0;
}

Car* insertInSortedOrder(Car* head, char* model, int year){
	Car* curCar;
	curCar = head;
	Car* nextCar;
	Car* prevCar = NULL;
	Car* newCar = createCar(model, year);
	int insertSuccess = FALSE;
	//If first in list, return the new node
	if(curCar == NULL){
		return newCar;
	}
	//If not first in list
	else{
		//Loops until end of list or the element has been inserted
		while(curCar != NULL && insertSuccess == FALSE){
			//If the current players name in list is closer to A
			//printf("First letter model: %c\n", (curCar->model)[0]);
			if((curCar->model)[0] < model[0]){
				//If there is another player after current
				if(curCar->next != NULL){
					//Moves onto next player
					prevCar = curCar;
					curCar = curCar->next;
				}
				else{
					//Sets next player to the new player
					curCar->next = newCar;
					insertSuccess = TRUE;
					printf("reached here at curCar = %c\n", (curCar->model)[0]);
				}
			}
			//If the current players name in list is further from A
			else{
				//If current blue is not the first player in the list
				if(prevCar != NULL){
					//Has previous player's "next" node point to the new player to be inserted
					prevCar->next = newCar;
					//Has the new player's "next" node point to the player that was currently being looked at
					newCar->next = curCar;
					insertSuccess = TRUE;
				}
				//If current blue IS the first player in list
				else{
					//Has the new player's "next" point to the current player being looked at
					newCar->next = curCar;
					//Makes the new Blue the head of the list
					head = newCar;
					insertSuccess = TRUE;
				}
			}
		}
		return head;		
	}
}

int updateCar(Car* head, char* targetModel, int newYear){
		Car* curCar;
		curCar = head;
		while(curCar){
			if(strcmp(curCar->model, targetModel) == 0){
				curCar->year = newYear;
				return 1;
			}
			else{
				curCar = curCar->next;
			}
		}
		return -1;
}

Car* createCar(char* model, int year){
	Car* newCar = malloc(sizeof(Car));
	newCar->model = malloc(sizeof(char)*MAX_MODEL);
	strcpy(newCar->model, model);
	newCar->year = year;
	printf("Year: %d\n", year);
	newCar->next = NULL;
	return newCar;
}

void print(Car X){
	//Copies X into new p to traverse
	Car* p;
	//Traverse each address in list and prints each element of struct
	for(p = &X; p != NULL; p = p->next){
		printf("%s %d\n", p->model, p->year);
	}
}
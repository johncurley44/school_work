/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 6 - 3/12/2013
 * BONUS COMPLETE
 */
 
//Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 //Global Constants
 #define MAX_LINE 50
 #define MAX_MODEL 20
 #define TRUE 1
 #define FALSE 0
 //Car definition
  typedef struct car{
	char* model;
	int year;
	struct car* next;
  } Car;
//Function Prototypes
 Car* readFromFile(FILE* fPtr);
 Car* createCar(char* model, int year);
 Car* insertInSortedOrder(Car* head, char* model, int year);
 Car* removeCar(Car* head, char* targetModel);
 int updateCar(Car* head, char* targetModel, char* newModel);
 void printCars(Car* head);
 Car* reverseList(Car* head);
/* Function Purpose: Tests every function in file, asking for several user-interface inputs
 * Input params: argc - number of arguments in commandline prompt / argv - array of strings of commandline prompts
 * Return param: some int
 **/
 int main(int argc, char** argv){
	FILE* fPtr;
	Car* head;
	char remove[MAX_MODEL];
	char updated[MAX_MODEL];
	char newCar[MAX_MODEL];
	int updateCheck;
	Car* freeCar;
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
	//Calls readFromFile to create new linked list of cars, head is the head of the list
	head = readFromFile(fPtr);
	printf("Original List:\n\n");
	//Calls printCars to print the list
	printCars(head);
	printf("\nEnter a model to update: ");
	scanf("%s", updated);
	printf("Enter a new value for the model: ");
	scanf("%s", newCar);
	//Calls updateCar to change one of the models, returns 1 (TRUE) if somethine was found and changed
	updateCheck = updateCar(head, updated, newCar);
	//If update was performed
	if(updateCheck == TRUE){
		printf("Car found and updated\n");
		printf("\nUpdated list:\n\n");
		printCars(head);
	}
	//If car target was not found and no update was performed
	else{
		printf("Car not found. No update performed\n");
	}
	//User input for car to remove
	printf("\nEnter a car model to remove: ");
	scanf("%s", remove);
	//Calls removeCar to remove user input car
	head = removeCar(head, remove);
	//If the removed car wasn't the only one in the list
	if(!head){
		printf("\nNo Cars left remaining in list!\n\n");
	}
	//If there are still cars left in the list after removeCar is called
	else{
		printf("List with car removed:\n\n");
		printCars(head);
	}
	//Calls bonus reverseList to reverse the order, then print
	head = reverseList(head);
	printf("\n----- BONUS -----\n\n");
	printCars(head);
	fclose(fPtr);
	//Frees each Car in link list
	while(head){
		free(head->model);
		freeCar = head->next;
		free(head);
		head = freeCar;
	}
	return 0;
 }
/* Function Purpose: Reads and parses lines from the imput file, then calls insertInSortedOrder to add them to a linked list.
 * Input params: File to be read from
 * Return param: Pointer to the head of the linked list created
 **/
Car* readFromFile(FILE* fPtr){
	char tempLine[MAX_MODEL];
	char tempModel[MAX_MODEL];
	Car* curHead = NULL;
	int tempYear, updateInt;
	//While there are still lines to be read from the file
	while(fgets(tempLine, MAX_LINE, fPtr) != NULL){
		//If the line read is not empty
		if(tempLine){
			//Copies the model from the first fgets statement into a temporary string tempModel
			strcpy(tempModel, strtok(tempLine," ,\n"));
			//Copies the model year into temporary integer tempYear
			tempYear = atoi(strtok(NULL," ,\n"));
			//Calls insertInSortedOrder to add new car to linked list in alphabetical order
			curHead = insertInSortedOrder(curHead, tempModel, tempYear);
		}
		//If the line read is empty. Means something has gone wrong in coding/file.
		else{
			printf("Error, templine not read\n\n");
			return NULL;
		}
	}
	return curHead;
}
/* Function Purpose: Creates a new Car that has the given model and year. 
 * Input params: New car's model and year
 * Return param: Pointer to the new car
 **/
Car* createCar(char* model, int year){
	//Malloc'd space for Car pointer and the model string
	Car* newCar = malloc(sizeof(Car));
	newCar->model = malloc(sizeof(char)*MAX_MODEL);
	//Copies the input model string into the new Car's model element
	strcpy(newCar->model, model);
	//Copies the input year into the new Car's year element
	newCar->year = year;
	//Sets the newCar next pointer to null
	newCar->next = NULL;
	return newCar;
}
/* Function Purpose: Uses createCar in order to make a new Car, then inserts (in ascending alphabetical order) that Car into the linked list beginning with head.
 * Input params: head of linked list, model string and year ineger of Car
 * Return param: head of the list
 **/
Car* insertInSortedOrder(Car* head, char* model, int year){
	Car* curCar;
	curCar = head;
	Car* nextCar;
	Car* prevCar = NULL;
	int insertSuccess = FALSE;
	Car* newCar = createCar(model, year);
	//If first in list, return the new node
	if(curCar == NULL){
		return newCar;
	}
	//If not first in list
	else{
		//Loops until end of list or the element has been inserted
		while(curCar != NULL && insertSuccess == FALSE){
			//If the current Car model in list is closer to A
			if((curCar->model)[0] < model[0]){
				//If there is another Car after current
				if(curCar->next != NULL){
					//Moves onto next Car
					prevCar = curCar;
					curCar = curCar->next;
				}
				else{
					//Sets next Car to the new Car
					curCar->next = newCar;
					insertSuccess = TRUE;
				}
			}
			//If the current Car's name in list is further from A
			else{
				//If current Car is not the first Car in the list
				if(prevCar != NULL){
					//Has previous Car's "next" node point to the new Car to be inserted
					prevCar->next = newCar;
					//Has the new Car's "next" node point to the Car that was currently being looked at
					newCar->next = curCar;
					insertSuccess = TRUE;
				}
				//If current Car IS the first Car in list
				else{
					//Has the new Car's "next" point to the current Car being looked at
					newCar->next = curCar;
					//Makes the new Car the head of the list
					head = newCar;
					insertSuccess = TRUE;
				}
			}
		}
		return head;		
	}
}
/* Function Purpose: Finds the Car with model targetModel and removes it form the linked list. Regardless of whether the Car is found in the list or not,
 * 					 this function always returns the head of the linked list. Assumes that at most one car has a model of targetModel.
 * Input params: head of linked list, targetModel - the model to be searched for
 * Return param: head of list
 **/
Car* removeCar(Car* head, char* targetModel){
	Car* curCar;
	Car* prevCar = NULL;
	curCar = head;
	//While there is still a car to be looked at in the list
	while(curCar){
		//If the current Car's model is the same as the target model
		if(strcmp(curCar->model, targetModel) == 0){
			//If the current car is the only car in the list, removes it and returns NULL
			if(curCar->next == NULL && curCar == head){
				free(curCar);
				return NULL;
			}
			//If the current car is the last in the list, but not the only in the list, removes it and returns head
			else if(curCar->next == NULL && curCar != head){
				prevCar->next = NULL;
				free(curCar);
				return head;
			}
			//If the current car is the head of the list, but not the only in the list, removes it, changes head and returns it
			else if(curCar == head && curCar->next){
				head = curCar->next;
				free(curCar);
				return head;
			}
			//If the current car is somewhere in the middle of a list, removes it, redirects previous pointer, returns head
			else{
				prevCar->next = curCar->next;
				free(curCar);
				curCar = prevCar->next;
				return head;
			}
		}
		//If the current car is not the same model as targetModel, switches current car to next and makes previous car equal to the former current car
		else{
			prevCar = curCar;
			curCar = curCar->next;
		}
	}
	return head;
}
/* Function Purpose: Searches for a Car in the linked list beginning at head with the model targetModel.
 * Input params: head of linked list, targetModel to be searched, newModel to replace targetModel with
 * Return param: If found, the model for the Car is replaced by newModel and 1 is returned. If not found, -1 is returned.
 **/
int updateCar(Car* head, char* targetModel, char* newModel){
		Car* curCar;
		curCar = head;
		//While there is still a car to be looked at in the list
		while(curCar){
			//If the current car model is the same as targetModel, change current car model to targetModel
			if(strcmp(curCar->model, targetModel) == 0){
				strcpy(curCar->model, newModel);
				return 1;
			}
			//If the current model is different, change current car to next
			else{
				curCar = curCar->next;
			}
		}
		return -1;
}
/* Function Purpose: Prints all of the cars from the linked list.
 * Input params: head of linked list
 * Return param: void
 **/
void printCars(Car* head){
	//Copies head into p to traverse
	Car* p;
	printf("Model               Year\n---------------------------\n");
	//Traverse each address in list and prints each element of Car
	for(p = head; p != NULL; p = p->next){
		printf("%-19s %d\n", p->model, p->year);
	}
}
/* Function Purpose: Reverses the order of the cars in the list
 * Input params: head of linked list
 * Return param: new head of list
 **/
Car* reverseList(Car* head){
	Car* curCar = head;
	Car* nextCar = NULL;
	Car* prevCar = NULL;
	int contLoop = TRUE;
	//While curCar has a value and sentinal value (contLoop) true
	while(curCar && contLoop == TRUE){
		//If there is car after the current car
		if(curCar->next){
			//sets nextCar equal to the one after current
			nextCar = curCar->next;
			//has next pointer of current car point to previous car
			curCar->next = prevCar;
			//sets prevCar as curCar
			prevCar = curCar;
			//sets curCar to the next car in the list
			curCar = nextCar;
		}
		//If looking at the last car in the list
		else{
			//Sets the next pointer of the current car to the previous car
			curCar->next = prevCar;
			//Cancels while loop using sentinal value
			contLoop = FALSE;
		}
	}
	return curCar;
}
				
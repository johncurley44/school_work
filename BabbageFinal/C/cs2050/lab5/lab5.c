/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 5 - 3/5/13
 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 //Global constants
 #define MAX_NAME 20
 #define MAX_LINE 100
 //Global Struct
 struct record{
	int age;
	char f_name[MAX_NAME];
	char l_name[MAX_NAME];
	struct record *next;
	};
 typedef struct record Record;
 
 //Function prototypes
 Record *Open(FILE *pt);
 Record *Link_Back(Record *Head, char first_name[], char last_name[], int age);
 Record *Link_Front(Record *Head, char first_name[], char last_name[], int age);
 Record *Create_Record(char first_name[], char last_name[], int age);
 void print_Record(Record X);
 Record *Delete_Decade(Record *Head, int decade);
/* Function Purpose: Reads in a file, checks to make sure file can be opened and correct 
 * 					  number of user input, constructs and prints list, asks for modification, reprints
 * Input params: argc - number of arguments, argv - array of strings of arguments
 * Return param: some int
 **/
 int main(int argc, char **argv){
	FILE *fp;
	int decade;
	//1. Checks to make sure command line contains only one other argument (file name)
	if(argc != 2){
		printf("Only one command line argument allowed, terminating. \n\n");
		return 1;
	}
	
	//Opens file
	fp = fopen(argv[1], "r");
	
	//Checks to make sure file was found
	if(fp == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	//Creates a Record pointer, sends to Open
	Record* mainRecord = Open(fp);
	//Prints record as read from file
	print_Record(*mainRecord);
	//Asks user which decade to delete, calls function, reprints new list
	printf("\nWhich decade would you like to delete?\n");
	scanf("%d", &decade);
	printf("\n");
	mainRecord = Delete_Decade(mainRecord, decade);
	print_Record(*mainRecord);
	//Free list
	free(mainRecord);
	return 0;
 }
/* Function Purpose: Opens the file, reads the lines and call appropriate link function
 * Input params: File to be read from
 * Return param: Head of link list formed
 **/
 Record *Open(FILE *pt){
	//Check with user on where to put new link. Continue until valid input is provided
	int cont_loop = 1;
	char userIn[MAX_NAME];
	while(cont_loop == 1){
		printf("Would you like to insert at the beginning or end?\n");
		scanf("%s", userIn);
		if(strcmp(userIn, "end") == 0 || strcmp(userIn, "beginning") == 0){
			cont_loop = 0;
		}
		else{
			printf("Please try again. Input must be exactly \"end\" or \"beginning\".\n");
		}
	}
	//Declare Record pointer and malloc strings to store information from file temporarily
	Record* newRecord;
	char* tempLine = malloc(MAX_LINE*sizeof(char));
	char* first_name = malloc(MAX_NAME*sizeof(char));
	char* last_name = malloc(MAX_NAME*sizeof(char));
	int age;
	//Reads each line in file and calls appropriate link function based on user input
	while(fgets(tempLine, MAX_LINE, pt) != NULL){
		strcpy(first_name, strtok(tempLine, " \n"));
		strcpy(last_name, strtok(NULL, " \n"));
		age = atoi(strtok(NULL, " \n"));
		if(strcmp(userIn, "end") == 0){
			newRecord = Link_Back(newRecord, first_name, last_name, age);
		}
		else if(strcmp(userIn, "beginning") == 0){
			newRecord = Link_Front(newRecord, first_name, last_name, age);
		}
		else{
			printf("\nError. Neither end or beginning detected as user input\n");
		}
	}
	//Frees charactr pointers malloced at beginnning to temporarily hold variables
	free(last_name);
	free(first_name);
	free(tempLine);
	return newRecord;
}
/* Function Purpose: Creates new struct and links it to the back of the list
 * Input params: Head of current list, first name, last name and age of struct to be added to list
 * Return param: Head of list
 **/
Record *Link_Back(Record *Head, char first_name[], char last_name[], int age){
	Record* newRecord;
	Record* saveHead = Head;
	//Calls Create_Record to form record struct to add
	newRecord = Create_Record(first_name, last_name, age);
	//If first element of list, returns the struct pointer
	if(Head == NULL){
		return newRecord;
	}
	//If not first element
	else{
		//Traverses to end of list
		while(Head->next != 0){
			Head = Head->next;
		}
		//Points new record to the end of the list
		Head->next = newRecord;
	}
	return saveHead;
}
/* Function Purpose: Creates new struct and links it to the front of the list
 * Input params: Head of list, first name, last name, and age of struct to add to list
 * Return param: New head of list
 **/
Record *Link_Front(Record *Head, char first_name[], char last_name[], int age){
	Record* newRecord;
	//Calls Create_Record to create new Record to add to list
	newRecord = Create_Record(first_name, last_name, age);
	//If first element in list, returns the created struct pointer
	if(Head == NULL){
		return newRecord;
	}
	//If not first element in list
	else{
		//Makes the new struct point to current head
		newRecord->next = Head;
		//Sets the new record as the head of the list
		Head = newRecord;
	}
	return Head;
}
/* Function Purpose: Fills struct with information
 * Input params: First name, last name, and age of subject
 * Return param: Pointer to record created
 **/
Record *Create_Record(char first_name[], char last_name[], int age){
	Record *newRecord = malloc(sizeof(Record));
	strcpy(newRecord->f_name, first_name);
	strcpy(newRecord->l_name, last_name);
	newRecord->age = age;
	newRecord->next = NULL;
	return newRecord;
}
/* Function Purpose: Prints each element of list
 * Input params: Record value
 * Return param: void
 **/
void print_Record(Record X){
	//Copies X into new p to traverse
	Record* p;
	//Traverse each address in list and prints each element of struct
	for(p = &X; p != NULL; p = p->next){
		printf("%s %s %d\n", p->f_name, p->l_name, p->age);
	}
}
/* Function Purpose: Deletes all information from list that is associated with a certain decade
 * Input params: Head of list, year in decade that is to be deleted
 * Return param: Head of list
 **/
Record *Delete_Decade(Record *Head, int decade){
	Record *checkRec = Head;
	Record *prevLink = NULL;
	int cmpDec;
	//Comparison int that is the first year in the decade to delete
	cmpDec = (decade - (decade%10));
	//Traverses list until at the last node
	while(checkRec != NULL){
		//If age is in decade
		if(checkRec->age >= cmpDec && checkRec->age < (cmpDec+10)){
			//If information found isnt the first node, deletes node, links previous to next
			if(prevLink != NULL){
				prevLink->next = checkRec->next;
				free(checkRec);
				checkRec = prevLink->next;
			}
			//If information found is the first node, deletes node, makes next node head
			else{
				checkRec = checkRec->next;
				Head = checkRec;
			}
		}
		//If age is not in decade, checks next node
		else{
			prevLink = checkRec;
			checkRec = checkRec->next;
		}
	}
	return Head;
}
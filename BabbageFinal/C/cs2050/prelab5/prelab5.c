/* John Curley
 * Prelab 5 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define MAX_NAME 20
 #define MAX_LINE 100
 
 struct record{
	int dob;
	char f_name[MAX_NAME];
	char l_name[MAX_NAME];
	struct record *next;
	};
 typedef struct record Record;
 
 //function prototypes
 Record *open(FILE *fp);
 Record *Link(Record *X, char first_name[], char last_name[], int dob);
 Record *create_Record(char first_name[], char last_name[], int dob);
 void print_Record(Record *X);
 
 
 int main(int argc, char **argv){
	FILE *fp;
	fp = fopen(argv[1], "r");
	Record* mainRecord = open(fp);
	//printf("FROM MAIN: %s %s %d\n", mainRecord->f_name, mainRecord->l_name, mainRecord->dob);
	print_Record(mainRecord);
	free(mainRecord);
 }
 
 Record *open(FILE *fp){
	//Record* newRecord = malloc(sizeof(Record));
	//Record* root;
	//Record* newRecord = root;
	Record* newRecord;
	char* tempLine = malloc(MAX_LINE*sizeof(char));
	char* first_name = malloc(MAX_NAME*sizeof(char));
	char* last_name = malloc(MAX_NAME*sizeof(char));
	int dob;
	
	while(fgets(tempLine, MAX_LINE, fp) != NULL){
		strcpy(first_name, strtok(tempLine, " \n"));
		strcpy(last_name, strtok(NULL, " \n"));
		dob = atoi(strtok(NULL, " \n"));
		//WORKS HERE printf("From open: %s %s %d\n", first_name, last_name, dob);
		newRecord = Link(newRecord, first_name, last_name, dob);
		//DONT DO THISSSSSS newRecord++;
		//WORKS HERE printf("From open 2: %s %s %d\n", newRecord->f_name, newRecord->l_name, newRecord->dob);
	}
	free(last_name);
	free(first_name);
	free(tempLine);
	return newRecord;
}

Record * Link(Record *X, char first_name[], char last_name[], int dob){
/*DO YOU HAVE TO MALLOC HERE?>???*/	Record* newRecord; //= malloc(sizeof(Record)); 
	Record* saveHead = X;
	newRecord = create_Record(first_name, last_name, dob);
	//WORKS HERE
	//printf("From Link: %s %s %d\n", newRecord->f_name, newRecord->l_name, newRecord->dob);
	if(X == NULL){
		//printf("Found, x ==NULL\n");
		return newRecord;
	}
	else{
		while(X->next != 0){
			X = X->next;
		}
		X->next = newRecord;
		//printf("From Link2: %s %s %d\n", newRecord->f_name, newRecord->l_name, newRecord->dob);
	}
	return saveHead;
}

Record *create_Record(char first_name[], char last_name[], int dob){
	Record *newRecord = malloc(sizeof(Record));
	strcpy(newRecord->f_name, first_name);
	strcpy(newRecord->l_name, last_name);
	newRecord->dob = dob;
	//WORKS HEREprintf("From create: %s %s %d\n", newRecord->f_name, newRecord->l_name, dob);
	newRecord->next = NULL;
	return newRecord;
}

void print_Record(Record *X){
	Record* p;
	for(p = X; p != NULL; p = p->next){
		printf("%s %s %d\n", p->f_name, p->l_name, p->dob);
	}
}
			
	
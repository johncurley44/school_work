/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: Final Countdown
 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define MAX 9
 #define MAXNAME 20
 #define TRUE 1
 #define FALSE 0
 
 //Structure definition
 typedef struct {
   int id;
   char* name;
   float gpa;
} data;

//Funciton prototypes
void initialize(data student[], int size);
void sort_by_id(data student[], int size);
void sort_by_gpa(data student[], int size);
void print(data student[], int size);

/* Function Purpose: Takes in number of records from command line. Creates data array then calls functions to initialize, sort and print data.
 * Input params: number of inputs and a character array that will contain a.out and input size from command line
 * Return param: some integer
 **/
int main(int argc, char* argv[]){
	//Checks to make sure 2 inputs were entered on command line, including executable file name, prints error message and quits if not
	if(argc != 2){
		printf("USAGE: ./a.out SIZE (0<SIZE<10)\n\n");
		return 1;
	}
	//Changes input size character to int
	int size = atoi(argv[1]);
	int sortChoice, count = 0;
	//Creates memory for students (data type) array
	data students[MAX];
	//initializes elements and prints them
	initialize(students, size);
	print(students, size);
	//Error checks to ensure user inputs valid number, 1 or 2, for sorting option
	do{
		printf("Sort by: (1) ID or (2) GPA? ");
		scanf("%d", &sortChoice);
		//Calls id sort if input=1, prints sorted array
		if(sortChoice == 1){
			printf("\nSorted by ID\n");
			sort_by_id(students, size);
			print(students, size);
		}
		//calls gpa sort if input=2, prints sorted array
		else if(sortChoice == 2){
			printf("\nSorted by GPA\n");
			sort_by_gpa(students, size);
			print(students, size);
		}
		//prints invalid selection if neither 1 or 2 was entered
		else{
			printf("Invalid Selection\n");
		}
		
	}while(sortChoice != 1 && sortChoice != 2);
	//frees each allocated pointer in the name field of data students[]
	do{
		free(students[count].name);
		count++;
	}while(count < size);

	return 0;
}	

/* Function Purpose: Asks user for ID, name, and GPA for each element of array student
 * Input params: blank array of type student, size of that array
 * Return param: void
 **/
void initialize(data student[], int size){
	int count = 0;
	//Creates blank string to store temporary information
	char tempString[MAXNAME];
	int idCheck, gpaCheck;
	printf("\n");
	do{
		//Resets idCheck to keep loop valid
		idCheck = FALSE;
		do{
			printf("Please enter student ID: ");
			scanf("%d", &(student[count].id));
			//Changes sentinel value to stop loop
			if(student[count].id < 1000 && student[count].id > 99){
				idCheck = TRUE;
			}
			else{
				printf("Invalid ID. (100 <= ID <= 999)\n");
			}
		}while(idCheck == FALSE);
		
		printf("Student name: ");
		scanf("%s", tempString);
		//Allocates memory for name field in current element of student. Uses length of input string, tempString, to allocate exact number of elements required
		student[count].name = (char*)(malloc(sizeof(char)*strlen(tempString)));
		strcpy(student[count].name, tempString);
		//Resets gpaCheck to keep loop valid
		gpaCheck = FALSE;
		 do{
			printf("Student GPA: ");
			scanf("%f", &(student[count].gpa));
			//Changes sentinel value to stop loop
			if(student[count].gpa <= 4.0 && student[count].gpa >= 0){
				gpaCheck = TRUE;
			}
			else{
				printf("Invalid ID. (0 <= GPA <= 4.0)\n");
			}
		}while(gpaCheck == FALSE);
		
		count++;
	}while(count < size);
}

/* Function Purpose: Sorts data array, student, based on id from lowest to highest
 * Input param: data array filled with IDs, names, and GPAs and size of that array
 * Return param: void
 **/
void sort_by_id(data student[], int size){
	int count1 = 0;
	data tempSave;
	//Iterates through each element of array
	do{
		//Resets count2 to keep loop valid
		int count2 = 1;
		//Compares each element of array and swaps adjacent elements if second is greater than first
		do{
			if(student[count2].id < student[count2 - 1].id){
				tempSave = student[count2 - 1];
				student[count2 - 1] = student[count2];
				student[count2] = tempSave;
			}
			count2++;
		}while(count2 < size);
		count1++;
	}while(count1 < size);
}

/* Function Purpose: Sorts data array, student, based on GPA from lowest to highest
 * Input param: data array filled with IDs, names, and GPAs and size of that array
 * Return param: void
 **/
void sort_by_gpa(data student[], int size){
	int count1 = 0;
	data tempSave;
	//Iterates through each element of array
	do{
		//Resets count2 to keep loop valid
		int count2 = 1;
		//Compares each element of array and swaps adjacent elements if second is greater than first
		do{
			if(student[count2].gpa < student[count2 - 1].gpa){
				tempSave = student[count2 - 1];
				student[count2 - 1] = student[count2];
				student[count2] = tempSave;
			}
			count2++;
		}while(count2 < size);
		count1++;
	}while(count1 < size);	
}

/* Function Purpose: Prints all fields of each element of data array, student
 * Input param: data array filled with IDs, names, and GPAs and size of that array
 * Return param: void
 **/
void print(data student[], int size){
	int count = 0;
	printf("----------------------------\nID   Name           GPA\n");
	//Iterates through each element of student and prints each field
	do{
		printf("%-5d%-15s%.2f\n", student[count].id, student[count].name, student[count].gpa);
		count++;
	}while(count < size);
	printf("\n");
}
 //int main(int argc, char* argv[])
 //int size = atoi(argv[2]);
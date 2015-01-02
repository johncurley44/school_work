/* John Curley - jmcgdd *
 * Lab Section: C       *
 * Homework 4			*/
 
 //Preprocess commands
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 //Definition constants
 #define TRUE 1
 #define FALSE 0
 #define MAXSTR 20
 #define GRADES 3
 #define LETTERS 5
 
 //data Structure definition
typedef struct
{
	int id;
	char name[10];
	int hw;
	int quiz;
	int midterm;
	char grade;
}data;
//Function Prototypes
data* read_info(int size);
void print_info(data *student, int n);
void update_score(data *, int size);
void calculate_grades(data *student, int size);
void compute_stats(data *student, int size);
int checkID(int studID, data* stuData, int size);
void print_histogram(data *student, int size);


int maxGrade = 0, minGrade = 303, avgGrade = 0, saveMinID = 0, saveMaxID = 0;
char saveMaxStudent[MAXSTR], saveMinStudent[MAXSTR];

/* Function Purpose: Calls all functions to create, modify and print structs of type data containing student's information. Prints histogram to show grades.
 * Input params: None
 * Return param: some integer (main)
 **/
int main(void){
	int size = 0;
	//Asks user for number of students
	printf("\nEnter the size of the input: ");
	scanf("%d", &size);
	printf("\n");
	//Uses readInfo function to fill each struct
	data* studentInfo = read_info(size);
	//Prints each student's info
	print_info(studentInfo, size);
	//Calls update_score to modify grades
	update_score(studentInfo, size);
	printf("\nUpdated Score\n");
	//Prints new info
	print_info(studentInfo, size);
	//Calculates the letter grades
	calculate_grades(studentInfo, size);
	//Calculates group stats
	compute_stats(studentInfo, size);
	//Frees student info memory
	free(studentInfo);
	
}	

/* Function Purpose: Asks user to input information for n students, where n is user input from main.
 * Input params: Number of students in group.
 * Return param: Struct of data type that contains all information for n individual students.
 **/
data* read_info(int size){
	int count = 0;
	//Reserves memory for dataStruct
	data* dataStruct = (data*)malloc(sizeof(data)*size);
	//Asks user to input student ID, name, hw score, quiz score and midterm score for each student
	while(count<size){
		if(count > 0){
			dataStruct++;
		}
		printf("Please enter student ID: ");
		scanf("%d", &((*dataStruct).id));
		printf("Student name: ");
		scanf("%s", &((*dataStruct).name));
		printf("Homework score: ");
		scanf("%d", &((*dataStruct).hw));
		printf("Quiz score: ");
		scanf("%d", &((*dataStruct).quiz));
		printf("Midterm score: ");
		scanf("%d", &((*dataStruct).midterm));
		printf("\n");
		count++;
	}
	//Brings dataStruct pointer back to the first location
	dataStruct -= (count - 1);
	return dataStruct;
}

/* Function Purpose: Prints student information (ID, name, and hw, quiz and midterm scores
 * Input params: The struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: None
 **/
void print_info(data *student, int size){
		printf("ID    Name      HW  Quiz  Midterm\n\n");
		int count = 0;
		//Prints the student ID, name, hw score, quiz score and midterm score for each student
		while(count < size){
			printf("%-5d %-9s %-4d %-6d %d\n", (*student).id, (*student).name, (*student).hw, (*student).quiz, (*student).midterm);
			student++;
			count++;
		}
		//Returns student back to original position
		student-=count;
		printf("\n");
}

/* Function Purpose: Updates a student's homework, quiz, or midterm score by asking user for change in score.
 * Input params: The struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: None
 **/
void update_score(data *stuData, int size){
	int stuID, score, member, contUpdate, contYesNo, count = 0, idLoc = 0;
	int isID = FALSE;
	int endCheck = FALSE;
	char checkStr[MAXSTR], yesOrNo[MAXSTR];
	int stopCheck = FALSE;
	//Keeps asking for student ID to update until user enters "no" when prompted at the end of the loop
	do{
		//When count is greater than 0, resets stuData pointer to original location
		if(count > 0){
			stuData -= (idLoc - 1);
		}
		do{
			//Resets endCheck in case the loop has already cycled at least once.
			endCheck = FALSE;
			count = 0;
			printf("Enter student ID to update the score: ");
			scanf("%d", &stuID);
			//Goes through each student and if ID is found, saves the location of that id to allow the resetting of the pointer later
			do{
				isID = checkID(stuID, stuData, size);
				if(isID == TRUE){
					endCheck = TRUE;
					idLoc = count + 1;
				}
				stuData++;
				count++;
			}while(count < size);
			//If the ID wasnt found, prints error statement and returns to top of loop to ask for a new ID
			if(endCheck == FALSE){
				printf("Invalid ID\n\n");
				count = 0;
				//Resets pointer to original location
				stuData -= size;
			}
			//Sets the pointer to the postion of the ID that was searched and found
			else{
				stuData -= (size - idLoc +1);
			}
		}while(endCheck == FALSE);
		// Asks user for the score to update, continues until a valid input is given
		do{
			printf("Enter the score you want to update: ");
			scanf("%s", checkStr);
			//If hw, stops loop and saves member to use later
			if(strcmp(checkStr, "hw") == 0){
				stopCheck = TRUE;
				member = 1;
			}
			//If quiz, stops loop and saves member to use later
			else if(strcmp(checkStr, "quiz") == 0){
				stopCheck = TRUE;
				member = 2;
			}
			//If midterm, stops loop and saves member to use later
			else if(strcmp(checkStr, "midterm") == 0){
				stopCheck = TRUE;
				member = 3;
			}
			//If invalid input, prints error statement and continues loop
			else{
				stopCheck = FALSE;
				printf("Please enter a valid option (hw, quiz, or midterm)\n");
			}
		}while(stopCheck == FALSE);
	
		printf("Enter the %s score: ", checkStr);
		scanf("%d", &score);
		//Uses member, saved in previous loop, to ask for update to grade and to change that grade
		switch(member){
			//hw chosen
			case 1:
				stuData->hw += score;
				break;
			//quiz chosen
			case 2: 
				stuData->quiz += score;
				break;
			//midterm chosen
			case 3:
				stuData->midterm += score;
				break;
			//None of three detected, prints error message that there is a problem earlier in the program
			default:
				printf("Error: member value incorrect, check code");
				break;
		}
		//Loop that asks if user wishes to continue updating score. Asks repeatedly until "yes" or "no" is entered
		do{
			printf("\nDo you want to update more scores type yes or no: ");
			scanf("%s", yesOrNo);
			printf("\n");
			//If input is yes, continue to update ID but not loop to ask whether or not to update more scores
			if(strcmp(yesOrNo,"yes") == 0){
				contUpdate = TRUE;
				contYesNo = FALSE;
			}
			//If input is no, do not continue to update ID or the loop to ask whether or not to update more scores
			else if(strcmp(yesOrNo,"no") == 0){
				contUpdate = FALSE;
				contYesNo = FALSE;
			}
			//If input is neither, ask again whether or not to update scores
			else{
				printf("Invalid entry\n");
				contYesNo = TRUE;
			}
		}while(contYesNo == TRUE);
		
	}while(contUpdate == TRUE);	
}	

/* Function Purpose: Calculates each student's overall grade based on their 3 scores, saves those grades as characters in struct.
 * Input params: The struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: None
 **/
void calculate_grades(data *student, int size){
	int count = 0;
	int total = 0, avg = 0;
	//Takes total of each student's scores and devides them by 3 to get average. Then assigns a grade to the "grade" field of the data struct
	do{
		total = (*student).hw + (*student).quiz + (*student).midterm;
		avg = total/GRADES;
		if(avg >= 90){
			student->grade = 'A';
		}
		else if(avg >= 80 && avg < 90){
			student->grade = 'B';
		}
		else if(avg >= 70 && avg < 80){
			student->grade = 'C';
		}
		else if(avg >= 60 && avg < 70){
			student->grade = 'D';
		}
		else{
			student->grade = 'F';
		}
		count++;
		student++;
		
	}while(count < size);
	//Resets student pointer to first position
	student-=count;
}

/* Function Purpose: Computes best grade, worst grade, and class average and prints them. Also prints the histogram found from the print_histogram function
 * Input params: The struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: None
 **/
void compute_stats(data *student, int size){
	int count = 0,  totalGrade = 0, studentGrade = 0; 
	double holdGrade, holdSize, holdMax, holdMin, gradesDouble = 3.0;
	//Goes through each student to calculate class average and the maximum and minimum averages of individuals
	do{
		//Total grade of class
		totalGrade += (*student).hw + (*student).quiz + (*student).midterm;
		//Individual student total grade
		studentGrade = (*student).hw + (*student).quiz + (*student).midterm;
		//Max Grade check, replaces current max with current student grade if greater
		if(studentGrade > maxGrade){
			maxGrade = studentGrade;
			saveMaxID = (*student).id;
			strcpy(saveMaxStudent, student->name);
		}
		
		//Min Grade check, replaces current in with current student grade if less
		if(studentGrade < minGrade){
			minGrade = studentGrade;
			saveMinID = (*student).id;
			strcpy(saveMinStudent, student->name);
		}
		count++;	
		student++;
	}while(count < size);
	//Resets student pointer back to first location
	student-=count;
	holdGrade = (double)totalGrade;
	holdSize = (double)size;
	printf("Class average is %.2lf\%\n\n", holdGrade/(holdSize*gradesDouble));
	holdMax = (double)(maxGrade);
	holdMin = (double)(minGrade);
	printf("Student with the highest marks\n%d %s with the total of %.2lf\%\n\n", saveMaxID, saveMaxStudent, holdMax/gradesDouble);
	printf("Student with the lowest marks\n%d %s with the total of %.2lf\%\n\n", saveMinID, saveMinStudent, holdMin/gradesDouble);
	//Prints grade distribution using print_histogram function
	printf("Grade distribution\n\n");
	print_histogram(student, size);
	printf("\n\n");
}
	
/* Function Purpose: Checks to see if the input ID is in any of the structs.
 * Input params: int, studID, the id to be searched, the struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: 1 for true, 0 for false.
 **/
int checkID(int studID, data* stuData, int size){
	int count = 0;
	//Checks each student to see if input ID is equal to that student's ID
	while(count < size){
		if(studID == (*stuData).id){
			return TRUE;
		}
		count++;
		studID++;
	}
	return FALSE;
}

/* Function Purpose: Prints a histogram for the grades of the students in the group.
 * Input params: The struct pointer, stuData, that points to the student information, and int, size, the number of students in the group.
 * Return param: none
 **/
void print_histogram(data* student, int size){
	int count1 = 0, count2 = 0, count3 = 0;
	char currentGrade;
	int gradeFreq[LETTERS] = {0, 0, 0, 0, 0};
	char letterGrades[LETTERS] = {'A', 'B', 'C', 'D', 'F'};
	//Goes through each location in frequency array
	while(count1 < size){
		//Temp saves current student's grade
		currentGrade = (*student).grade;
		//Depending on the current student's grade, adds one to its respective location the in the frequency array
		switch(currentGrade){
			case 'A':
				gradeFreq[0]++;
				break;
			case 'B':
				gradeFreq[1]++;
				//printf("gradeFreq: %d\n", gradeFreq[count2]);
				break;
			case 'C':
				gradeFreq[2]++;
				break;
			case 'D':
				gradeFreq[3]++;
				break;
			case 'F':
				gradeFreq[4]++;
				break;
			default:
				printf("Incorrect Grade letter, check print_histogram");
				break;
		}
		count1++;
		student++;
	}
	//Resets student pointer to first position
	student-=count1;
	//Goes through each of the letter grades
	while(count2 < LETTERS){
		//Prints the current letter grade
		printf("%c: ", letterGrades[count2]);
		//Prints n *'s, where n is the number of times the current grade was found, using the gradeFreq[] array
		while(count3 < gradeFreq[count2]){
			printf("*");
			count3++;
		}
		count2++;
		count3 = 0;
		printf("\n");
	}
}
		
			
	
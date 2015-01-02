/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 1
 */
 
  //Preprocess commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 //Global definitions
 #define MAX_LINE 100
 #define NUM_DIGITS 5
 
 //Class_Standing enum definition
 typedef enum{
	FRESHMAN = 1,
	SOPHOMORE = 2,
	JUNIOR = 3,
	SENIOR = 4
} Class_Standing;

//Function prototypes
 float minGPA(float *gpa, int length);
 float maxGPA(float *gpa, int length);
 float avgGPA(float *gpa, int length);
 float getGPA(int targetId, int* idArray, float* gpaArray, int length);
 void printClassStanding(int targetID, int* idArray, Class_Standing *classStandingArray, int length);
 void saveInBetterFormat(int* idArray, float* gpaArray, Class_Standing *classStandingArray, int length);
 
 /* Function Purpose: Checks that there is only one cmd line input. Makes sure file is found. Uses functions to find min, max and avg gpa, prints them.
 *                    Asks user to test both getGPA and printClassStanding functions.
 * Input params: number of arguments, and string array of arguments.
 * Return param: some integer
 **/
 int main(int argc, char **argv){
	FILE *fptr;
	int length, i = 0, searchId;
	float foundGPA;
	//Checks to make sure command line contains only one other argument (file name)
	if(argc != 2){
		printf("Only one command line argument allowed, terminating. \n\n");
		return 1;
	}
	
	fptr = fopen(argv[1], "r");
	//Checks to make sure file was found
	if(fptr == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	//Scans in first number of file (# of students), creates arrays of IDs, GPAs, and Class_Standings based on that #
	fscanf(fptr,"%d",&length);
	int idArray[length];
	float gpaArray[length];
	Class_Standing standArray[length];
	//Scans and stores ID, GPA, and Class_Standings from file in corresponding arrays.
	while(i<length){
		fscanf(fptr,"%d%f%d",&idArray[i],&gpaArray[i],&standArray[i]);
		//printf("%d  %f  %d", idArray[i],gpaArray[i],standArray[i]);
		i++;
	}
	
	fclose(fptr);
	
	printf("Average GPA is %f\nMax GPA is %f\nMin GPA is %f\n",avgGPA(gpaArray,length),maxGPA(gpaArray,length),minGPA(gpaArray,length));
	printf("To test getGPA, please enter a student's id: ");
	scanf("%d",&searchId);
	foundGPA = getGPA(searchId, idArray, gpaArray, length);
	//If a GPA is found, prints it
	if( foundGPA != -1){
		printf("GPA is %f\n",foundGPA);
	}
	//Otherwise, prints error statement
	else{
		printf("ID not found.\n");
	}
	//Calls for input ID, uses printClassStanding function to print the corresponding class of student
	printf("To test printClassStanding, please enter a student's id: ");
	scanf("%d",&searchId);
	printClassStanding(searchId, idArray, standArray, length);
	
	//calls saveInBetterFormat function
	saveInBetterFormat(idArray, gpaArray, standArray, length);
}
	

  /* Function Purpose: Calculates and returns minimum GPA from file.
 * Input params: Pointer to GPA (float), number of GPAs to store.
 * Return param: Minimum GPA (float)
 **/
 float minGPA(float *gpa, int length){
	int i=0;
	float currMin = 5;
	//Searches through all GPA and saves minimum
	while(i<length){
		if(*gpa < currMin){
			currMin = *gpa;
		}
		gpa++;
		i++;
	}
	return currMin;
}

 /* Function Purpose: Calculates and returns maximum GPA from file.
 * Input params: Pointer to GPA (float), number of GPAs to store.
 * Return param: Maximum GPA (float)
 **/
 float maxGPA(float *gpa, int length){
	int i=0;
	float currMax = 0;
	//Searches through all GPA and saves maximum
	while(i<length){
		if(*gpa > currMax){
			currMax = *gpa;
		}
		gpa++;
		i++;
	}
	return currMax;
}

 /* Function Purpose: Calculates and returns average GPA from file.
 * Input params: Pointer to GPA (float), number of GPAs to store.
 * Return param: Average GPA (float)
 **/
 float avgGPA(float *gpa, int length){
	int i=0;
	float total = 0;
	//Searches through all GPA, adds to total
	while(i<length){
		total += *gpa;
		gpa++;
		i++;
	}
	//returns average
	return (total/((float)length));
}

 /* Function Purpose: Finds GPA based on input ID.
 * Input params: Id to search for, pointer of id's, pointer of gpa's and number of students to serach.
 * Return param: GPA corresponding to input ID or -1 if nothing is found.
 **/
float getGPA(int targetId, int *idArray, float* gpaArray, int length){
	int i = 0;
	//Searches through all ID's and returns corresponding GPa if found
	while(i<length){
		if(targetId == *idArray){
			return *gpaArray;
		}
		i++;
		idArray++;
		gpaArray++;
	}
	//If all Id's are searched and no matches are found, returns -1
	return -1;
}
 /* Function Purpose: Prints the class standing of input ID
 * Input params: ID to search for, pointer of id's, pointer of class standings, number of students to search.
 * Return param: void
 **/
void printClassStanding(int targetId, int* idArray, Class_Standing *classStandingArray, int length){
	int i = 0;
	int found = 0;
	//Checks each ID for one matching to input search value
	while(i<length){
		if(targetId == *idArray){
			//Once target ID is found, checks corresponding class standing and prints based on value
			switch(*classStandingArray){
				case FRESHMAN:
					printf("Class standing is FRESHMAN\n");
					break;
				case SOPHOMORE:
					printf("Class standing is SOPHOMORE\n");
					break;
				case JUNIOR:
					printf("Class standing is JUNIOR\n");
					break;
				case SENIOR:
					printf("Class standing is SENIOR\n");
					break;
				default:
					printf("Error, class standing not found\n");
					break;
			}
			found = 1;
		}
		i++;
		idArray++;
		classStandingArray++;
	}
	//If no matching ID is found, prints error statement
	if(found == 0){
		printf("id not found\n");
	}
}

 /* Function Purpose: Saves information to new file that includes word for class standing instead of numbers
 * Input params: ID array, gpa Array, class standing array and number of students
 * Return param: void
 **/
void saveInBetterFormat(int* idArray, float* gpaArray, Class_Standing *classStandingArray, int length){
	//Creates new file pointer and opens "output.txt" to write to
	FILE *fptr2;
	fptr2 = fopen("output.txt", "w");
	fprintf(fptr2,"%d\n",length);
	int i = 0;
	//Goes through the input number of students and prints their information, line by line
	while(i<length){
		//prints ID and GPA
		fprintf(fptr2,"%d %f ",*idArray, *gpaArray);
		//prints class standing, dependent upon value of current element in classStandingArray
		switch(*classStandingArray){
			case FRESHMAN:
				fprintf(fptr2,"FRESHMAN\n");
				break;
			case SOPHOMORE:
				fprintf(fptr2,"SOPHOMORE\n");
				break;
			case JUNIOR:
				fprintf(fptr2,"JUNIOR\n");
				break;
			case SENIOR:
				fprintf(fptr2,"SENIOR\n");
				break;
			default:
				fprintf(fptr2,"Error, class standing not found\n");
				break;
		}
		i++;
		idArray++;
		gpaArray++;
		classStandingArray++;
	}
	fclose(fptr2);
}
 
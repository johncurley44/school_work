/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: Vomitory
 */
 
 //Preprocess commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define COUNTFILENAME "numberOfPresidents.txt"
 #define NAMESIZE 50
 #define OUTPUTFILENAME "output.txt"
 #define PARTYPRINT "There were %d members of the %s party.\n"
 #define PARTYSFILENAME "parties.txt"
 #define PRESIDENTSFILENAME "presidents.txt"
 #define VICEPRESIDENTSFILENAME "vicePresidents.txt"
 #define PARTIES 6
 //Structure definition for president information
 typedef struct presidents
	{
	char firstName[NAMESIZE];
	char lastName[NAMESIZE];
	int number;
	char party[NAMESIZE];
	char vicePresidentFirstName[NAMESIZE];
	char vicePresidentLastName[NAMESIZE];
	}PRESIDENTS;
 enum partyTypes
	{
	NOPARTY,
	FEDERALIST,
	DEMOCRATICREPUBLICAN,
	WHIG,
	DEMOCRATIC,
	REPUBLICAN,
	NUMBEROFPARTIES
	};
 //Function prototypes
 int getNumberOfPresidents(char fileName[]);
 void fillPresidentVectorWithPresidents(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents);
 void fillPresidentVectorWithVicePresidents(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents);
 void prettyPrintPartiesToFile(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents);
 void prettyPrintPresidents( PRESIDENTS presidentVector[], int numberOfPresidents );
 void prettyPrintPresidentVectorToFile( char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents );
 /* Function Purpose: Calls all functions
 * Input params: argument information
 * Return param: some int
 **/
 int main(int argc, char** argv){
	//gets number of presidents for the other functions
	int i, numberOfPresidents = getNumberOfPresidents(COUNTFILENAME);
	//declares presidentVector used in every function
	PRESIDENTS presidentVector[numberOfPresidents];
	//calls all functions
	fillPresidentVectorWithPresidents(PRESIDENTSFILENAME,presidentVector,numberOfPresidents);
	fillPresidentVectorWithVicePresidents(VICEPRESIDENTSFILENAME,presidentVector,numberOfPresidents);
	prettyPrintPartiesToFile( PARTYSFILENAME, presidentVector, numberOfPresidents );
	prettyPrintPresidents( presidentVector, numberOfPresidents );
	prettyPrintPresidentVectorToFile( OUTPUTFILENAME, presidentVector, numberOfPresidents );	
	return 0;
}
/* Function Purpose: Retrieves number of presidents from "numberOfPresidents.txt"
 * Input params: a file containing the number of presidents
 * Return param: integer equal to the number of presidents
 **/
int getNumberOfPresidents(char fileName[]){
	FILE *fptr;
	int presNum;
	fptr = fopen(fileName,"r");
	fscanf(fptr, "%d", &presNum);
	fclose(fptr);
	return presNum;
}
/* Function Purpose: Fills the president vector with each president's number, name, and party
 * Input params: file to read from, president vector, number of presidents
 * Return param: void
 **/
void fillPresidentVectorWithPresidents(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents){
	int i, presNum;
	FILE *fptr;
	fptr = fopen(fileName, "r");
	char presFirstName[NAMESIZE], presLastName[NAMESIZE], presParty[NAMESIZE];
	//Reads in each president's number, first name, last name, and party he belonged to
	for(i=0;i<numberOfPresidents;i++){
		fscanf(fptr,"%d%s%s%s", &presidentVector[i].number, presidentVector[i].firstName, presidentVector[i].lastName, presidentVector[i].party);
	}
	fclose(fptr);
}
/* Function Purpose: Fills the president vector with each vice president's name
 * Input params: file to read from, president vector, number of presidents
 * Return param: void
 **/
void fillPresidentVectorWithVicePresidents(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents){
	int i;
	FILE *fptr;
	fptr = fopen(fileName, "r");
	char firstName[NAMESIZE], lastName[NAMESIZE];
	//Reads in each vice president's first name and last name
	for(i=0;i<numberOfPresidents;i++){
		fscanf(fptr,"%s%s", presidentVector[i].vicePresidentFirstName, presidentVector[i].vicePresidentLastName);
	}
	fclose(fptr);
}
/* Function Purpose: Creates a file that contains the number of presidents from each party
 * Input params: file to print to, president vector, number of presidents
 * Return param: void
 **/
 void prettyPrintPartiesToFile(char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents){
	FILE *fptr;
	int freqVector[PARTIES], i, j, k, currentLoc;
	char *partyNames[PARTIES] = {"No_Party", "Federalist", "Democratic-Republican", "Whig", "Democratic", "Republican"};
	//Iterates through each president in presidentVector
	for(i=0;i<numberOfPresidents;i++){
		//series of if/else if statements: check to see which party the president belonged to, adds one to respective location in frequency array
		if(strcmp(partyNames[0],presidentVector[i].party)==0){
			freqVector[0]++;
		}
		else if(strcmp(partyNames[1],presidentVector[i].party)==0){
			freqVector[1]++;
		}
		else if(strcmp(partyNames[2],presidentVector[i].party)==0){
			freqVector[2]++;
		}
		else if(strcmp(partyNames[3],presidentVector[i].party)==0){
			freqVector[3]++;
		}
		else if(strcmp(partyNames[4],presidentVector[i].party)==0){
			freqVector[4]++;
		}
		else if(strcmp(partyNames[5],presidentVector[i].party)==0){
			freqVector[5]++;
		}
		else{
			printf("\n\nerror in prettyPrintPartiesToFile\n\n");
		}
	}
		

	
	fptr = fopen(fileName, "w");
	//Goes through each possible party, prints the number of members in that party
	for(j=0;j<PARTIES;j++){
		fprintf(fptr,"There were %d members of the %s party.\n", freqVector[j], partyNames[j]);
	}
	fclose(fptr);
 }
 /* Function Purpose: Prints all the presidents' info as output
 * Input params: president vector, number of presidents
 * Return param: void
 **/
 void prettyPrintPresidents( PRESIDENTS presidentVector[], int numberOfPresidents ){
	int i;
	//Iterates through each president in vector, prints their number, name, and party
	for(i=0;i<numberOfPresidents;i++){
		printf("%-2d: %-11s%-15swas a member of the %-22sparty\n", presidentVector[i].number, presidentVector[i].firstName, presidentVector[i].lastName, presidentVector[i].party);
	}
}
/* Function Purpose: Prints all the presidents' and vice presidents' to a file
 * Input params: file to print to, president vector, number of presidents
 * Return param: void
 **/
void prettyPrintPresidentVectorToFile( char fileName[], PRESIDENTS presidentVector[], int numberOfPresidents ){
	int i;
	FILE *fptr;
	fptr = fopen(fileName,"w");
	//Iterates through each president in vector, prints their number, name and vice president name
	for(i=0;i<numberOfPresidents;i++){
		fprintf(fptr,"\n%-3dPresident:      %-15s%s\n   Vice President: %-15s%s\n", presidentVector[i].number, presidentVector[i].firstName, presidentVector[i].lastName, presidentVector[i].vicePresidentFirstName, presidentVector[i].vicePresidentLastName);
	}	
	fclose(fptr);
 }
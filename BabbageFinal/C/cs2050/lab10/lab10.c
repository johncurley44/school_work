/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* Lab 10
*/
//Preprocess commands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Definitions of constants
#define MAX_LINE 250
#define MAX_WORD 30
//Function prototypes
int looksLikePhoneNumber(const char* word);
int looksLikeCourse(const char* word);
int looksLikeDate(const char* word);
int looksLikeName(const char* word);
int isValidDate(const char* word);
/* Function Purpose: Reads a file, parses the lines into words, then evaluates each word to see if it matches a pattern of interest
 * Input params: argc - number of variables read from command line, argv - holds strings of command line inputs
 * Return param: some int
 **/
int main(int argc, char** argv){
	FILE* fPtr;
	char *tempStr = malloc(MAX_LINE*sizeof(char));
	char *wordToCheck = malloc(MAX_WORD*sizeof(char));
	char *prevWord = malloc(MAX_WORD*sizeof(char));
	int lastName = 0;
	int numWords = 0;
	//Checks to make sure command line contains only one other argument
	if(argc != 2){
		printf("One and only one command line arguments are allowed, terminating. \n\n");
		return 1;
	}
	//Opens files
	fPtr = fopen(argv[1], "r");
	//Checks to make sure files were found
	if(fPtr == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	//Reads from file, line by line
	while(fgets(tempStr, MAX_LINE, fPtr)){
		//strips newline characters from the end of lines read in
		if(*(tempStr+(strlen(tempStr)-1)) == '\n'){
			*(tempStr+(strlen(tempStr)-1)) = '\0';
		}
		//Takes first word from line
		wordToCheck = strtok(tempStr, " ");
		//While there is still a word to look at on a line
		while(wordToCheck != NULL){
			//If the word is a phone number
			if(looksLikePhoneNumber(wordToCheck)==1){
				printf("Found a phone number: %s\n", wordToCheck);
			}
			//If the word is a course
			else if(looksLikeCourse(wordToCheck)==1){
				printf("Found a course: %s\n", wordToCheck);
			}
			//If the word is a date
			else if(looksLikeDate(wordToCheck)==1){
				printf("Found a date: %s\n", wordToCheck);
				if(isValidDate(wordToCheck) == 1){
					printf("The date is valid\n");
				}
				else{
					printf("The date is not valid\n");
				}
			}
			else{
				//If the word is a Name
				if(looksLikeName(wordToCheck)==1){
					lastName++;
					if(lastName==2){
						printf("Name found: %s %s\n", prevWord, wordToCheck);
						lastName = 0;
					}
					else{
						strcpy(prevWord, wordToCheck);
					}
				}
				else{
					lastName = 0;
				}
			}
			//Changes wordToCheck to the next word in the line
			wordToCheck = strtok(NULL, " ");
			//Increments the counter of words
			numWords++;
		}
	}
	printf("There were %d words in the file.\n", numWords);
	fclose(fPtr);
	free(tempStr);
	free(wordToCheck);
	free(prevWord);
	return 0;
}
/* Function Purpose: Determines whether the word provided looks like a phone number
 * Input params: word to inspect
 * Return param: int - 1 if looks like a phone number, 0 if not
 **/
int looksLikePhoneNumber(const char* word){
	int length = strlen(word);
	int i;
	//Returns 0 if the word isn't 14 characters long
	if(length != 14){
		return 0;
	}
	//Inspects each character of word
	for(i=0; i<length; i++){
		//Checks if the first character is an open paren.
		if(i==0){
			if(*(word+i) != '('){
				return 0;
			}
		}
		//Checks if the 5th character is a close paren.
		else if(i==4){
			if(*(word+i) != ')'){
				return 0;
			}
		}
		//Checks if the 6th and 10th character are dashes
		else if(i==5 || i==9){
			if(*(word+i) != '-'){
				return 0;
			}
		}
		//Checks to make sure every other character is a number
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	//returns 1 if all characters are of phone number form
	return 1;
}
/* Function Purpose: Determines whether the word provided is a course
 * Input params: word to inspect
 * Return param: int - 1 if looks like a course, 0 if not
 **/
int looksLikeCourse(const char* word){
	int length = strlen(word);
	int i;
	//If the word is not 6 characters long, not a course
	if(length != 6){
		return 0;
	}
	//Inspects every element of course
	for(i=0; i<length; i++){
		//Checks to see if first 2 characters are letters
		if(i<2){
			if(isalpha(*(word+i))==0){
				return 0;
			}
		}
		//Checks to see if the other characters are numbers
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	//returns 1 if all characters are in course form
	return 1;
}
/* Function Purpose: Determines if provided word is a date 'XX-XX-XXXX'
 * Input params: word to inspect
 * Return param: int - 1 if looks like a date, 0 if not
 **/
int looksLikeDate(const char* word){
	int length = strlen(word);
	int i;
	//If the word is not 10 characters long, not a date
	if(length != 10){
		return 0;
	}
	//Inspects each character
	for(i=0; i<length; i++){
		//Checks to see if the 3rd and 6th characters are dashes
		if(i==2 || i==5){
			if(*(word+i)!='-'){
				return 0;
			}
		}
		//Checks if other characters are numbers
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	//returns 1 if all characters are in date form
	return 1;
}
/* Function Purpose: Determines whether the word provided looks like a name
 * Input params: word to inspect
 * Return param: int - 1 if Name, 0 if not
 **/
int looksLikeName(const char* word){
	int i = 0;
	int length = strlen(word);
	//If the first letter is not uppercase, not a name
	if(isupper(*(word+i)) == 0){
		return 0;
	}
	//If any of the other letters in the name not lower case besides the first, not name
	for(i=1; i<length; i++){
		if(islower(*(word+i)) == 0){
			return 0;
		}
	}
	//Returns 1 if all characters in name form
	return 1;
}
/* Function Purpose: Checks to see if a date is valid
 * Input params: A word in date form
 * Return param: int - 1 if valid date, 0 if not
 **/
int isValidDate(const char* word){
	//validDays[0] represents January, which is 01 in a date string
	int validDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char* tempWord = malloc(MAX_WORD*sizeof(char));
	strcpy(tempWord, word);
	int month = atoi(strtok(tempWord,"-"));
	int day = atoi(strtok(NULL,"-"));
	//If the month value is not 1-12, not a valid date
	if(month>0 && month<13){
		//If the day is not at least 1 or more than the respective month's last day, not a valid date
		if(day<=validDays[month-1] && day>0){
			return 1;
		}
	}
	else{
		return 0;
	}
	free(tempWord);
}
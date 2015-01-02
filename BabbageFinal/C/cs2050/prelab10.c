/*
* Name: John Curley	
* Lab section: B
* TA: Zhi Zhou / Seth Wiessman
* prelab10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 100

int looksLikePhoneNumber(const char* word);
int looksLikeCourse(const char* word);
int looksLikeDate(const char* word);

int main(int argc, char** argv){
	FILE* fPtr;
	char *tempStr = malloc(MAX_LINE*sizeof(char));
	char *wordToCheck = malloc(MAX_LINE*sizeof(char));
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
	
	while(fgets(tempStr, MAX_LINE, fPtr)){
		wordToCheck = strtok(tempStr, " ");
		while(wordToCheck != NULL){
			
		
			//printf("%s ", tempStr);
			if(looksLikePhoneNumber(wordToCheck)==1){
				printf("Found a phone number: %s\n", wordToCheck);
			}
			else if(looksLikeCourse(wordToCheck)==1){
				printf("Found a course: %s\n", wordToCheck);
			}
			else if(looksLikeDate(wordToCheck)==1){
				printf("Found a date: %s\n", wordToCheck);
			}
			wordToCheck = strtok(NULL, " ");
		}
	}
}

int looksLikePhoneNumber(const char* word){
	if(!word){
		printf("WHOOPS\n");
	}
	int length = strlen(word);
	int i;
	//printf("phone length: %d\n", length);
	if(length != 14){
		return 0;
	}
	
	for(i=0; i<length; i++){
		if(i==0 || i==4 || i==5 || i==9){
			if(ispunct(*(word+i))==0){
				return 0;
			}
		}
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	
	return 1;
}

int looksLikeCourse(const char* word){
	int length = strlen(word);
	int i;
	
	if(length != 6){
		return 0;
	}
	
	for(i=0; i<length; i++){
		if(i<2){
			if(isalpha(*(word+i))==0){
				return 0;
			}
		}
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	return 1;
}

int looksLikeDate(const char* word){
	int length = strlen(word);
	int i;
	
	if(length != 10){
		return 0;
	}
	
	for(i=0; i<length; i++){
		if(i==2 || i==5){
			if(ispunct(*(word+i))==0){
				return 0;
			}
		}
		else{
			if(isdigit(*(word+i))==0){
				return 0;
			}
		}
	}
	return 1;
}
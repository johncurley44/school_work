
#include <stdlib.h>
#include <stdio.h>

void allocate(char **string, int size);
int length(char* string);
void copy(char* source, char* target);

int main(void){

char array[10] = {'a', 'b', 'd', 'y', 'u', 'i', 'p', 'o', '\0'};
printf("enter a string under 9 characters");
scanf("%s", array);
int len = length(array);
char array2[10];
allocate(*array2, len);
copy(array, array2);

printf("array: %s\narray2: %s\n\n", array, array2);
printf("arrayLoc: %p\narray2Loc: %p\n\n", array, array2);

}

/* Function Purpose: Calculates the length of a string using pointer math
 * Input params: String you want the length of
 * Return param: Length of string
 **/
 int length(char* string){
	char *temp = string;
	int count = 0;
	// While loop that goes through each string character and adds one to a length value (count) to determine length. Stops on null terminator.
	while (*temp != '\0'){
		
		temp++;
		count++;
	}
	return count;
}

/* Function Purpose: Takes a source pointer string and copies each element into a new string using pointer math
 * Input params: String to be copied
 * Return param: Void
 **/
void copy(char* source, char* target){
	char* start = source;
	char* temp = target;
	// While loop that uses pointer math to copy each character of string into a new string, and prints that new string one character at a time.
	while(*start != '\0'){
		*temp = *start;
		printf("%c", *temp);
		temp++;
		start++;
	}
	// Places the null terminator at the end of new, copied string.
	*temp = '\0';
	printf("\n");
}


void allocate(char** string, int size){

	string = (char**)malloc(sizeof(char)*size+1);

}


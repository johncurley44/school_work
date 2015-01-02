/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: Flabbergasted
 */
 
 //Preprocess commands
 #include <stdio.h>
 #include <stdlib.h>
 
 //Function Prototypes
 int length(char *string);
 void copy(char* source, char* target);
 void reverse(char* source, char* target);
 int compare(char* string1, char* string2);
 
 int LEN = 0;
 
 int main(void){
	char input[20];
	//while(LEN >= 0) "exit"){ //compares addresses, will not work
		printf("Enter a string: ");
		scanf("%s", &input);
		
		printf(" String Copy: ");
		char *sCopy = (char*)malloc(sizeof(char)*(length(input) + 1));
		
		copy(input, sCopy);
		free(sCopy);
		
		printf(" Reverse String: ");
		char *sReverse = (char*)malloc(sizeof(char)*(length(input) + 1));
		reverse(input, sReverse);
		
		if(compare(input, sReverse) == 1){
			printf("\"%s\" is a palindrome string.", input);
		}
		
		else{
			printf("\"%s\" is not a palindrome string.", input);
		}
		free(sReverse);
		printf("\n");
	//}
		
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

/* Function Purpose: Takes a pointer string and creates a new one that is the reverse of the original
 * Input params: Original pointer string and pointer to where new string is to be placed
 * Return param: Void
 **/
void reverse(char* source, char* target){
	LEN = length(source);
	char* end = source + LEN - 1;
	char* temp = target;
	while(LEN >= 0){
		printf("%c", *end);
		*temp = *end;
		end--;
		temp++;
		LEN--;
	}
	*temp = '\0';
	printf("\n");
}

/* Function Purpose: Compares two pointer strings, element by element, to determine if they are identical, returns 1 or 0 for same or different, respectively
 * Input params: 2 pointer strings that are to be compared
 * Return param: 1 or 0, 1 if strings are identical, 0 if they are not
 **/
int compare(char* string1, char* string2){
	char* temp1 = string1;
	char* temp2 = string2;
	int count = 0;
	LEN = length(string1);
	//While loop that goes through each element of a 2 strings of equal length and compares to make sure each is equal. 
	//If strings are the same, while loop terminates, if one character is different, 0 is immediately returned.
	while(LEN >=0){					//CURRENTLY INCLUDES NULL TERMINATOR, CORRECT????????????????
		if(*(temp1 + count) != *(temp2 + count)){
			return 0;
		}
		LEN--;
		count++;
	}
	return 1;
}


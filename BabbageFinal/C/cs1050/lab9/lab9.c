/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: My name is Matthew England
 */
 
//Preprocess commands
 #include <stdio.h>
 #include <stdlib.h>
 #define MAX 20
 #define ARRAYSIZE 5
 #define NAMES 3

//Function Prototypes
 int length(char *string);
 void copy(char* source, char* target);
 int compare(char* string1, char* string2);
 void allocate(char** string, int size);
 void search(char* stringArray[MAX], char* searchName);
 void prefixSearch(char* stringArray[MAX], char* searchPrefix);
 
 /* Function Purpose: Gathers 5 names from user, asks for 3 full names and 3 prefixes to search and print results of search
 * Input params: none
 * Return param: main (0)
 **/
 int main(void){
	//variable declaration
	 char* nameArray[ARRAYSIZE];
	 char buffer[MAX];
	 int i = 0, j = 0, k = 0, l = 0;
	 int bLen = 0;
	 char tempSearch[MAX];
	 //Asks for 5 names, allocates space for each, and copies each into a location of string array
	 for(i = 0; i<ARRAYSIZE; i++){
		printf("Enter a name: ");
		scanf("%s", buffer);
		bLen = length(buffer);
		allocate(&(nameArray[i]), bLen+1);
		copy(buffer,(nameArray[i]));
	 }  
	 //Asks for 3 names to search for and uses search function to do so
	 for(j = 0; j<NAMES; j++){
		printf("\nSearch for name %d: ", j+1);
		scanf("%s", tempSearch);
		search(nameArray, tempSearch);
	 }
	 //Asks for 3 prefixes to search for and uses prefixSearch to do so
	 for(k = 0; k<NAMES; k++){
		printf("\nSearch for prefix %d: ", k+1);
		scanf("%s", tempSearch);
		prefixSearch(nameArray, tempSearch);
	 }
	 printf("\nProgram Terminated.\n\n");
	 //Frees memory for each location of string array
	 for(l = 0; l<ARRAYSIZE; l++){
		free(nameArray[l]);
	 }
	 return 0;
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
		temp++;
		start++;
	}
	// Places the null terminator at the end of new, copied string.
	*temp = '\0';
	//printf("\n");
}

/* Function Purpose: Compares two pointer strings, element by element, to determine if they are identical, returns 1 or 0 for same or different, respectively
 * Input params: 2 pointer strings that are to be compared
 * Return param: 1 or 0, 1 if strings are identical, 0 if they are not
 **/
int compare(char* string1, char* string2){
	char* temp1 = string1;
	char* temp2 = string2;
	int count = 0;
	int len = length(string1);
	//While loop that goes through each element of a 2 strings of equal length and compares to make sure each is equal. 
	//If strings are the same, while loop terminates, if one character is different, 0 is immediately returned.
	while(len >=0){					//CURRENTLY INCLUDES NULL TERMINATOR, CORRECT????????????????
		if(*(temp1 + count) != *(temp2 + count)){
			return 0;
		}
		len--;
		count++;
	}
	return 1;
}
/* Function Purpose: Allocates memory for a string using a pointer of strings
 * Input params: Pointer of strings and size of that pointer
 * Return param: void
 **/
void allocate(char** string, int size){
	// Allocates enough memory for the number of characters in input string
	*string = (char*)malloc(sizeof(char)*size);

}
/* Function Purpose: Searches through array of strings for input string, prints result of search
 * Input params: Array of strings and string to search for
 * Return param: void
 **/
void search(char* stringArray[MAX], char* searchName){
	int len = ARRAYSIZE;
	int count1, found = 0;
	//Iterates through string array
	for(count1 = 0; count1<len; count1++){
		//Uses compare function to determine is current string being looked at in string array
		// is equivilant to input search string
		if(compare(searchName, stringArray[count1]) == 1){
			printf("The name %s was found at index %d\n", stringArray[count1], count1);
			found = 1;
		}
	}
	//If the search name was never found, prints accordingly
	if(found != 1){
		printf("The name %s was not found in the array.\n", searchName);
	}
}
/* Function Purpose: Searches through array of strings for a specified prefix, prints results
 * Input params: Array of strings to search through, prefix you are searching for
 * Return param: void
 **/
void prefixSearch(char* stringArray[MAX], char* searchPrefix){
	int len = ARRAYSIZE;
	int lens = length(searchPrefix);
	int count1, count2, notHere = 0, found = 0;
	//Iterates through each string in string array
	for(count1 = 0; count1<len; count1++){
		//Iterates through each character in searchPrefix
		for(count2 = 0; count2<lens; count2++){
			//If characters in respective locations of searchPrefix and current string
			// from string array do not match, sets notHere = 1
			if(*(stringArray[count1]+count2) != *(searchPrefix + count2)){
				notHere = 1;
			}
		}
		//Prints that the prefix was found at current location, found=1 indicates 
		// that the prefix was found in at least one location
		if(notHere == 0){
			printf("Prefix %s was found at index %d\n", searchPrefix, count1);
			found = 1;
		}
		//Resets notHere
		notHere = 0;
	}
	//Prints statement that prefix wasn't found
	if(found == 0){
		printf("Prefix %s was not found in the array\n", searchPrefix);
	}
}
		
		
	

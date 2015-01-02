/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 2
 */
 
  //Preprocess commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 //Global Definitions
 #define SIZE 100
 #define MAX_ASCII 122
 #define MIN_ASCII 97
 
 //Function Prototypes
 char **allocate_Array(int num_sentences);
 void fill_Array(FILE *fp, char **X, int num_sentences);
 void print_Array(char **X, int num_sentences);
 void shift(char **X, int shift_length, int num_sentences);
/* Function Purpose: Tests all functions included in program. Also shifts letters from a 2-d array of sentences to letters
						further down in the alphabet
 * Input params: number of arguments, string array of arguments
 * Return param: some integer
 **/
 int main(int argc, char **argv){
	FILE *fptr;
	int num_sentences;
	int shift_length;
	char* num;
	num = malloc(4*sizeof(char));
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
	//1. Read in the first line of the data file to determine the possible number sentences
	fgets(num,SIZE,fptr);
	num_sentences = atoi(num);
	//2. Declare an array of char pointers for the sentences
	char **sentence_Array;
	//3. Call allocate_Array where length is obtained from 1.
	sentence_Array = allocate_Array(num_sentences);
	//4. Call fill_Array to fill our array with the sentences from the text file
	fill_Array(fptr, sentence_Array, num_sentences);
	//5. Call print_Array to print our array as well as make sure the values were stored from fill_Array
	print_Array(sentence_Array, num_sentences);
	//6. Prompt user for a shift length to shift characters. Then call shift and shift the chars by the shift_length
	printf("\nShifted by ");
	scanf("%d", &shift_length);
	printf("\n");
	shift(sentence_Array, shift_length, num_sentences);
	//7. Finally, call print_Array to make sure the characters were shifted, as well as stored.
	print_Array(sentence_Array, num_sentences);
 }
/* Function Purpose: Uses malloc to allocate a 2d array of pointers and SIZE = 100 characters for each of those pointers
 * Input params: number of pointers = number of sentences in 2-d array
 * Return param: double pointer with allocated memory
 **/
 char **allocate_Array(int num_sentences){
	char **sent_ptr = malloc(num_sentences*sizeof(char*));
	int i;
	//allocates 100 characters for each sentence required
	for(i=0;i<num_sentences;i++){
		*(sent_ptr+i) = malloc(SIZE*sizeof(char));
	}
	return sent_ptr;
 }
/* Function Purpose: Fills the array of sentences with sentences from file
 * Input params: some file to read from, the double pointer for saving the sentences from the file, and number of sentences in the 2d array
 * Return param: none
 **/
 void fill_Array(FILE *fp, char **X, int num_sentences){
	int i;
	//saves sentences from file into each pointer
	for(i=0;i<num_sentences;i++){
		fgets(*(X+i),SIZE,fp);
	}

 }
/* Function Purpose: Prints the 2d array of sentences
 * Input params: 2d array of sentences and the number of sentences in that 2d array
 * Return param: none
 **/
 void print_Array(char **X, int num_sentences){
	int i=0, j=0;
	//cycles through each sentence
	for(i=0;i<num_sentences;i++){
		j=0;
		//prints each character in sentence until null character is found
		while(*(*(X+i)+j) != '\0'){
			printf("%c", *(*(X+i)+j));
			j++;
		}
	}
	printf("\n");
 }
/* Function Purpose: Shifts each character in sentence array by user-specified amount using ASCII table
 * Input params: 2d sentence array, number of letters to shift in alphabet, and number of sentences in array
 * Return param: none
 **/
 void shift(char **X, int shift_length, int num_sentences){
	int i=0, j=0;
	//cycles through each sentence in array
	for(i=0;i<num_sentences;i++){
		j=0;
		//cylces through each character in sentence until null character is found
		while(*(*(X+i)+j) != '\0'){
			//Makes it so character will only be shifted if it is a lower-case alphabet character
			if(*(*(X+i)+j) > 96 && *(*(X+i)+j) < 123){
				//shifts reguarly if the shift number doesn't force the character outside of the lower-case range of ASCII
				if((shift_length + *(*(X+i)+j)-1) < MAX_ASCII){
					(*(*(X+i)+j))+=shift_length;
				}
				//if the shift number shifts the character past z, loops back to a
				else{
					(*(*(X+i)+j))-=(MAX_ASCII-MIN_ASCII-shift_length+1);
				}
			}
			j++;
		}
	}
 }
 

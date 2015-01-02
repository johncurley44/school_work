/* John Curley
 * Prelab 7 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define MAX_WORD 15
 #define TRUE 1
 #define FALSE 0
 
typedef struct word{
	char *word_space;
	struct word *next;
}Word;

Word *push(Word *Head, char *words);
Word *pop(Word *Head);

int main(void){
	char* pushWord = malloc(sizeof(char)*MAX_WORD);
	Word *Head = NULL;
	Word *nextHead = NULL;
	int contLoop = TRUE;
	int x;
	while(contLoop == TRUE){
		printf("Would you like to push or pop from the stack? 1 for push, 0 for pop, any other number to quit.\n");
		scanf("%d", &x);
		if(x == 1){
			printf("What word would you like to add to the stack?\n");
			scanf("%s", pushWord);
			Head = push(Head, pushWord);
		}
		else if(x == 0){ 
			Head = pop(Head);
		}
		else{
			contLoop = FALSE;
		}
	}
	while(Head){
		nextHead = Head->next;
		free(Head->word_space);
		free(Head);
		Head = nextHead;
	}
		
}

Word *push(Word *Head, char *words){
	Word *newWord = malloc(sizeof(Word));
	newWord->word_space = malloc(sizeof(char)*MAX_WORD);
	strcpy(newWord->word_space, words);
	if(Head){
		newWord->next = Head;
	}
	else{
		newWord->next = NULL;
	}
	printf("%s was successfully added to the stack\n", newWord->word_space);
	return newWord;
}

Word *pop(Word *Head){
	Word *newHead = NULL;
	if(Head){
		if(Head->next){
			newHead = Head->next;
			free(Head->word_space);
			free(Head);
		}
		else{
			free(Head->word_space);
			free(Head);
		}
	}
	else{
		printf("There is nothing on the stack to remove.\n");
	}
	if(newHead){
		printf("New top of the stack is: %s\n", newHead->word_space);
	}
	else{
		printf("There are no more elements on the stack\n");
	}
	return newHead;
}
	
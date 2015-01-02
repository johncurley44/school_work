/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 7 - 3/19/2013
 * 
 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 //Global Constants
 #define TRUE 1
 #define FALSE 0
 #define MAX_WORD 20
 
 typedef struct word{
	char word[MAX_WORD];
	struct word *next;
 }Sentence;
//Function Prototypes
Sentence *link(Sentence *Main, char word[]);
Sentence *undo(Sentence *Main, Sentence **Redo);
Sentence *redo(Sentence *Redo, Sentence **Main);
Sentence *create_Sentence(char word[]);
void print_Sentence(Sentence *Main);
void clean_up(Sentence *Main, Sentence *Redo);
/* Function Purpose: Ask user how they want to modify sentence, modify it accordingly
 * Input params: argc and argv, arguments not used in this program
 * Return param: some int
 **/
int main(int argc, char **argv){
	int contLoop = TRUE;
	int option = 0;
	char newWord[MAX_WORD];
	Sentence *mainHead = NULL;
	Sentence *redoHead = NULL;
	
	while(contLoop == TRUE){
		printf("What would you like to do? 1 push, 2 undo, 3 redo, 4 print, 5 exit\n");
		scanf("%d", &option);
		switch(option){
			case 1: 
				scanf("%s", newWord);
				mainHead = link(mainHead, newWord);
				break;
			case 2: 
				mainHead = undo(mainHead, &redoHead);
				break;
			case 3:
				redoHead = redo(redoHead, &mainHead);
				break;
			case 4:
				print_Sentence(mainHead);
				break;
			case 5:
				clean_up(mainHead, redoHead);
				contLoop = FALSE;
				break;
			default: 
				printf("Please enter valid number\n");
				break;
			}
		}
		
		return 1;
		
}
/* Function Purpose: Given a word, call create_Sentence and put in the list
 * Input params: Main list, word to add
 * Return param: Head of main list
 **/
Sentence *link(Sentence *Main, char word[]){
	Sentence *newSent = create_Sentence(word);
	Sentence *saveHead = NULL;
	Sentence *savePrev = NULL;
	if(!Main){
		Main = newSent;
		Main->next = NULL;
		return Main;
	}
	else{
		saveHead = Main;
		while(Main){
			savePrev = Main;
			Main = Main->next;
		}
		Main = newSent;
		savePrev->next = Main;
		return saveHead;
	}
}
/* Function Purpose: Remove the word that was most recently added
 * Input params: Main sentence list, pointer to "redo" stack
 * Return param: Head of main sentence list
 **/
Sentence *undo(Sentence *Main, Sentence **Redo){
	Sentence *saveHead = NULL;
	Sentence *newRedo = NULL;
	Sentence *prevMain = NULL;
	if(!Main){
		printf("There is nothing to undo!\n\n");
		return Main;
	}
	else{
		saveHead = Main;
		while(Main->next){
			prevMain = Main;
			Main = Main->next;
		}
		//Saves end of main
		newRedo = Main;
		Main = NULL;
		//Sets the next pointer in the new top of Redo to the old head
		newRedo->next = *Redo;
		//Makes the new head of Redo the word just taken off of main
		*Redo = newRedo;
		//Removes link to last word that is being undone
		if(prevMain){
			prevMain->next = NULL;
			return saveHead;
		}
		else{
			return NULL;
		}
	}
}
/* Function Purpose: Redo last word that was removed
 * Input params: Redo stack and pointer to main list
 * Return param: pointer to head redo sentence
 **/
Sentence *redo(Sentence *Redo, Sentence **Main){
	Sentence *tempHeadRedo = NULL;
	Sentence *prevMain = NULL;
	Sentence *pMain = *Main;
	Sentence *saveHead = NULL;
	if(!Redo){
		printf("There is nothing on the redo stack!\n\n");
		return Redo;
	}
	else{
		if(pMain){
			saveHead = pMain;
			while(pMain){
				prevMain = pMain;
				pMain = pMain->next;
			}
			//Makes the new last word in sentence equal to head of redo stack
			pMain = Redo;
			//Points the previous last word to the new last word
			prevMain->next = pMain;
			Redo = Redo->next;
			//Sets the next value of the new last word equal to NULL
			pMain->next = NULL;
			//Resets Main head
			*Main = saveHead;
		}
		else{
			*Main = Redo;
			Redo = Redo->next;			
			(*Main)->next = NULL;
		}
		return Redo;
	}
}
/* Function Purpose: creates a new sentence from a word
 * Input params: word to create new Sentence from
 * Return param: the Sentence created
 **/
Sentence *create_Sentence(char word[]){
	Sentence *newSentence = malloc(sizeof(Sentence));
	strcpy(newSentence->word, word);
	newSentence->next = NULL;
	return newSentence;
}
/* Function Purpose: Prints sentence
 * Input params: main list
 * Return param: void
 **/
void print_Sentence(Sentence *Main){
	Sentence *p = Main;
	printf("\n");
	while(p){
		printf("%s ", p->word);
		p = p->next;
	}
	printf("\n\n");
}
/* Function Purpose: frees all malloc memory
 * Input params: main list and redo stack
 * Return param: void
 **/
void clean_up(Sentence *Main, Sentence *Redo){
	Sentence *tempMain = NULL;
	Sentence *tempRedo = NULL;
	while(Main){
		tempMain = Main;
		Main = Main->next;
		free(tempMain);
	}
	while(Redo){
		tempRedo = Redo;
		Redo = Redo->next;
		free(tempRedo);
	}
}
		
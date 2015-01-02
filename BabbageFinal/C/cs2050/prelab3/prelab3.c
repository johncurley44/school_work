/* John Curley
 * Prelab 3 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define SIZE 50
 
int createarray(int** arrayRef, FILE * fptr);
void sortarray(int* array, int size);
void printarray(int *array, int size); 

int main(int argc, char** argv){
	FILE *fptr;
	int** arrayRef;
	fptr = fopen(argv[1], "r");
	int size = createarray(arrayRef, fptr);
	//printf("something  %d\n", *(*arrayRef+1));
	sortarray(*arrayRef, size);
	printarray(*arrayRef, size);
	fclose(fptr);
	return 0;
}

int createarray(int** arrayRef, FILE* fptr){
	int tempSize = 0, endMarker = 0, count = 0, tempNum, i;
	int *tempPtr = malloc(SIZE*sizeof(int));
	while(endMarker != EOF){
		endMarker = fscanf(fptr, "%d", &tempNum);
		*tempPtr = tempNum;
		printf("TEST: %d\n", *tempPtr);
		tempSize++;
		tempPtr++;
		printf("%p", fptr);
	}
	//printf("tempSize: %d\n", tempSize);
	//free(tempPtr);
	*arrayRef = malloc(tempSize*sizeof(int));
	endMarker = 0;
	for(i=0;i<tempSize;i++){
		fscanf(fptr, "%d", &tempNum);
		printf("somethingsomething %d\n", tempNum);
		(*(*arrayRef+i))=tempNum;
	}
	return tempSize;
}

/*int createarray(int** arrayRef, FILE* fptr){
	*arrayRef = malloc(SIZE*sizeof(int));
	int i = 0, endMarker, tempNum, size = 0;
	while(endMarker != EOF){
		endMarker = fscanf(fptr, "%d", &tempNum);
		*(*arrayRef+size) = tempNum;
		size++;
	}
	return (size-1);
}
*/
void sortarray(int* array, int size){
	int i, j, temp;
	for(i=0;i<(size-1);i++){
		for(j=0;j<(size-i-1);j++){
			if(*(array+j) > *(array+j+1)){
				temp = *(array+j);
				//printf("TEMPAFDJAKFDJA: %d\n", temp);
				*(array+j) = *(array+j+1);
				*(array+j+1) = temp;
			}
			//printf("TEST: %d\n", *(array+j));
		}
	}
}

void printarray(int *array, int size){
	int i;
	for(i=0;i<size;i++){
		printf("%d\n",*(array+i));
	}
}
		
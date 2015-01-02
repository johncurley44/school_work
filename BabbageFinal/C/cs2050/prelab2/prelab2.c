/* John Curley
 * Prelab 2 */
 
 
  //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 void calculateSum(int a, int b, int *c);
 float findAverage(float *nums, int length);
 void searchForNum(int **data, int numRows, int numCols, int *resultRow, int *resultCol, int searchNum);

int main(void){
	int a = 4, b = 5, i, j, k= 0;
	int *c = malloc(3*sizeof(int));
	calculateSum(a,b,c);
	printf("Sum: %d\n", *c);
	
	float *nums = malloc(5*sizeof(float));
	for(i = 0; i<5; i++){
		*nums = i;
		nums++;
	}
	nums-=5;
	float avg = findAverage(nums, 5);
	printf("Average: %f\n", avg);
	
	int **data = malloc(5*sizeof(int*));
	int *resultRow = malloc(5*sizeof(int*));
	int *resultCol = malloc(5*sizeof(int*));
 
	for(i=0; i<5; i++){
		*(data+i)=malloc(5*sizeof(int));
	}
	
	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			*(*(data+i)+j) = k;
			k+=3;
		}
	}
			
	searchForNum(data, 5, 5, resultRow, resultCol, 33);
}

void calculateSum(int a, int b, int *c){
	*c = a + b;
}

float findAverage(float *nums, int length){
	int i = 0;
	float total = 0;
	do{
		total+=*nums;
		nums++;
		i++;
	}while(i<length);
	
	return (total/((float)length));
}

void searchForNum(int **data, int numRows, int numCols, int *resultRow, int *resultCol, int searchNum){
	int i, j, found = 0;
	for(i=0;i<numRows;i++){
		int *currRow = *(data+i);
		for(j=0;j<numCols;j++){
			if(*(currRow+j) == searchNum){
				*resultRow=i;
				*resultCol=j;
				found = 1;
				printf("Row: %d \n Col: %d\n", (*resultRow)+1, (*resultCol)+1);
			}
		}
		if(found==0){
			*resultRow=-1;
			*resultCol=-1;
		}
	}
}
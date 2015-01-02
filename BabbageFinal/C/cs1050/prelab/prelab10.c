 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <time.h>
 
 #define TRUE 1
 #define FALSE 0
 
 
typedef struct {
   int id;
   float gpa;
} data;


 void initialize(data student[], int size);
 void print(data student[], int size);
 int search_by_id(data student[], int target, int size);
 
 
 int main(void){
	int contLoop = TRUE;
	int idSearch, size, index;
	data student[10]; 
	srand(time(NULL));
	
	printf("Array Size: ");
	scanf("%d", &size);
	printf("----------------------------\nID   GPA\n");
	initialize(student, size);
	print(student, size);
	
	do{
		printf("\nPlease enter student ID: ");
		scanf("%d", &idSearch);
		index = search_by_id(student, idSearch, size);
		if(idSearch == 0){
			break;
		}
		else if(index != -1){
			printf("ID   GPA\n");
			printf("%-5d%.2lf\n", idSearch, student[index].gpa);
		}
		else{
			printf("Student ID %d not found\n", idSearch);
		}
	}while(contLoop == TRUE);
 }
 
 void initialize(data student[], int size){
	int count = 0;
	do{
		student[count].id = rand() % 900 + 100;
		student[count].gpa = (rand() % 401) * 0.01;
		count++;
	}while(count < size);
}

void print(data student[], int size){
	int count = 0;
	while(count < size){
		printf("%-5d%.2lf\n", student[count].id, student[count].gpa);
		count++;
	}
}

 int search_by_id(data student[], int target, int size){
	int count = 0;
	do{
		if(target == student[count].id){
			return count;
		}
		count++;
	}while(count < size);
	
	return -1;
}



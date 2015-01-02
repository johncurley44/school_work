#include <stdio.h>
#include <stdlib.h>

void initialize(int a[], int b[], int size);
void print(int a[], int b[], int size);
void redundancies(int a[], int b[], int size);
//void sort(int a[], int b[], int size);

int a[10] = {0,0,0,0,0,0,0,0,0,0};
int b[10] = {0,0,0,0,0,0,0,0,0,0};

int main(void){
	initialize(a,b,10);
	print(a,b,10);
	redundancies(a,b,10);
}

void initialize(int a[], int b[], int size){
	int count;
	for(count=0; count<size; count++){
		a[count] = rand() % 10;
		b[count] = rand() % 10;
	}
}

void print(int a[], int b[], int size){
	int count;
	printf("Array A: ");
	for(count=0; count<size; count++){
		printf("%d ",a[count]);
	}
	printf("\nArray B: ");
	for(count=0; count<size; count++){
		printf("%d ",b[count]);
	}
	printf("\n\n");
}

void redundancies(int a[], int b[], int size){
	int count1, count2;
	int common=0;
	printf("Common Values are: ");
	for(count1=0;count1<size;count1++){
		for(count2=count1;count2<size;count2++){
			if(a[count1]==b[count2]){
				printf("%d ",a[count1]);
			}
		}
	}
}
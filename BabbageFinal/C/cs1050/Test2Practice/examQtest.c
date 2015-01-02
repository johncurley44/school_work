#include <stdio.h>

int main(void){
	int number = 0;
	int *aPtr = &number;
	printf("\naPtr: %p", aPtr);
	printf("\n&aPtr: %p", &aPtr);
	printf("\n&number: %p\n", &number);
}
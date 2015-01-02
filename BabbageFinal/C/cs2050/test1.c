#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
	printf("\n%d\n", calculate());
	return;
}


int calculate(){
	int sum = 0;
	int result = 0;
	int i;
	for(i=0;i<50;i++){
		sum+=i;
	}
	result = sum;
	return result;
}
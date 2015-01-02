/* John Curley - jmcgdd
 * Lab Section: B
 * Prelab 9 - 4/15/2013
 * 
 */
 
 //Preprocess Commands
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 #define ARRAY_SIZE 30
 #define MAX_LINE 50
 //Function Prototypes
 void Quicksort(int *X, int low, int high);
 int partition(int* X, int low, int high);
 int partitionR(int* X, int low, int high);
 void printNums(int *X);
 
// Main function. 
int main(int argc, char** argv)
{
	FILE* fPtr;
	//Checks to make sure command line contains only one other argument
	if(argc != 2){
		printf("One and only one command line arguments are allowed, terminating. \n\n");
		return 1;
	}
	//Opens files
	fPtr = fopen(argv[1], "r");
	//Checks to make sure files were found
	if(fPtr == NULL){
		printf("Could not find file, terminating.\n\n");
		return 1;
	}
	
	int *X = malloc(sizeof(int)*(ARRAY_SIZE));
	char tempStr[MAX_LINE];
	char tempDataStr[MAX_LINE];
	int i = 0;
	while(fgets(tempStr, 50, fPtr)){
		strcpy(tempDataStr, strtok(tempStr, " "));
		*(X+i) = atoi(tempDataStr);
		i++;
	}
	
	Quicksort(X, 0, i-1);
	printNums(X);
}

void Quicksort(int *X, int low, int high){
	int pivot;
	if((high-low)<=0){
		return;
	}
	pivot = partitionR(X, low, high);
	Quicksort(X, low, pivot);
	Quicksort(X, pivot+1, high);
}
int partition(int* X, int low, int high){
	int mid, pivot, i, j, k, u;
	int l = 0, m = 0, p = 0;
	int length = high-low+1;
	mid = (low+high)/2;
	pivot = *(X+mid);
	//printf("mid: %d, *(X+mid): %d length: %d, high: %d, low: %d\n\n", mid, *(X+mid), length, high, low);
	int less[length];
	int more[length];
	int tempPiv[length];
	for(i=low; i<=high; i++){
		if(*(X+i) < pivot){
			less[l] = *(X+i);
			l++;
		}
		else if(*(X+i)>pivot){
			more[m] = *(X+i);
			m++;
		}
		else{
			tempPiv[p] = pivot;
			p++;
		}
	}
	for(j=0;j<l;j++){
		*(X+j+low) = less[j];
	}
	for(u=0;u<p;u++){
		*(X+u+j+low) = tempPiv[u];
	}
	for(k=0;k<m;k++){
		*(X+k+u+j+low) = more[k];
	}
	return (j+low);
}

int partitionR(int* X, int low, int high){
    srand(time(NULL));
	int j;
    int rndInd = low + rand() % (high-low+1);
    int pivot = *(X+rndInd);
    int temp = *(X+rndInd);
	*(X+rndInd) = *(X+high);
	*(X+high) = temp;
    rndInd = high;
    int i = low -1;
    for(j=low; j<high; j++)
    {
        if(*(X+j) <= pivot)
        {
			temp = *(X+(++i));
			*(X+i) = *(X+j);
			*(X+j) = temp;
        }
    }
	temp = *(X+i+1);
	*(X+i+1) = *(X+rndInd);
	*(X+rndInd) = temp;
    return i+1;
}
		
/*int partition(int* X, int low, int high){
	int temp, mIndex, pivot, L, R;
	if(low == high){
		return high;
	}
	else if(low == high-1){
		if (*(X+high) < *(X+low))
		{
			temp = *(X+high);
			*(X+high) = *(X+low);
			*(X+low) = temp;
        }
      return;
	}
	else{
		mIndex =(low+high)/2;
		pivot = *(X+mIndex);
		*(X+mIndex) = *(X+low);
		*(X+low) = pivot;
		L = low+1;
		R = high;
		while(L<R){
			if(*(X+L) <= pivot){
				L++;
			}
			else{
				temp = *(X+R);
				*(X+R) = *(X+L);
				*(X+L) = temp;
				R--;
			}
		}
		L--;
		temp = *(X+L);
		*(X+L) = *(X+low);
		*(X+low) = temp;
		return L;
	}
}*/
/*int partition(int* X, int low, int high){
	int pivot =(low+high)/2;
	int saveHigh;
	//if(high>low+1){
		while(low<high){
			//printf("high: %d, low: %d\n", high, low);
			if(*(X+low) <= *(X+pivot)){
				low++;
			}
			else{
				saveHigh = *(X+high);
				*(X+high) = *(X+low);
				*(X+low) = saveHigh;
				high--;
			}
		}
	//}
	return pivot;
}*/

void printNums(int *X){
	int i;
	for(i=0;i<ARRAY_SIZE; i++){
		printf("%d\n", *(X+i));
	}
}	
		
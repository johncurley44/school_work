/* John Curley - jmcgdd
 * Lab Section: C
 * Submission Code: smashmouth */
 
 #include <stdio.h>
 #include <math.h>
 #include <time.h>
 
 //Define Constants
 #define MAX 20
 
 //Function prototypes
 int random_gen(void);
 void init_array(int a[], int n);
 void print_array(int a[], int n);
 void init_IDarray(int a[], int n);
 void highest_grade(int grade[], int id[], int n);
 void sort_array(int grade[], int id[], int n);
 void partial_sort(int a[], int x, int size);
 
 int main(void)
 {
	srand(time(NULL));
	//Variable declaration
	int aSize = 0, partSort = 0;
	int grade[MAX], id[MAX], bonus[MAX];
	//Asks user for size of student id and grade arrays
	printf("\n\nEnter the size of the array: ");
	scanf("%d", &aSize);
	
	//Initializes the grade and student id arrays based on user input size
	init_array(grade, aSize);
	init_IDarray(id, aSize);
	
	//Prints the initialized arrays
	printf("\n\nInput arrays are\nStudent ID: ");
	print_array(id, aSize);
	printf("\nGrade:      ");
	print_array(grade, aSize);
	
	//Places highest grade and corresponding student id in first location, prints that id and grade
	highest_grade(grade, id, aSize);
	printf("\n\nStudent with the highest grade has an ID %d with the grade %d\n", id[0], grade[0]);
	
	//Reprints arrays with highest grade and corresponding student id in first location
	printf("\nGrade and studentID arrays after calculating highest grade\nStudent ID: ");
	print_array(id, aSize);
	printf("\nGrade:      ");
	print_array(grade, aSize);
	
	//Sorts arrays in ascending order by grade, then reprints both arrays
	sort_array(grade, id, aSize);
	printf("\n\nArrays after sorting\nStudent ID: ");
	print_array(id, aSize);
	printf("\nGrade:      ");
	print_array(grade, aSize);
	printf("\n\n");
	
	//Initializes new array "bonus" with values 0-99
	init_array(bonus, aSize);
	printf("Bonus part\n");
	printf("New array:  ");
	print_array(bonus, aSize);
	
	//User inputs number to use for partial sort
	printf("\nEnter a number for partial sorting: ");
	scanf("%d", &partSort);
	
	//Uses partial_sort function and reprints array after sort
	partial_sort(bonus, partSort, aSize);
	printf("Array after partial sorting with number %d\n", partSort);
	print_array(bonus, aSize);
	printf("\n\n");
 }
 
/* Function Purpose: Creates a random integer from 0-9 and returns it
 * Input params: void
 * Return param: random integer, 0-9
 **/
 int random_gen(void)
 {
	int randGrade = 0;
	randGrade = rand() % 10;
	return randGrade;
 }
 
/* Function Purpose: Initializes an array of grade values from 0-99
 * Input params: Grade array (a[]) and array size (n)
 * Return param: void
 **/
 void init_array(int a[], int n)
 {
	int count;
	//Goes through the input array filling it with numbers from 0-99
	for(count = 0; count < n; count++)
	{
		a[count]=(random_gen()*10)+random_gen();
	}
 }
 
/* Function Purpose: Prints an array
 * Input params: Array to be printed (a[]) and size of array (n)
 * Return param: void
 **/
 void print_array(int a[], int n)
 {
	int count;
	//Goes through input array and prints one value at a time
	for(count = 0; count < n; count++)
	{
		printf("%-3d ", a[count]);
	}
 }
 
/* Function Purpose: Initializes array of student IDs with values 0 - 999
 * Input params: Student ID array (a[]) and array size (n)
 * Return param: void
 **/
 void init_IDarray(int a[], int n)
 {
	int count;
	//Goes through input array and fills it with numbers from 0 - 999 
	for(count = 0; count < n; count++)
	{
		a[count] = (((random_gen()%9)+1)*100) + (random_gen()*10) + random_gen();
	}
 }
 
/* Function Purpose: Finds the highest grade in the array, then moves it and it's corresponding student id to the first location of their respective arrays
 * Input params: Grade array (grade[]), student ID array (id[]), and array size (n)
 * Return param: void
 **/
 void highest_grade(int grade[], int id[], int n)
 {
	int count, max = 0, locMax = 0, tempSaveG = 0, tempSaveID = 0;
	//Goes through entire input array
	for(count = 0; count < n; count++)
	{
		// If the current element in the array is greater than the current max, sets max equal to current value, saves that location
		if(grade[count] > max)
		{
			max = grade[count];
			locMax = count;
		}
	}
	//Swaps first grade and student number with highest grade and corresponding student number
	tempSaveG = grade[0];
	tempSaveID = id[0];
	grade[0] = max;
	id[0] = id[locMax];
	grade[locMax] = tempSaveG;
	id[locMax] = tempSaveID;
 }
 
/* Function Purpose: Sorts the arrays in ascending order of grades
 * Input params: Grade array (grade[]), student ID array (id[]), and array size (n)
 * Return param: void
 **/
 void sort_array(int grade[], int id[], int n)
 {
	int count1, count2, tempHoldG, tempHoldID;
	//Goes through each element of array
	for(count1 = 1; count1 < n; count1++)
	{
		// Insertion sort algorithm, pushes lower values up one spot until array is in ascending order
		for (count2 = count1; count2 > 0 && grade[count2] < grade[count2-1]; count2--)
		{		
			tempHoldG = grade[count2];
			grade[count2] = grade[count2 - 1];
			grade[count2 - 1] = tempHoldG;
			tempHoldID = id[count2];
			id[count2] = id[count2 - 1];
			id[count2 - 1] = tempHoldID;
		}
	}
}

/* Function Purpose: Partially sorts input array by moving all values less than input x to left side of array in no particular order
 * Input params: input array (a[]), sort number (x), and size of input array (size)
 * Return param: void
 **/
void partial_sort(int a[], int x, int size)
{
	int count, tracker = 0, tempHold = 0, maxVal = 0;
	//Finds maximum value in input array
	for(count = 0; count < size; count++)
	{
		if(a[count] > maxVal)
		{
			maxVal = a[count];
		}
	}
	//Goes through array and moves swaps values greater than the search input with values less than the search input to force those less than to the left
	for(count = 0; count < size; count++)
	{
		if(a[count] < x && maxVal >= x)
		{	
			tempHold = a[tracker];
			a[tracker] = a[count];
			a[count] = tempHold;
			tracker++;
		}
	}
}
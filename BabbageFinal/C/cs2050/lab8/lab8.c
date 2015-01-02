/* John Curley - jmcgdd
 * Lab Section: B
 * Lab 8 - 4/2/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1)struct points*/
typedef struct points
{
	float axis[2];
	int id; 
}Points;

Points *fill_Array(FILE *fp, Points *S, int num_points);
void mergesort(Points *S, int low, int high, int number_of_points, int sort);
void merge(Points *S, int low, int middle, int high, int number_of_points, int sort);
int b_search(Points *S, int number_of_points, int ID_Target);
void print_Set(Points *S, int number_of_points);
void range_query_on_x(Points *S, int number_of_points, float x, float distance);


	int
	main(int argc, char *argv[])
	{

		/*
		* FILE I/O
		* ERROR CHECKING
		* SET MAX POINTS FROM FILE
		*/
		FILE *fp = NULL;
		
		/*5)if(argc != 1)*/
		if(argc != 2)
		{
			printf("Usage: ./file <file.txt>\n");
			return 0;
		}
	
		int number_of_points = 0;
		fp = fopen(argv[1], "r"); 
		
		if(fscanf(fp, "%d", &number_of_points) != 1)
		{
			printf("File can not be opened.\n");
		}


		/*
		* VAR DECLARATIONS
		* FILL Set with ID AND COORDINATES
		* MERGESORT ON ID
		* CLOSE FILE
		*/		

		/*2.)  Points Set = malloc(number_of_points * sizeof(Points));*/
		Points *Set = malloc(number_of_points * sizeof(Points));

		Set = fill_Array(fp, Set, number_of_points);		
		fclose(fp);
		
		mergesort(Set, 0, number_of_points, number_of_points, 0);

		print_Set(Set, number_of_points);

		/*
		* OBTAIN TARGET ID TO SEARCH FOR
		*/
		int Target = 0;
		printf("What ID to search for?\n");
		scanf("%d", &Target);
		
		int m = b_search(Set, number_of_points, Target);
		if(m != -1)
			printf("%d %f %f\n", Set[m].id, Set[m].axis[0], Set[m].axis[1]);
		else
			printf("Not found\n");


		/*
		* RESORT ON X (axis[0]) 
		* RANGE QUERY ON X
		*/

		printf("\n\nSorting on x axis..\n");
		mergesort(Set, 0, number_of_points, number_of_points, 1);
		print_Set(Set, number_of_points);
		
		float x, d;
		printf("Enter a X value and a distance from the X value you would like to return. e.g. <3.433 5.3432>\n");
		
		scanf("%d %d", &x, &d);
		range_query_on_x(Set, number_of_points, x, d);

		return 0;
	}

	/*
	* print_Set prints all points in the passedin Points *
	*/
	void
	print_Set(Points *Set, int number_of_points)
	{
		int i;
		/* 9)for(i=0; i<number_of_points; ++i)*/
		for(i=0; i<number_of_points; ++i)
			printf("%d %f %f\n", Set[i].id, Set[i].axis[0], Set[i].axis[1]);
	}

	/*
	* fill_Array, given a file point and an array of Points
	* assign all points to Points *S
	* return the allocated and filled array
	*/

	Points *
	fill_Array(FILE *fp, Points *S, int num_points)
	{
		float x_coord, y_coord;
		int ID, i = 0; 
		while(fscanf(fp, "%d %f %f", &ID, &x_coord, &y_coord) == 3 && i < num_points)
		{
		/*3)S[i]->id = ID;
			S[i]->axis[0] = x_coord;
			S[i]->axis[1] = y_coord;*/
			S[i].id = ID;
			S[i].axis[0] = x_coord;
			S[i].axis[1] = y_coord;
			/*6)needs i++*/
			i++;
		}
		/*7) need rewind*/
		rewind(fp);
		return S; 
	}
	
	/*
	* mergesort will recursively subdivide our array S and merge them back together in sorted order
	* sort determines whether we sort on ID or axis[0] (X)

	*/
	void
	mergesort(Points *S, int low, int high, int number_of_points, int sort)
	{

		if(low < high)
		{
			int middle = (low + high) / 2;
			mergesort(S, low, middle, number_of_points, sort);
			mergesort(S, middle+1, high, number_of_points, sort);
			merge(S, low, middle, high, number_of_points, sort);
		}
	}
	
	void 
	merge(Points *S, int low, int middle, int high, int number_of_points, int sort)
	{
		/*11.) Points *Helper = malloc(high * sizeof(Points));*/
		Points *Helper = malloc(number_of_points * sizeof(Points));
		int i;
		
		for(i=0; i<=high; ++i){
			Helper[i] = S[i];
		}

		int helperLeft = low;
		int helperRight = middle + 1;
		int current = low;
		/*8) while(helperLeft <= middle && helperRight <= high)*/
		while(helperLeft <= middle && helperRight <= high)
		{
			if(sort == 1)
			{
				/*12.)if( Helper[helperLeft].axis[1] <= Helper[helperRight].axis[1])*/ 
				if( Helper[helperLeft].axis[0] <= Helper[helperRight].axis[0] )
				{
					S[current] = Helper[helperLeft];
					helperLeft++;
				}
				else
				{
					S[current] = Helper[helperRight];
					helperRight++;
				}
			}
			else
			{
                if( Helper[helperLeft].id <= Helper[helperRight].id )
                {
                    S[current] = Helper[helperLeft];
                    helperLeft++;
                }
                else
                {
                    S[current] = Helper[helperRight];
                    helperRight++;
                }

			}
			current++;
		}
		/* 10) int remaining = helperLeft - middle;*/
		int remaining = middle - helperLeft;
		for(i=0; i <= remaining; ++i){
			S[current + i] = Helper[helperLeft + i];
		}
		
		
	}

	/*
	* b_search performs a binary search on our array S
	* returns -1 if ID_Target is not found
	* otherwise returns the indices of the target
	*/		

	int
	b_search(Points *S, int number_of_points, int ID_Target)
	{
		int low = 0;
		int mid;
		
		while(low < number_of_points)
		{
			mid = (low + number_of_points) / 2;
			if(S[mid].id < ID_Target)
				low = mid;
			else
				if(S[mid].id > ID_Target){
					/*3)number_of_points = mid*/
					number_of_points = mid;
				}
			else
				return mid;
		}
		
		return -1;
	}		

	/*
	* range_query_on_x will find the smallest point from x at a certain distance
	* it will then print all points within the distance
	*/

	void
	range_query_on_x(Points *S, int number_of_points, float x, float distance)
	{
		int low = 0;
		int mid;
		int high = number_of_points;
		float low_end = x - distance; 
 		float high_end = x + distance;
		
		while(low <= high)
		{
			mid = (low + high);
			if(S[mid].axis[0] < low_end)
				low = mid + 1;
			else
			if(S[mid].axis[0] > low_end)
				high = mid -1;
			else
				break;
		}
		
		while(mid < high)
		{
			if(S[mid].axis[0] <= high_end)
			{
				printf("%d %f %f\n", S[mid].id, S[mid].axis[0], S[mid].axis[1]);				
			}
			else break;
		}
	}

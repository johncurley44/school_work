/* John Curley - jmcgdd
 * Lab Section: C
 * Homework 3
 */
 
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define COLUMN 3
#define ROW 5
#define MAX_PASS 20
#define RAND_SIZE 5
typedef short BOOL;
char admin_password[] = "123abcFtw";
int seat_cost[][COLUMN] = {{200, 200, 200},
                           {200, 200, 200},
                           {200, 200, 200},
                           {150, 150, 150},                        
                           {100, 100, 100}};
void initSeats(char flight[][COLUMN], int p);
void printFlight(char flight[][COLUMN]);
BOOL isValidPassword(char input_password[]);
int getRevenue(char f1[][COLUMN], char f2[][COLUMN], char f3[ ][COLUMN]);
void setSeatReservation(char flight[][COLUMN]);

int main(void)
{	
	srand(time(NULL));
	char flight_1[ROW][COLUMN]; 
	char flight_2[ROW][COLUMN]; 
	char flight_3[ROW][COLUMN];
	char input_password[MAX_PASS];
	int reserved_seats;
	char userIn;
	printf("HERE!");
	int contLoop1 = TRUE, contLoop2 = TRUE, contLoop3 = TRUE, contLoop4 = TRUE;
	int rev = 0, flightNum;
	
	reserved_seats = rand() % RAND_SIZE + 1;
	
	while(contLoop1 == TRUE)
	{
		printf("Welcome to Joe's Travel System\n\n");
		printf("HERE");
		initSeats(flight_1, reserved_seats);
		printf("Here.");
		initSeats(flight_2, reserved_seats);
		initSeats(flight_3, reserved_seats);
		
		while(contLoop2 == TRUE)
		{
			printf("1) Admin Portal\n2) Reserve a seat on a flight\nQ) Quit Program\nOption: ");
			scanf("%c",&userIn);
			if(userIn == '1' || userIn == '2' || userIn == 'q' || userIn == 'Q')
			{
				contLoop2 = FALSE;
			}
			else
			{
				printf("Error: not an option.\n\n");
			}
		}
		
		switch(userIn)
		{
			case '1':
				while(contLoop3 == TRUE)
				{
					printf("\nAdmin password: ");
					scanf("%c", &input_password);
					if(isValidPassword(input_password) == TRUE)
					{
						printFlight(flight_1);
						printFlight(flight_2);
						printFlight(flight_3);
						rev = getRevenue(flight_1, flight_2, flight_3);
						break;
					}
					else
					{
						printf("Wrong Admin Password. Try Again.\n\n");
					}
				}
			case '2':
				printf("\nWhich flight do you want?\n1) New York\n2)Las Vegas\n3)St. Louis\nFlight: ");
				while(contLoop4 == TRUE)
				{
					scanf("%d", &flightNum);
					if(flightNum == 1)
					{
						printFlight(flight_1);
						setSeatReservation(flight_1);
						break;
					}
					else
					{
						printf("Invalid flight number. Try again.\n");
					}
				}
			case 'q':
				contLoop1 = FALSE;
				break;
			case 'Q':
				contLoop1 = FALSE;
		}
				
	}
}	

void initSeats(char flight[][COLUMN], int p)
{
	printf("HEREERE");
	int r = 0, c = 0, pCount = 0, row, col;
	printf("Here>");
	for(r = 0; r < ROW; r++)
	{
		printf("Here!");
		for(c = 0; c < COLUMN; c++)
		{
			flight[r][c] = 'O';
		}
	}
	
	for(pCount = 0; pCount < p; p++)
	{
		row = rand() % ROW;
		col = rand() % COLUMN;
		flight[row][col] = 'X';
	}
}

void printFlight(char flight[][COLUMN])
{
	int r = 0, c = 0;
	for(r = 0; r < ROW; r++)
	{
		for(c = 0; c < COLUMN; c++)
		{
			printf("%-c ", flight[r][c]);
		}
		printf("\n");
	}
}

BOOL isValidPassword(char input_password[])
{
	BOOL pwCheck;
	pwCheck = strcmp(input_password, admin_password);
	return pwCheck;
}

int getRevenue(char f1[][COLUMN], char f2[][COLUMN], char f3[ ][COLUMN])
{
	int cRow, cColumn, revenue = 0;
	for(cRow = 0; cRow < ROW; cRow++)
	{
		for(cColumn = 0; cColumn < COLUMN; cColumn++)
		{
			if(f1[cRow][cColumn] = 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
			if(f2[cRow][cColumn] = 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
			if(f3[cRow][cColumn] = 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
		}
	}
	return revenue;
}

void setSeatReservation(char flight[][COLUMN])
{
	printFlight(flight);
	int available = FALSE, checkR, checkC, seatR, seatC;
	while(available == FALSE)
	{
		checkR = FALSE; checkC = FALSE;
		while(checkR == FALSE)
		{
			printf("\n\nWhich seat row do you want?: ");
			scanf("%d", &seatR);
			if(seatR < 0 || seatR >= ROW)
			{
				printf("Seat rows are between 0 and 4\nTry again.");
			}
			else
			{
				checkR = TRUE;
			}
		}
		while(checkC == FALSE)
		{
			printf("\n\nWhich seat column do you want?: ");
			scanf("%d", &seatC);
			if(seatC < 0 || seatC >= COLUMN)
			{
				printf("Seat columns are between 0 and 2\nTry again.");
			}
			else
			{
				checkC = TRUE;
			}
		}
		if(flight[seatR][seatC] == 'X')
		{
			printf("Sorry, someone else reserved that seat\nTry again.");
		}
		else
		{
			printf("Congrats, the seat has been reserved\n\n");	
			flight[seatR][seatC] = 'X';
			printFlight(flight);
			available = TRUE;
		}
	}
}


				
			
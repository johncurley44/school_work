/* John Curley - jmcgdd
 * Lab Section: C
 * Homework 3
 */
 
//Preprocess statements
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

//Define constants
#define TRUE 1
#define FALSE 0
#define COLUMN 3
#define ROW 5
#define MAX_PASS 20
#define RAND_SIZE 5

//Create variable type BOOL
typedef short BOOL;

//Declaration of global variables
char admin_password[] = "123abcFtw";
int seat_cost[][COLUMN] = {{200, 200, 200},
                           {200, 200, 200},
                           {200, 200, 200},
                           {150, 150, 150},                        
                           {100, 100, 100}};

// Function prototypes
void initSeats(char flight[][COLUMN], int p);
void printFlight(char flight[][COLUMN]);
BOOL isValidPassword(char input_password[]);
int getRevenue(char f1[][COLUMN], char f2[][COLUMN], char f3[ ][COLUMN]);
void setSeatReservation(char flight[][COLUMN]);


int main(void)
{	
	srand(time(NULL));
	//Declaration of Variables
	char flight_1[ROW][COLUMN]; 
	char flight_2[ROW][COLUMN]; 
	char flight_3[ROW][COLUMN];
	char input_password[MAX_PASS];
	int reserved_seats;
	char userIn;
	int contLoop1 = TRUE, contLoop2, contLoop3, contLoop4;
	int rev = 0, flightNum;
	
	//Fills a random number of seats on each flight
	reserved_seats = rand() % RAND_SIZE + 1;
	initSeats(flight_1, reserved_seats);
	initSeats(flight_2, reserved_seats);
	initSeats(flight_3, reserved_seats);
	
	//Causes main menu to appear until value 'q' or 'Q' is entered
	while(contLoop1 == TRUE)
	{
		//rests the sentinel values for each of the while loops after a main menu option is completed
		contLoop2 = TRUE;
		contLoop3 = TRUE;
		contLoop4 = TRUE;
		printf("Welcome to Joe's Travel System\n\n");
		
		//Error check: if invalid input detected for main menu selection, asks for user to re-enter selection
		while(contLoop2 == TRUE)
		{
			printf("1) Admin Portal\n2) Reserve a seat on a flight\nQ) Quit Program\nOption: ");
			scanf("%s",&userIn);
			if(userIn == '1' || userIn == '2' || userIn == 'q' || userIn == 'Q')
			{
				contLoop2 = FALSE;
			}
			else
			{
				printf("Error: not an option.\n\n");
			}
		}
		
		//Switch statement used so correct funcitons are carried out from main menu selection screen
		switch(userIn)
		{
			case '1':
				//Error check: asks for admin password until a valid case sensitive password is entered
				while(contLoop3 == TRUE)
				{
					printf("\nAdmin password: ");
					scanf("%s", &input_password);
					//If the password is correct, prints all flight names and seating availability arrays, along with current total revenue from flights
					if(isValidPassword(input_password) == FALSE)
					{
						printf("\nNew York Flight\n");
						printFlight(flight_1);
						printf("\nLas Vegas Flight\n");
						printFlight(flight_2);
						printf("\nSt. Louis Flight\n");
						printFlight(flight_3);
						printf("\n");
						rev = getRevenue(flight_1, flight_2, flight_3);
						printf("The totals of all flights so far is: $%d\n\n", rev);
						contLoop3 = FALSE;
					}
					else
					{
						printf("Wrong Admin Password. Try Again.\n\n");
					}
				}
				break;
			case '2':
				printf("\nWhich flight do you want?\n1)New York\n2)Las Vegas\n3)St. Louis\nFlight: ");
				//Error check: If invalid flight number is input, asks user to try again, then does same check on new input
				while(contLoop4 == TRUE)
				{
					//When valid flight number is entered, a seat reservation is requested then the seating arrangement is updated
					scanf("%d", &flightNum);
					printf("\n");
					if(flightNum == 1)
					{
						setSeatReservation(flight_1);
						contLoop4 = FALSE;
					}
					else if(flightNum == 2)
					{
						setSeatReservation(flight_2);
						contLoop4 = FALSE;
					}
					else if(flightNum == 3)
					{
						setSeatReservation(flight_3);
						contLoop4 = FALSE;
					}
					else
					{
						printf("Invalid flight number. Try again.\n");
					}
				}
				break;
			//Terminates program if q is entered
			case 'q':
				printf("\nProgram Terminated\n");
				contLoop1 = FALSE;
				break;
			//Terminates program is Q is entered
			case 'Q':
				printf("\nProgram Terminated\n");
				contLoop1 = FALSE;
				break;
		}
				
	}
}	

/* Function Purpose: Creates seat arrangement arrays full of 'O's (open seats) then fills them with p 'X's (taken seats)
 * Input params: 1 Flight seating arrangement array, number of seats to automatically and randomly fill
 * Return param: void
 **/
void initSeats(char flight[][COLUMN], int p)
{
	int r = 0, c = 0, pCount = 0, row, col;
	//Nested for loop fills seating array of 'O's
	for(r = 0; r < ROW; r++)
	{
		for(c = 0; c < COLUMN; c++)
		{
			flight[r][c] = 'O';
		}
	}
	//Randomly places p 'X's in seating arrangement
	for(pCount = 0; pCount < p; pCount++)
	{
		row = rand() % ROW;
		col = rand() % COLUMN;
		flight[row][col] = 'X';
	}
}

/* Function Purpose: Prints current seating arrangement for input seating array
 * Input params: flight seating arrangement
 * Return param: void
 **/
void printFlight(char flight[][COLUMN])
{
	int r = 0, c = 0;
	//Nested for loop that prints one character 'O' or 'X' at a time from input seating array
	for(r = 0; r < ROW; r++)
	{
		for(c = 0; c < COLUMN; c++)
		{
			printf("%-c ", flight[r][c]);
		}
		printf("\n");
	}
}

/* Function Purpose: Checks to make sure input password is identical to the constant password defined at top of code
 * Input params: Password as input by user
 * Return param: Boolean value, 0 meaning 2 passwords are identical, 1 meaning there is a difference
 **/
BOOL isValidPassword(char input_password[])
{
	BOOL pwCheck;
	//Uses string.h function strcmp, takes two strings and compares them, returns 0 if identical
	pwCheck = strcmp(input_password, admin_password);
	/*Since strcmp can return many numbers besides 0 and 1, transforms and value that isnt 0 into 1, because we are only 
	 *interested in whether or not the password is exactly the same*/
	if(pwCheck != FALSE)
	{
		pwCheck = TRUE;
	}
	return pwCheck;
}

/* Function Purpose: Finds current total revenue from all three flights based on the seat_cost array defined globally
 * Input params: all three flight seating arrays
 * Return param: integer value representing total revenue in dollars
 **/
int getRevenue(char f1[][COLUMN], char f2[][COLUMN], char f3[ ][COLUMN])
{
	int cRow, cColumn, revenue = 0;
	/*Nested for loop goes through each position of seats, then checks each flight to see if it is taken, if so, adds corresponding
	  cost of seat to total revenue*/
	for(cRow = 0; cRow < ROW; cRow++)
	{
		for(cColumn = 0; cColumn < COLUMN; cColumn++)
		{
			if(f1[cRow][cColumn] == 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
			if(f2[cRow][cColumn] == 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
			if(f3[cRow][cColumn] == 'X')
			{
				revenue+=seat_cost[cRow][cColumn];
			}
		}
	}
	return revenue;
}

/* Function Purpose: Shows current seat availabilty, then asks user which seat they would like to reserve, filling that position
 *	of the seating array with an 'X'
 * Input params: one flight seating array
 * Return param: void
 **/
void setSeatReservation(char flight[][COLUMN])
{
	printFlight(flight);
	int available = FALSE, checkR, checkC, seatR, seatC;
	//Error check: continues asking user for seat location until a location is chosen that is open
	while(available == FALSE)
	{
		checkR = FALSE; checkC = FALSE;
		//Error check: continues asking for a row value until one that is between 0-4 is entered
		while(checkR == FALSE)
		{
			printf("\n\nWhich seat row do you want?: ");
			scanf("%d", &seatR);
			if(seatR >= 0 && seatR < ROW)
			{
				checkR = TRUE;
			}
			else
			{
				printf("Seat rows are between 0 and 4\nTry again.");
			}
		}
		//Error check: continues asking for a columb value until one that is between 0-2 is entered
		while(checkC == FALSE)
		{
			printf("\n\nWhich seat column do you want?: ");
			scanf("%d", &seatC);
			if(seatC >= 0 && seatC < COLUMN)
			{
				checkC = TRUE;
			}
			else
			{
				printf("Seat columns are between 0 and 2\nTry again.");
			}
		}
		//Prints an error message if seat is already taken, causes loop to reiterate
		if(flight[seatR][seatC] == 'X')
		{
			printf("Sorry, someone else reserved that seat\nTry again.");
		}
		//Prints a message acknowledging the seat was open and is now reserved, ends loop
		else
		{
			printf("Congrats, the seat has been reserved\n\n");	
			flight[seatR][seatC] = 'X';
			printFlight(flight);
			available = TRUE;
		}
	}
}


				
			
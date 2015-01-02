/*John Curley
 *Lab C
 *9/11/12
 *Submission Code: Wabbit
  **/

#include <stdio.h>

//Declare Constants

#define MUB 22.98
#define MLB 20.18

#define FUB 22.75
#define FLB 20.76

#define END_LOOP 0
#define CONT_LOOP 1

int main(void)
{
	//Declaration of Variables
	int mhr, gender, current_year, birth_year, age;
	double heart_rate;
	//Sentinal Control Variable
	int loop_controller = CONT_LOOP;
	int year_check = CONT_LOOP;
	
	//Verifies that the loop should or should not continue (flight info)
	while(loop_controller == CONT_LOOP)
	{		
			printf("\nPlease enter the year of the flight: ");
			scanf("%d",&current_year);
			printf("Please enter birth year: ");
			scanf("%d",&birth_year);		
		
		//Verifies that the loop should or should not continue (gender info)
		while(loop_controller == CONT_LOOP)
		{
			printf("Please Select Gender\n Male=> 1\n Female=> 2\n Exit=>0\n Gender:  ");
			scanf("%d",&gender);
		
			//Checks for a valid birth year, valid flight year, and that birth year is before flight year
			while(loop_controller==CONT_LOOP)
			{	
				if(birth_year >= 1920 && birth_year <= 2015)
				{
					if(current_year >= 1961 && current_year <= 2025)
					{
						if(birth_year >= current_year)
						{
							printf("Flight year cannot be less than or equal to birth year.\n");
							loop_controller=END_LOOP;
						}
						else
							loop_controller=END_LOOP;
					}
					else
					{
						printf("Error: flight year must be between 1961 and 2025.\n");
						loop_controller=END_LOOP;
					}
				}
				else
				{
					printf("Error: year of birth must be between 1920 and 2015\n");
					loop_controller=END_LOOP;
				}
			}
			
			//Stops asking for gender if valid gender number (0,1,2) is entered
			switch(gender)
			{
				case 1:
					loop_controller=END_LOOP;
					break;
				case 2:
					loop_controller=END_LOOP;
					break;
				case 0:
					loop_controller=END_LOOP;
					break;
				default:
					printf("Incorrect value for gender.\n");
					loop_controller=CONT_LOOP;
					break;
			}
		}
		
		//resets loop controller if valid birth year was entered 
		loop_controller=CONT_LOOP;
		
		//age calculation
		age=current_year-birth_year;
		
		//Max Heart Rate Calculation
		mhr=((double) 220-age)/3;
		
		//Compares values stored in gender if birth and current year conditions are met
		if(birth_year < current_year && current_year >= 1961 && current_year <= 2025 && birth_year >= 1920 && birth_year <= 2015)
		{
			if(gender == 1)
			{
				//Calculates men's heart rate
				heart_rate=(mhr*0.85)-(mhr*0.5);
				
				//Checks male upper and lower bounds for heart rate
				if(heart_rate > MUB)
					printf("The flight with THR (%.2lf) will NOT be safe.\n",heart_rate);
				else if(heart_rate < MLB)
					printf("The flight with THR (%.2lf) will NOT be safe.\n",heart_rate);
				else
					printf("The flight with THR (%.2lf) will be safe.\n",heart_rate);
			}
			
			else if(gender == 2)
			{
				//Calculates women's heart rate
				heart_rate=(mhr*.8)-(mhr*.45);
				
				//Checks female upper and lower bounds for heart rate
				if(heart_rate > FUB)
					printf("The flight with THR (%.2lf) will NOT be safe.\n\n",heart_rate);
				else if(heart_rate < FLB)
					printf("The flight with THR (%.2lf) will NOT be safe.\n\n",heart_rate);
				else
					printf("The flight with THR (%.2lf) will be safe.\n\n",heart_rate);
			}
			
			//Terminates program if 0 is entered
			else if(gender == 0)
			{
				printf("Program terminated.\n\n");
				loop_controller=END_LOOP;
			}
		}
	}
	
	return 0;
}
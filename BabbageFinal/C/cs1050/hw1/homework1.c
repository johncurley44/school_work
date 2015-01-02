/*
John Curley
jmcgdd
Lab Section C
Matthew England : mremtf@mail.mizzou.edu office hours Wednesday 3-4 pm 
TUTORING:  Aleks Wednesday 6-8 pm, Eliot Thursday 6-8 pm
*/

#include <stdio.h>


int main(void)
{
	/* Declare Variables*/
	int sel,mealcount=0,stop=0;
	float ham=3,fries=2,drink=1,shake=2,des=2,val=5,big=7;
	float hamt,friest,drinkt,shaket,dest,valt,bigt;
	float cost=0;
	float tax=4.225;
	
	/*Loop terminates when stop is set to 1 in case(7)*/
	while(stop==0)
	{
		printf("\n\nWelcome to Joe's, may I take your order?\n");
		printf("\tType \"0\" to order one of Joe's Juicy Burgers.\n");
		printf("\tType \"1\" to order some of Joe's tasty fries.\n");
		printf("\tType \"2\" to order a Drink.\n");
		printf("\tType \"3\" to order one of Joe's delicious Milkshakes.\n");
		printf("\tType \"4\" to order one of Joe's delightful desserts.\n");
		printf("\tType \"5\" to order one of Joe's Value Meals.\n");
		printf("\tType \"6\" to order one of Joe's Big Size Value Meals.\n");
		printf("\tType \"7\" to exit.\n\n");
		
		scanf("%d",&sel);
	
		/* Switch-case for taking order*/
		switch(sel)
		{
			case(0):
				printf("You ordered a hamburger.\n");
				/*adds tax to price of the item (same for cases 1-6)*/
				hamt=ham+(ham*(tax/100));
				/*adds the cost of the item to total income for the day (same for cases 1-6)*/
				cost+=hamt;
				/*increments the counter for number of items sold on the day (same for cases 1-6)*/
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",hamt);
			break;
			
			case(1):
				printf("You ordered fries.\n");
				friest=fries+fries*(tax/100);
				cost+=friest;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",friest);
			break;
			
			case(2):
				printf("You ordered a drink.\n");
				drinkt=drink+drink*(tax/100);
				cost+=drinkt;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",drinkt);
			break;
			
			case(3):
				printf("You ordered a milkshake.\n");
				shaket=shake+shake*(tax/100);
				cost+=shaket;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",shaket);
			break;
			
			case(4):
				printf("You ordered a dessert.\n");
				dest=des+des*(tax/100);
				cost+=dest;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",dest);
			break;
			
			case(5):
				printf("You ordered a value meal.\n");
				valt=val+val*(tax/100);
				cost+=valt;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",valt);
			break;
			
			case(6):
				printf("You ordered a big size value meal.\n");
				bigt=big+big*(tax/100);
				cost+=bigt;
				mealcount++;
				printf("The cost of your meal is $ %.2lf.\nThanks for eating at Joe's!\n\n",bigt);
			break;
			
			case(7):
				printf("\nYou have chosen to close the store for the day.\n");
				
				/*Checks to see if any items were sold, prints different message when 0 items were sold*/
				if(cost==0)
				{
					printf("There were no orders today!\n");
				}
				else		
				{
					printf("The average cost of a meal today was $ %.2lf.\n",cost/mealcount);
					printf("The total number of orders today was %d.\n",mealcount);
					printf("The day's total sales was $ %.2lf.\n",cost);
				}
				
				/*terminates while loop when user picks 7*/
				stop=1;
			break;
			
			/*anytime an input is not an integer from 0-7, this message will print*/
			default:
				printf("ERROR: You did not enter a valid number.\nRestarting order process.\n\n");
			break;
		}
	}
	
	return 0;
}
			
			
		
	
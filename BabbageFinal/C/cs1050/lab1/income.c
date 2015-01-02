#include <stdio.h>

/* John Curley
 * LAB Section C
 * Lab Code: Chuck Norris
 * 8/28/12 
 * */

int main(void)
{

	//Declare Variables
	double ticknum;
	double students;
	double stDis;
	double seniors;
	double seDis;
	double price;
	double rev;
	double stRev;
	double seRev;
	double stPrice;
	double sePrice;
	double other;
	double stIncome;
	double seIncome;



	printf("Enter the total number of tickets sold:\n");
	scanf("%lf",&ticknum);

	printf("Enter the number of students that attended:\n");
	scanf("%lf", &students);

	printf("Enter the percent discount for students:\n");
	scanf("%lf",&stDis);

	printf("Enter the number of seniors that attended:\n");
	scanf("%lf",&seniors);

	printf("Enter the percent discount for seniors:\n");
	scanf("%lf",&seDis);

	printf("Enter the price of the tickets:\n");
	scanf("%lf",&price);

	// Calculates student ticket price
	stPrice = (1-stDis/100)*price;

	// Calculates senior ticket price
	sePrice = (1-seDis/100)*price;

	// Determines number of non-student non-senior tickets
	other = ticknum-students-seniors;

	// Calculates income from students and seniors
	stIncome = stPrice*students;
	seIncome = sePrice*seniors;

	// Calculates total revenue
	rev = stIncome + seIncome + price*other;

	printf("The net income for this show is: $%.2lf\n",rev);
	printf("The net income for students is: $%.2lf\n",stIncome);
	printf("The net income for seniors is: $%.2lf\n",seIncome);

	if (stIncome > seIncome) {
		printf("The income from students is greater than that from seniors by: $%.2lf\n",stIncome-seIncome);
	}

	if (seIncome > stIncome) {
		printf("The income from seniors is greater than that from students by: $%.2lf\n",seIncome-stIncome);
	}

	if (seIncome == stIncome) {
		printf("The income from students is equal to the income from seniors\n");
	}



	return 0;

}



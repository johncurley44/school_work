#include <stdio.h>

int main(void)
{
double price1;
double ticknum;
double cost;

printf("Price of one ticket?\n");
scanf("%lf",&price1);


printf("How many tickets?\n");
scanf("%lf",&ticknum);

cost = ticknum * price1;

printf("Total Revenue is %lf\n", cost);

return 0;
}



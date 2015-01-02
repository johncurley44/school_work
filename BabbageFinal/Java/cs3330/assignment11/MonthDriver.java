//------------------------> MonthDriver Class <--------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 11	                                 ! 
//  FILENAME:   MonthDriver.java                                     !
//																	 !
//-------------------------------------------------------------------+


import java.util.*;
import java.lang.*;
public class MonthDriver
{
	public static void main(String[] args)
	{
		boolean flag = true;
		//While loop ends with excpetion only
		while(flag == true){
			int monthIn;
			Scanner input = new Scanner(System.in);
			//parses user input for number
			System.out.print("Enter a month number (1-12): ");
			
			//tries to create Month
			try
			{
				monthIn = Integer.parseInt(input.nextLine());
				Month newMonth = new Month(monthIn);
				System.out.println(newMonth.toString());
			}
			//catches if month is not integer
			catch(InputMismatchException imise)
			{
				//System.err.printf("\nException: %s\n", imise);
				System.out.println("Exception: Invalid Input Type");
				System.exit(1);
			}
			//catches if month not > 1 or < 12
			catch(InvalidMonthException ime)
			{
				System.err.printf("\nException: %s\n", ime);
				System.exit(1);
			
			}
			
				
		}
	}
}
		
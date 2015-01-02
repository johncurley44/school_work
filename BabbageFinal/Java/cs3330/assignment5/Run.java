//----------------------------->Clock Run Program<------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 5 -- Cuckoo Clock Simulator (part 1)					!
//	FILENAME: 	Run.java														!
//																				!
//	OVERALL PURPOSE																!
//	This file runs the interface and stats programs simply by creating an		!
//	Interface object of user specified time and calling its menu() function.	!													!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		None																	!
//																				!
//		ExternalFile:	Clock.java												!
//		Functions:			Clock(constructors)									!
//							run, cuckoo(), cuckoo(int n), printTime,			!
//							getNumCuckoos, resetNumCuckoos						!
//		ExternalFile:	Interface.java											!
//		Functions:			Interface(constructors)								!
//							menu												!
//																				!
//	METHOD - Main Program														!
//		Step 1 - Initialize interface object with default time					!
//		Step 2 - Call menu														!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley 							!
//																				!
//------------------------------------------------------------------------------+

public class Run
{
	public static void main(String[]args)
	{
		//STEP 1 - Initialize interface object (and therefore the clock object) with default time (12)
		Interface a = new Interface();
		//STEP 2 - Call menu
		a.menu();
	}
}
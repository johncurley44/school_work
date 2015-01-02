//------------------------>Hello Program Tester<--------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 1 -- Hello World										!
//	FILENAME: 	HelloTest.java														!
//																				!
//	OVERALL PURPOSE																!
//	The purpose of this file is to test the Hello.java file by calling the		!
//	sayHello function to print "Hello World!!!"									!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		Library:		None													!
//																				!
//		External File:	Hello.java												!
//		Functions: 		Hello (default constructor)								!
//						sayHello												!
//																				!
//	METHOD - Main program														!
//		Step 1 - Initialize object												!
//		Step 2 - Call sayHello function to print								!
//																				!
//	Credits																		!
//		All code transcribed by John Curley, originally by Dean Zeller.			!
//																				!
//------------------------------------------------------------------------------+

public class HelloTest
{
	public static void main (String[] args)
	{
		//Step 1 - Initialize object
		Hello h = new Hello();
		//Step 2 - Call sayHello function to print
		h.sayHello();
	}
}

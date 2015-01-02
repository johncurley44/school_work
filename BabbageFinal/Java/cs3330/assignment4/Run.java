//----------------------------->Stats Run Program<------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 4 -- File Input and Output							!
//	FILENAME: 	Run.java														!
//																				!
//	OVERALL PURPOSE																!
//	This file runs the interface and stats programs simply by creating an		!
//	Interface object of user specified size and calling its menu() function.	!
//	Also, it utilizes the output() function to create an output file with		!	
//	all statistics printed														!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		Library:		java.io.*												!
//		Functions:			BufferedReader										!
//							InputStreamReader									!
//																				!
//		ExternalFile:	Stats.java												!
//		Functions:			Stats(constructors)									!
//							addNum, printNums									!
//							getSum, getAvg, getMin, getMax, getCurrSize,		!
//							getArraySize, getMedian, getVariance, getStdDev		!
//							calcSum, calcAvg, calcMin, calcMax, insertionSort	!
//							insertionSortReverse, calcMedian, calcVariance,		!
//							calcStdDev											!
//		ExternalFile:	Interface.java											!
//		Functions:			Interface(constructors)								!
//							menu												!
//							output												!
//																				!
//	METHOD - Main Program														!
//		Step 1 - Initialize interface object with user input size				!
//		Step 2 - Call menu														!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley 							!
//																				!
//------------------------------------------------------------------------------+
import java.io.*;

public class Run{

	public static void main (String[] args){
		//STEP 1 - Initialize interface object with user input size	
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		String input = " ";
		int arraySize = 0;
		boolean posNumCheck = false;
		//Print welcome message
		System.out.println("\nWelcome to John Curley's Statistics Calculating Program");
		//Get user input for size of stats array
		System.out.print("\nHow many numbers would you like to use for statistical calculations?\n=>");
		while(posNumCheck == false){
			//Check to make sure user input valid int
			try
			{
				arraySize = Integer.parseInt(br.readLine());
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read number.");
				System.exit(1);
			}
			//If the user input int is positive, instantiate Interface object, call menu, end loop
			if(arraySize > 0){
				//STEP 2 - Call menu
				Interface a = new Interface(arraySize);
				a.menu();
				posNumCheck = true;
			}
			//Else, print error message and retry input
			else{
				System.out.print("\nInvalid input. Number must be greater than 0. Try again.\n=> ");
			}
		}
	} 
}
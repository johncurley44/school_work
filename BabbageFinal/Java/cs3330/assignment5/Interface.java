//------------------------->Clock Interface Program<----------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 5 -- Cuckoo Clock Simulator (part 1)					!
//	FILENAME: 	Interface.java													!
//																				!
//	OVERALL PURPOSE																!
//	This file contains an Interface object that can be called by other programs	!
//  that creates a Clock object. It also displays a menu with several options	!
//	of actions to take on the Clock object										!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		Library:		java.io.*												!
//		Functions:			BufferedReader										!
//							InputStreamReader									!
//																				!
//																				!
//																				!
//		ExternalFile:	Clock.java												!
//		Functions:			Clock(constructors)									!
//							run, cuckoo(), cuckoo(int n), printTime,			!
//							getNumCuckoos, resetNumCuckoos						!
//																				!
//	METHODS																		!
//		Constructors: Interface(int start), Interface() - default				!
//		menu -- Displays menu that asks user for input. Continues asking for	!
//				input until user decides to quit. Operations are performed		!
//				based on input, using methods from Clock.java file				!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley								!
//																				!
//------------------------------------------------------------------------------+

import java.io.*;

public class Interface
{
	private Clock a;
	private int nTime = 0;
	//Constructor for interface, with start being the start time for the call to Clock constructor
	public Interface(int start)
	{
		a = new Clock(start);
	}
	//Default calls default clock
	public Interface()
	{
		a = new Clock();
	}
	
	public void menu()
	{
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		//Initialize variables to be used in method
		String input = " ";
		int inInt = 0;
		//Print initial menu
		System.out.println("\n\n(S)tart Time\t\t\tSet the start time of cuckoo clock");
		System.out.println("(R)un\t\t\t\tRun the cuckoo clock simulation");
		System.out.println("(N)umber of Cuckoos\t\tDisplay the number of cuckoos since last reset");
		System.out.println("(Z)ero number of cuckoos\tReset the number of cuckoos to zero");
		System.out.println("(Q)uit\t\t\t\tEnd program");
		System.out.println("Help (?)\t\t\tDisplay this menu again");
		//Until quit is selected
		boolean stop = false;
		while(stop==false){
			System.out.print("\n=> ");
			//Read in user choice from menu
			try 
			{
				input = br.readLine();
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read selection.");
				System.exit(1);
			}
			//Convert input to uppercase for easier error checking
			input = input.toUpperCase();
			//If statements to determine user input
			if(input.equals("S")){
				System.out.print("Set start time ==> ");
				try
				{
					inInt = Integer.parseInt(br.readLine());
				}
				catch (IOException ioe) // catch an IO exception error
				{
					System.out.println("IO error trying to read number.");
					System.exit(1);
				}
				//If given just the hour
				if(inInt>=1 && inInt<=12){
					nTime = inInt;
					System.out.println("Start time set to " + inInt + ":00.");
				}
				//If any value that is not identifiable as a time
				else{
					System.out.println("Could not recognize input as a time. Please try again.\n");
				}
			}
			//To quit
			else if(input.equals("Q")){
				System.out.println("Exiting simulation. Have a nice day!\n");
				stop = true;
			}
			//to redisplay menu
			else if(input.equals("?")){
				menu();
				stop = true;
			}
			//If not S, first make sure a time has been set
			else{
				//If a time has been set, allow user to call methods
				if(nTime != 0){
					if(input.equals("R")){
						System.out.println("Run Simulation\n");
						a.run(nTime);
					}
					else if(input.equals("N")){
						System.out.println("Number of Cuckoos: " + a.getNumCuckoos() + "\n");
					}
					else if(input.equals("Z")){
						System.out.println("Zero out NumCuckoo counter.");
						a.resetNumCuckoos();
						System.out.println("Number of Cuckoos: " + a.getNumCuckoos() + "\n");
					}
					//If input not recognized, print error message
					else{
						System.out.println("Invalid input. Please try again.\n");
					}
				}
				//If the time has not been set
				else{
					//If the input is valid, tell the  user they need to set the time first
					if(input.equals("R") || input.equals("N") || input.equals("Z")){
						System.out.println("Must set start time first, type <S> to do so.");
					}
					//If the input is invalid, print that error message
					else{
						System.out.println("Invalid input. Please try again");
					}
				}
			}
		}
	}
}
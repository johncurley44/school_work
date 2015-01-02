//------------------------->Stats Interface Program<----------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 3 -- Menu Interface									!
//	FILENAME: 	Interface.java													!
//																				!
//	OVERALL PURPOSE																!
//	This file contains an Interface object that can be called by other programs	!
//  that creates a Stats object. It also contains a menu method that displays	!
// 	a menu and allows user to input selection and performs operation based on	!
//  input. These operations are performed by methods in the Stats.java file.	!
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
//							getArraySize, getMedian								!
//							calcSum, calcAvg, calcMin, calcMax, insertionSort	!
//							insertionSortReverse, calcMedian					!
//																				!
//	METHODS																		!
//		Constructors: Interface(int size), Interface() - default				!
//		menu -- Displays menu that asks user for input. Continues asking for	!
//				input until user decides to quit. Operations are performed		!
//				based on input, using methods from Stats.java file				!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley								!
//																				!
//------------------------------------------------------------------------------+
import java.io.*;

public class Interface
{
	//Initialize Stats object
	Stats a;
	//Constructor: creates a stats object of array size <size>
	public Interface(int size){
		a = new Stats(size);
	}
	//default constuctor, size = 10
	public Interface(){
		this(10);
	}
	public void menu(){
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		//Initialize variables to be used in method
		String input = " ";
		double inD = 0;
		double sum, average, max, min, avg, median;
		boolean stop = false;
		//Retrieve currSize of numbers array and total space allocated for numbers array
		int currSize = a.getCurrSize();
		int arraySize = a.getArraySize();
		//Print the menu of options. Case insensitive.
		System.out.println("\nWelcome to John Curley's Statistics Calculating Program");
		System.out.println("\nYou have " + (arraySize-currSize) + " slots remaining in the data array.");
		System.out.println("\nCommands available:");
		System.out.println("\t(N)umber\tAdd a number to the data array");
		System.out.println("\t(P)rint\t\tDisplay all numbers on a line");
		System.out.println("\t(S)um\t\tCalculate and display the sum of the numbers");
		System.out.println("\t(A)verage\tCalculate and display the average of the numbers");
		System.out.println("\t(L)ow\t\tCalculate and display the lowest (min) of the numbers");
		System.out.println("\t(H)igh\t\tCalculate and display the highest (max) of the numbers");
		System.out.println("\t(I)ncreasing\tSort the numbers in increasing order");
		System.out.println("\t(D)ecreasing\tSort the numbers in decreasing order");
		System.out.println("\t(?) Help\tDisplay this menu");
		System.out.println("\t(Q)uit\t\tExit the program");
		//Until quit is selected
		while(stop==false){
			System.out.print("==> ");
			//Read in user choice from menu
			try 
			{
				input = br.readLine();
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read number.");
				System.exit(1);
			}
			//Convert input to uppercase for easier error checking
			input = input.toUpperCase();
			//If statements to determine user input
			//Add a number to the numbers array using Stats.java
			if(input.equals("N")){
				System.out.print("Number: Enter number => ");
				try
				{
					inD = Double.parseDouble(br.readLine());
				}
				catch (IOException ioe) // catch an IO exception error
				{
					System.out.println("IO error trying to read number.");
					System.exit(1);
				}
				a.addNum(inD);
				System.out.println();
			}
			//Print entire numbers array using Stats.java
			else if(input.equals("P")){
				a.printNums();
				System.out.println();
			}
			//Calculates and prints the sum using Stats.java. If there are no numbers in numbers array, print message.
			else if(input.equals("S")){			
				a.calcSum();
				if(a.getCurrSize() > 0){
					sum = a.getSum();
					System.out.println("Sum: " + sum);
				}
				System.out.println();
			}
			//Calculates and prints the average using Stats.java. If there are no numbers in numbers array, print message.
			else if(input.equals("A")){	
				a.calcAvg();
				if(a.getCurrSize() > 0){
					avg = a.getAvg();
					sum = a.getSum();
					currSize = a.getCurrSize();
					System.out.println("\nAverage: " + sum + " / " + currSize + " = " + avg );
				}
				System.out.println();
			}
			//Calculates and prints the maximum number in number array using Stats.java. If there are no numbers in numbers array, print message.
			else if(input.equals("H")){
				a.calcMax();
				if(a.getCurrSize() > 0){
					max = a.getMax();
					a.printNums();
					System.out.println("Max value: " + max );
				}
				System.out.println();
			}
			//Caculates and prints minimum number in number array using Stats.java. If there are no numbers in numbers array, print message.
			else if(input.equals("L")){
				a.calcMin();
				if(a.getCurrSize() > 0){
					min = a.getMin();
					a.printNums();
					System.out.println("Min value: " + min );
				}
				System.out.println();
			}
			//Calculates the median of the number array using Stats.java. The median is equal to the two middle values divided by 2 if number of elements
			//	in array is even. If there are no numbers in numbers array, print message.
			else if(input.equals("M")){
				a.calcMedian();
				if(a.getCurrSize() > 0){
					median = a.getMedian();
				}
				System.out.println();
			}
			//Orders the array in increasing order using Stats.java.
			else if(input.equals("I")){
				a.insertionSort();
				System.out.println("Sort increasing order");
				a.printNums();
				System.out.println();
			}
			//Orders the array in decreasing order using Stats.java.
			else if(input.equals("D")){
				a.insertionSortReverse();
				System.out.println("Sort decreasing order");
				a.printNums();
				System.out.println();
			}
			//Reprints the menu using recursion. Ends current loop once recursive call has been completed.
			else if(input.equals("?")){
				menu();
				System.out.println();
				stop = true;
			}
			//Ends loop
			else if(input.equals("Q")){
				System.out.println("Exiting Program\nHave a nice day!\n");
				stop = true;
			}
			//If input does not match any above options, print error message and allow user to try again.
			else{
				System.out.println(input + ": Command not found\nEnter ? for a list of commands.");
				System.out.println();
			}
		}
	}
}
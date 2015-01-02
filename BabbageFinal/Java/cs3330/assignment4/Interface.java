//------------------------->Stats Interface Program<----------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 4 -- File Input and Output							!
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
//						java.util.Scanner										!
//		Functions:			BufferedReader										!
//							InputStreamReader									!
//							PrintWriter											!
//							createNewFile										!
//																				!
//																				!
//		ExternalFile:	Stats.java												!
//		Functions:			Stats(constructors)									!
//							addNum, printNums									!
//							getSum, getAvg, getMin, getMax, getCurrSize,		!
//							getArraySize, getMedian								!
//							calcSum, calcAvg, calcMin, calcMax, insertionSort	!
//							insertionSortReverse, calcMedian, calcVariance		!
//							calcStdDev											!
//																				!
//	METHODS																		!
//		Constructors: Interface(int size), Interface() - default				!
//		menu -- Displays menu that asks user for input. Continues asking for	!
//				input until user decides to quit. Operations are performed		!
//				based on input, using methods from Stats.java file				!
//		output -- Creates an output file with all statistics printed in it.		!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley								!
//																				!
//------------------------------------------------------------------------------+
import java.io.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

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
		double sum, average, max, min, avg, median, var, stdDev;
		boolean stop = false, fileFoundSuccess = false;
		File f;
		Scanner scan;
		//Retrieve currSize of numbers array and total space allocated for numbers array
		int currSize = a.getCurrSize();
		int arraySize = a.getArraySize();
		//Print the menu of options. Case insensitive.
		System.out.println("\nYou have " + (arraySize-currSize) + " slots remaining in the data array.");
		System.out.println("\nCommands available:");
		System.out.println("\t(F)ile\t\t\tImport a file of numbers into data array");
		System.out.println("\t(N)umber\t\tAdd a number to the data array");
		System.out.println("\t(P)rint\t\t\tDisplay all numbers on a line");
		System.out.println("\t(S)um\t\t\tCalculate and display the sum of the numbers");
		System.out.println("\t(A)verage\t\tCalculate and display the average of the numbers");
		System.out.println("\t(V)ariance\t\tCalculate and display the variance of the numbers");
		System.out.println("\tStanda(R)d Deviation\tCalculate and display the standard deviation of the numbers");
		System.out.println("\t(L)ow\t\t\tCalculate and display the lowest (min) of the numbers");
		System.out.println("\t(H)igh\t\t\tCalculate and display the highest (max) of the numbers");
		System.out.println("\t(M)edian\t\tCaclulate and display the median of the numbers");
		System.out.println("\t(I)ncreasing\t\tSort the numbers in increasing order");
		System.out.println("\t(D)ecreasing\t\tSort the numbers in decreasing order");
		System.out.println("\t(O)utput Report\t\tCreate a file with all statistics");
		System.out.println("\t(?) Help\t\tDisplay this menu");
		System.out.println("\t(Q)uit\t\t\tExit the program");
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
			if(input.equals("F")){
				// Prints error message if array is full already
				currSize = a.getCurrSize();
				if(currSize == arraySize){
					System.out.println("Array is full, you cannot enter more!\n");
				}
				//Otherwise adds value and updates the size of the array and the location in the array of where to add the next value
				else{
					fileFoundSuccess = false;
					while(fileFoundSuccess == false){
						System.out.print("File: Enter File name => ");
						//Use try catch to return error message if file not found or input can't be read
						try
						{	
							//Read in user input for file name
							input = br.readLine();
							//Initialize file to be named later via user input
							f = new File(input);
							//Initialize Scanner b to scan file
							scan = new Scanner(f);
							//Initialize an array of the doubles read in from file.
							int i = a.getCurrSize();
							while(scan.hasNextDouble() && i < arraySize){
								a.addNum(scan.nextDouble());
								i++;
							}
							if(!scan.hasNextInt()){
								currSize = a.getCurrSize();
								System.out.println("File loaded into array succesfully.\nYou have " + (arraySize-currSize) + " slots remaining in the data array.");
							}
							else{
								System.out.println("File could not be completely loaded into array. Array not large enough.");
							}
							fileFoundSuccess = true;
						}
						
						catch (FileNotFoundException e)
						{
							System.out.println("File does not exist.");
						}
						catch (IOException ioe) // catch an IO exception error
						{
							System.out.println("IO error trying to read number.");
							System.exit(1);
						}
					}
				}
			}		
				
			//Add a number to the numbers array using Stats.java
			else if(input.equals("N")){
				// Prints error message if array is full already
				currSize = a.getCurrSize();
				if(currSize == arraySize){
					System.out.println("Array is full, you cannot enter more!\n");
				}
				//Otherwise adds value and updates the size of the array and the location in the array of where to add the next value
				else{
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
					currSize = a.getCurrSize();
					System.out.println("There are " + (arraySize-currSize) + " slots remaining in the data array.");
				}
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
			//Calculates the variance of the number array using Stats.java. If there are no numbers in the array, print message.
			else if(input.equals("V")){
				a.calcVariance();
				if(a.getCurrSize() > 0){
					var = a.getVariance();
					System.out.println("\nVariance: " + var);
				}
				System.out.println();
			}
			//Calculates the standard deviation of the number array using Stats.java. If there are no numbers in the array, print message.
			else if(input.equals("R")){
				a.calcStdDev();
				if(a.getCurrSize() > 0){
					stdDev = a.getStdDev();
					System.out.println("\nStandard Deviation: " + stdDev);
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
				a.calcMedian(1);
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
			//Creates an output file with all statistics printed.
			else if(input.equals("O")){
				if(a.getCurrSize() > 0){
					this.output();
				}
				else{
					System.out.println("Array is empty. Please insert values first");
				}
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
	//Creates a file containing all the statistical calculations
	public void output(){	
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		//Initialize variables to be used in method
		String input = " ";
		System.out.print("\nWhat would you like the output file to be named?\n=> ");
		//Read in name of output file from user input
		try 
		{
			input = br.readLine();
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read number.");
			System.exit(1);
		}
		a.calcSum();
		a.calcAvg();
		a.calcMin();
		a.calcMax();
		a.calcMedian(0);
		a.calcVariance();
		a.calcStdDev();
		//checks for IO exception or inability to write file due to security
		try
		{
			File f = new File(input);
			//fileCreateSuccess checks to see if file can be created, returns true if yes, false if no, throws exception as well
			boolean fileCreateSuccess = f.createNewFile();
			if(fileCreateSuccess){
				//If file can be created, write each of the statistical calculations to it
				PrintWriter writer = new PrintWriter(f);
				writer.println("File name: " + input);
				writer.println("\tSum: " + a.getSum());
				writer.println("\tAverage: " + a.getAvg());
				writer.println("\tMinimum value: " + a.getMin());
				writer.println("\tMaximum value: " + a.getMax());
				writer.println("\tMedian: " + a.getMedian());
				writer.println("\tVariance: " + a.getVariance());
				writer.println("\tStandard Deviation: " + a.getStdDev());
				//Puts array is increasing order
				a.insertionSort();
				writer.println("\tIncreasing order: " + a.toString());
				//Puts array in decreasing order
				a.insertionSortReverse();
				writer.println("\tDecreasing order: " + a.toString());
				writer.close();
				System.out.println("File successfully created");
			}
			else{
				System.out.println("Error: File already exists");
			}
		}
		catch(IOException ioe2)
		{
			System.out.println("IO error trying to read name");
		}
		catch(SecurityException se)
		{
			System.out.println("Need permission to write this file.");
		}		
	}
}
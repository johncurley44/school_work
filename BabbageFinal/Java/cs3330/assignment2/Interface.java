//------------------------->Stats Interface Program<----------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 2 -- Statistics										!
//	FILENAME: 	Interface.java													!
//																				!
//	OVERALL PURPOSE																!
//	This file serves to test the Stats.java file by asking for 3 sets of user	!
//	input numbers and calling Stats methods to calculate sum, average, minimum	!
//	and maximum of those numbers as well as print them. Program also prints the !
//	results of the calculations													!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		Library:		java.io.*												!
//		Functions:			BufferedReader										!
//							InputStreamReader									!
//																				!
//		ExternalFile:	Stats.java												!
//		Functions:			Stats(constructors)									!
//							loadNums, printNums									!
//							getSum, getAvg, getMin, getMax						!
//							calcSum, calcAvg, calcMin, calcMax					!
//																				!
//	METHOD - Main Program														!
//		Step 1 - Initialize objects and variables								!
//		Step 2 - Read input from user and convert to double values				!
//		Step 3 - Read numbers from input into Stats.java 						!
//		Step 4 - Calculate and print the sum, average, minimum, maximum of 		!
//					stat set A													!
//		Step 5 - Calculate and print the sum, average, minimum, maximum of 		!
//					stat set B													!
//		Step 6 - Calculate and print the sum, average, minimum, maximum of 		!
//					stat set C													!
//																				!
//	CREDITS																		!
//		Code modified by John Curley. (c)John Curley (Original by Dean Zeller)	!
//																				!
//------------------------------------------------------------------------------+
import java.io.*;

public class Interface
{

    public static void main (String[] args)
    {
		// Step 1 - Initialize objects and variables
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		String input = " ";
		int statNum = 3, j;
		int totalNum[] = new int[statNum];
		
		
		// Step 2 - Read input from user and convert to double values
		// 	Reads in numbers for each set of Stats
		for(j=0;j<statNum;j++){
			try 
			{
				// Asks user for number of inputs for stat
				System.out.printf("For Stat #%d\n",j+1);
				System.out.println("How many numbers would you like to use?");
				input = br.readLine();
				totalNum[j] = Integer.parseInt(input);
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read number.");
				System.exit(1);
			}
		}
		
		// Initializes the three sets of Stats objects
		Stats a = new Stats(totalNum[0]);
		Stats b = new Stats(totalNum[1]);
		Stats c = new Stats(totalNum[2]);
		//Creates an array to hold the array of numbers for each stat
		double numArray1[] = new double[totalNum[0]];
		double numArray2[] = new double[totalNum[1]];
		double numArray3[] = new double[totalNum[2]];
		try
		{
			int i;
			// Asks user to enter numbers for each of 3 stats, amount (totalNum[]) based on previous user input
			for(i=0;i<totalNum[0];i++){
				System.out.println("Enter a number(Stat A): ");
				input = br.readLine();
				numArray1[i] = Double.parseDouble(input);
			}
			for(i=0;i<totalNum[1];i++){
				System.out.println("Enter a number(Stat B): ");
				input = br.readLine();
				numArray2[i] = Double.parseDouble(input);
			}
			for(i=0;i<totalNum[2];i++){
				System.out.println("Enter a number(Stat C): ");
				input = br.readLine();
				numArray3[i] = Double.parseDouble(input);
			}
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read number.");
			System.exit(1);
		}
	
		
		// Step 3 - Loads numbers from input into Stats.java
		a.loadNums(numArray1);
		b.loadNums(numArray2);
		c.loadNums(numArray3);
		
		// Step 4 - Calcualte and print the sum, average, minimum, and maximum of stat set A
		System.out.println("\nStat A:\n");
		
		//	Calculate
		a.calcSum();
		a.calcAvg();
		a.calcMin();
		a.calcMax();
		
		//	Print
		a.printNums();
		System.out.println("    Sum:  " + a.getSum());
		System.out.println("    Avg:  " + a.getAvg());
		System.out.println("    Min:  " + a.getMin());
		System.out.println("    Max:  " + a.getMax());
		
		// Step 5 - Calcualte and print the sum, average, minimum, and maximum of stat set B
		System.out.println("\nStat B:\n");
		
		// 	Calculate
		b.calcSum();
		b.calcAvg();
		b.calcMin();
		b.calcMax();
		
		// 	Print
		b.printNums();
		System.out.println("    Sum:  " + b.getSum());
		System.out.println("    Avg:  " + b.getAvg());
		System.out.println("    Min:  " + b.getMin());
		System.out.println("    Max:  " + b.getMax());
		
		// Step 6 - Calcualte and print the sum, average, minimum, and maximum of stat set C
		System.out.println("\nStat C:\n");
		
		//	Calculate
		c.calcSum();
		c.calcAvg();
		c.calcMin();
		c.calcMax();
		
		// Print
		c.printNums();
		System.out.println("    Sum:  " + c.getSum());
		System.out.println("    Avg:  " + c.getAvg());
		System.out.println("    Min:  " + c.getMin());
		System.out.println("    Max:  " + c.getMax());
    }
}
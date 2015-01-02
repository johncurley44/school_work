//------------------------------>Stats Program<---------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 2 -- Statistics										!
//	FILENAME: 	Stats.java														!
//																				!
//	OVERALL PURPOSE																!
//	The purpose of this file is to calculate the sum, average, minimum and 		!
//	maximum of a set of numbers.												!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		None																	!
//																				!
//	METHODS																		!
//		Constructors: Stats(int size), Stats() - default						!
//		Calc functions: calcSum, calcAvg, calcMin, calcMax						!	
//						(calculates sum, avg, min, and max of input numbers)	!
//		Get functions: getSum, getAvg, getMin, getMax							!
//		loadNums -- sets the array of numbers for stats from user input			!
//		printNums -- prints the numbers for stat calculations					!
//																				!
//	CREDITS																		!
//		Code modified by John Curley. (c)John Curley (Original by Dean Zeller)	!
//																				!
//------------------------------------------------------------------------------+
public class Stats 
{
	//Initialize Variables
    private double data[], sum, avg, min, max;
    private int arraySize;
	
	// Stat constructor, takes in number of numbers involved in Stats object
    public Stats(int size)
    {
		arraySize = size;
		// Creates a double array for each of the values to be used to calculate stats
		data = new double[arraySize];
		sum = 0.0;
		avg = 0.0;
    }
	
	// Stat default constructor, defaults to 10 numbers
    public Stats()
    {
		this(10);
    }
	
	// Brings array of numbers in from Interface.java file so they can be used in this
    public void loadNums(double[] pArray) 
    { 
		data = pArray;
    }
	
	// Prints the amount of numbers entered and the numbers themselves for the user
    public void printNums()
    {
		int i;
		System.out.println("Number of entered values: " + arraySize + "\n");
		for(i=0;i<arraySize;i++){
			System.out.println(data[i] + " ");
		}
    }

	// Return methods to send calcSum, calcAvg, calcMin and calcMax values back
    public double getSum() { return sum; }
    public double getAvg() { return avg; }
	public double getMin() { return min; }
	public double getMax() { return max; }
	
	// Calculates sum of the numbers
    public void calcSum()
    {
		int i;
		sum = 0;
		for(i=0;i<arraySize;i++){
			sum = sum + data[i];
		}
    }
	
	// Caculates the average of the numbers using calcSum
    public void calcAvg()
    {
		this.calcSum();   
		avg = sum / arraySize;
    }
	
	// Calculates the minimum of the numbers
	public void calcMin()
	{
		int i;
		min = data[0];
		for(i=0;i<arraySize;i++){
			// If the currently observed value is less than current minimum, set current value to minimum
			if(data[i] < min){
				min = data[i];
			}
		}
	}
	
	// Calculates the maximum of the numbers
	public void calcMax()
	{
		int i;
		max = data[0];
		for(i=0;i<arraySize;i++){
			// If the currently observed value is greater than current maximum, set current value to maximum
			if(data[i] > max){
				max = data[i];
			}
		}
	}

}
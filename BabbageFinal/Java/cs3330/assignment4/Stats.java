//------------------------------>Stats Program<---------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 4 -- File Input and Output							!
//	FILENAME: 	Stats.java														!
//																				!
//	OVERALL PURPOSE																!
//	The purpose of this file is to calculate the sum, average, minimum, 		!
//	maximum, median, standard deviation, and variance of a set of numbers. 		!
//	Also, this file can sort numbers in increasing or decreasing order using	! 
//	insertion sort																!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		None																	!
//																				!
//	METHODS																		!
//		Constructors: Stats(int size), Stats() - default						!
//		Calc functions: calcSum, calcAvg, calcMin, calcMax, calcMedian,			!
//						calcVariance, calcStdDev								!	
//						(calculates sum, avg, min, max, median, variance, and	!
//						 standard deviation of input numbers)					!
//		Get functions: getSum, getAvg, getMin, getMax, getCurrSize,				!
//						getArraySize, getMedian, getStdDev						!
//		addNum -- adds a number to the array of a set size, arraySize. Also		!
//					keeps track of current number of elements in array, currSize!
//		printNums -- prints the numbers in the array based on currSize			!
//		insertionSort -- sorts the array in increasing order based on insertion	!
//						sort. 													!
//		insertionSortReverse -- sorts the array in decreasing order. Also based	!
//								on insertion sort								!
//		toString -- puts current values of array into a string and returns it	!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley								!
//																				!
//------------------------------------------------------------------------------+
public class Stats 
{
	//Initialize Variables
    private double data[], sum, avg, min, max, median, variance, stdDev;
    private int arraySize, currLoc = 0, currSize = 0;
	
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
	
	// Adds a number to the array. Added via menu method of Interface.java.
    public void addNum(double num) 
    { 
		data[currLoc++] = num;
		currSize++;
		System.out.println(num + " entered into array.");
    }
	
	// Prints the values in the numbers array
    public void printNums()
    {
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Array:\t<data array is empty>");
		}
		else{
			int i;
			System.out.print("Array: ");
			for(i=0;i<currSize;i++){
				System.out.print(data[i] + " ");
			}
			System.out.println();
		}
    }

	// Return methods to send values found from calcSum, calcAvg, calcMin, calcMax, calcMedian values back. 
	//	getCurrSize and getArraySize also included to send pertinant information about the array to other files
    public double getSum() { return sum; }
    public double getAvg() { return avg; }
	public double getMin() { return min; }
	public double getMax() { return max; }
	public int getCurrSize() { return currSize; }
	public int getArraySize() { return arraySize; }
	public double getMedian() { return median; }
	public double getVariance() { return variance; }
	public double getStdDev() { return stdDev; }
	
	// Calculates sum of the numbers
    public void calcSum()
    {
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Sum:\t\t<data array is empty>");
		}
		else{
			int i;
			sum = 0;
			for(i=0;i<currSize;i++){
				sum = sum + data[i];
			}
		}
    }
	
	// Caculates the average of the numbers using calcSum
    public void calcAvg()
    {
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Average:\t<data array is empty>");
		}
		else{
			this.calcSum();   
			avg = sum / currSize;
		}
    }
	
	// Calculates the minimum of the numbers
	public void calcMin()
	{
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Minimum:\t<data array is empty>");
		}
		else{
			int i;
			min = data[0];
			for(i=0;i<currSize;i++){
				// If the currently observed value is less than current minimum, set current value to minimum
				if(data[i] < min){
					min = data[i];
				}
			}
		}
	}
	
	// Calculates the maximum of the numbers
	public void calcMax()
	{
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Maximum:\t<data array is empty>");
		}
		else{
			int i;
			max = data[0];
			for(i=0;i<currSize;i++){
				// If the currently observed value is greater than current maximum, set current value to maximum
				if(data[i] > max){
					max = data[i];
				}
			}
		}
	}
	//Using insertion sort, orders the array by increasing value
	public void insertionSort(){
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Array:\t<data array is empty>");
		}
		else{
			int i, j;
			double save;
			//Looks at each element of array
			for(i=1; i<currSize; i++){
				j = i-1;
				//Cycles through all the elements before the ith element to find sorted location for the original ith element
				while(j>=0 &&  (data[j+1]<data[j])){
						save = data[j];
						data[j] = data[j+1];
						data[j+1] = save;
						j--;
				}
			}
		}
	}
	//Using insertion sort, orders the array by decreasing value
	public void insertionSortReverse(){
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Array:\t<data array is empty>");
		}
		else{
			int i, j;
			double save;
			//Looks at each element of array
			for(i=1; i<currSize; i++){
				j = i-1;
				//Cycles through all the elements before the ith element to find sorted location for the original ith element
				while(j>=0 && (data[j+1]>data[j])){
						save = data[j];
						data[j] = data[j+1];
						data[j+1] = save;
						j--;
				}
			}
		}
	}
	//Finds the middle element of the array after it has been sorted using insertionSort() method. Prints information only if print != 0
	public void calcMedian(int print){
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Median:\t<data array is empty>");
		}
		else{
			if(print != 0){
				System.out.println("Median");
			}
			this.insertionSort();
			if(print != 0){
				System.out.print("\tSorted list: ");
				this.printNums();
			}
			//if the array has an even number of values, print the median as the average of the middle two
			if(currSize%2 == 0){
				median = (data[currSize/2] + data[(currSize/2)-1])/2.0;
				if(print != 0){
					System.out.println("\tMedian value: (" + data[currSize/2] + "+" + data[(currSize/2)-1] + ")/2 = " + median);
				}
			}
			//if the array has an odd number of values, print the middle value
			else{
				median = data[currSize/2];
				if(print != 0){
					System.out.println("\tMedian value: " + median);
				}
			}
		}
		
	}
	//Finds and prints the variance of the array of numbers
	public void calcVariance(){
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Variance:\t<data array is empty>");
		}
		else{
			//gets number of values in array
			currSize = this.getCurrSize();
			//gets average of current values in array
			this.calcAvg();
			double avgVar = this.getAvg();
			int i;
			double varNumerator = 0;
			//Performs sumation in numerator of variance equation
			for(i=0;i<currSize;i++){
				varNumerator = varNumerator + Math.pow((data[i] - avgVar), 2);
			}
			variance = varNumerator/((double)(currSize-1));
		}
	}
	//Finds and prints the standard deviation of the array of numbers
	public void calcStdDev(){
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("Standard Deviation:\t<data array is empty>");
		}
		else{
			//gets variance of numbers
			this.calcVariance();
			double stdVar = this.getVariance();
			stdDev = Math.sqrt(stdVar);
		}
	}
	
	//Puts the array values into a string and returns it
	public String toString(){
		int i;
		currSize = this.getCurrSize();
		String arrString = " ";
		for(i=0;i<currSize;i++){
			arrString = arrString + " " + data[i];
		}
		return arrString;
	}
}

//------------------------------>Stats Program<---------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 3 -- Menu Interface									!
//	FILENAME: 	Stats.java														!
//																				!
//	OVERALL PURPOSE																!
//	The purpose of this file is to calculate the sum, average, minimum, 		!
//	maximum, and median of a set of numbers. Also, this file can sort numbers	!
//	in increasing or decreasing order using insertion sort						!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		None																	!
//																				!
//	METHODS																		!
//		Constructors: Stats(int size), Stats() - default						!
//		Calc functions: calcSum, calcAvg, calcMin, calcMax, calcMedian			!	
//						(calculates sum, avg, min, max, and median of input 	!
//							numbers)											!
//		Get functions: getSum, getAvg, getMin, getMax, getCurrSize,				!
//						getArraySize, getMedian									!
//		addNum -- adds a number to the array of a set size, arraySize. Also		!
//					keeps track of current number of elements in array, currSize!
//		printNums -- prints the numbers in the array based on currSize			!
//		insertionSort -- sorts the array in increasing order based on insertion	!
//						sort. 													!
//		insertionSortReverse -- sorts the array in decreasing order. Also based	!
//								on insertion sort								!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley	!
//																				!
//------------------------------------------------------------------------------+
public class Stats 
{
	//Initialize Variables
    private double data[], sum, avg, min, max, median;
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
		// Prints error message if array is full already
		if(currSize == arraySize){
			System.out.println("Array is full, you cannot enter more!\n");
		}
		//Otherwise adds value and updates the size of the array and the location in the array of where to add the next value
		else{
			data[currLoc++] = num;
			currSize++;
			System.out.println(num + " entered into array.");
			System.out.println("There are " + (arraySize-currSize) + " slots remaining in the data array.");
		}
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
	//Finds and prints the middle element of the array after it has been sorted using insertionSort() method.
	public void calcMedian(){
		System.out.println("Median");
		// If the array is empty, prints message.
		if(currSize == 0){
			System.out.println("\tArray:\t<data array is empty>");
		}
		else{
			this.insertionSort();
			System.out.print("\tSorted list: ");
			this.printNums();
			//if the array has an even number of values, print the median as the average of the middle two
			if(currSize%2 == 0){
				median = (data[currSize/2] + data[(currSize/2)-1])/2.0;
				System.out.println("\tMedian value: (" + data[currSize/2] + "+" + data[(currSize/2)-1] + ")/2 = " + median);
			}
			//if the array has an odd number of values, print the middle value
			else{
				median = data[currSize/2];
				System.out.println("\tMedian value: " + median);
			}
		}
		
	}
	

}

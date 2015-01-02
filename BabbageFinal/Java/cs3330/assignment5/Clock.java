//------------------------------>Clock Program<---------------------------------+
//																				!
//	NAME:		John Curley														!
//	CLASS:		CS3330 - Object Oriented Programming							!
//	PROFESSOR: 	Dean Zeller (LAB A - 8:00T, TA Michael Brush)					!
//	TERM:		Fall, 2013														!
//	PROJECT:	Assignment 5 -- Cuckoo Clock Simulator (part 1)					!
//	FILENAME: 	Clock.java														!
//																				!
//	OVERALL PURPOSE																!
//	The purpose of this file is to implement an object, Clock, that simulates	!
//	a cuckoo clock. The clock can run forward an hour, print cuckoos on the		!
// 	hour, print the time, send the number of cuckoos, and reset the number 		!
//	of cuckoos.																	!
//																				!
//	LIBRARIES AND EXTERNAL FUNCTIONS											!
//		None																	!
//																				!
//	METHODS																		!
//		Constructors: Clock(int start), Clock() - default						!
//																				!
//		Get functions: getNumCuckoos											!
//		run -- advances the time forward an hour, prints the time each minute	!
//				and calls the cuckoo function to print cuckoos on the hour		!
//		cuckoo -- no input: prints a cuckoo										!		
//					input n: prints calls cuckoo() n times						!
//		printTime -- prints current time										!
//		resetNumCuckoos -- sets the attribute cuckoos to zero					!
//																				!
//	CREDITS																		!
//		Code created by John Curley. (c)John Curley								!
//																				!
//------------------------------------------------------------------------------+

public class Clock
{
	//Initialize class attributes
	private int time;
	private int cuckoos;
	//Clock constructor
	public Clock(int start)
	{
		//If given just the hour
		if(start>=1 && start<=12){
			time = start*100;
		}
		//If any value that is not identifiable as a time
		else{
			System.out.println("Could not recognize input for time. Set to default - 12:00");
			time = 1200;
		}
	}
	//Default constructor - default value of time is 12
	public Clock()
	{
		this(12);
	}
	//run function, runs clock for hour calling printTime and cuckoo to print the time and corresponding num of cuckoos on the hour
	public void run(int start)
	{
		time = start*100;
		int endTime, i;
		//If time is between 12:00 and 12:59, send back to 1
		if(time==1200){
			endTime = 100;
		}
		//Otherwise, add an hour
		else{
			endTime = time + 100;
		}
		//Print start and end time for user
		System.out.print("Start time:\t");
		printTime();
		System.out.println("\nEnd time:\t" + endTime/100 + ":00\n");
		//Run clock simulation
		System.out.println("Starting clock...\n");
		//Cal cuckoo to print time and corresponding number of cuckoos
		this.cuckoo(time/100);
		time++;
		System.out.println();
		//Add a minute and print the time with each minute added
		if(time<1200){
			while(time<(endTime-40)){
				printTime();
				time++;
			}
		}
		else{
			while(time<1260){
				printTime();
				time++;
			}
		}
		time = endTime;
		System.out.println();
		this.cuckoo(time/100);
		System.out.println();
		System.out.println("\nEnding clock...\n");
	}
	//prints a single cuckoo, adds one to the cuckoo count, cuckoos
	void cuckoo()
	{
		System.out.print("Cuckoo! ");
		cuckoos++;
	}
	//prints the current time and then the corresponding number of cuckoos using a for loop and the cuckoo() method
	void cuckoo(int n)
	{
		printTime();
		System.out.print(" -- ");
		int i;
		for(i=0;i<n;i++){
			this.cuckoo();
		}
	}
	//Prints the current time
	void printTime()
	{
		if(time%100 < 10){
			System.out.print(time/100 + ":0" + time%100 + " ");
		}
		else{
			System.out.print(time/100 + ":" + time%100 + " ");
		}
	}
	
	int getNumCuckoos()	  	{	return cuckoos;	};
	void resetNumCuckoos()	{	cuckoos=0;		};
}
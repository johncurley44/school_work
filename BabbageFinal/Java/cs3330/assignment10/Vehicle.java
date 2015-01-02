//------------------------> Vehicle Class <--------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 10	                                 ! 
//  FILENAME:   Vehicle.java                                         !
//																	 !
//-------------------------------------------------------------------+


import java.util.*;
import java.io.*;

public class Vehicle implements Drivable
{
	//Instance Variables
	private String make;
	private String model;
	private int year;
	private int topSpeed;
	private double accelerationRate;
	private double decelerationRate;
	private double currentSpeed; 
	private double distanceTraveled; 
	private double driveTime; 
	private int passengerCapacity;

	//Get functions
	public double getCurrentSpeed()		{	return this.currentSpeed; 		}
	public double getDistanceTraveled()	{	return this.distanceTraveled;	}
	public double getDriveTime()		{	return this.driveTime;			}
	
	//Other functions:
	
	public void readInput(){
		//Initiates scanner, takes in input for each item
		Scanner input = new Scanner(System.in);
		System.out.print("Please enter the Make: ");
		this.make = input.nextLine();
		System.out.print("Please enter the Model: ");
		this.model = input.nextLine();
		System.out.print("Please enter the Year: ");
		this.year = Integer.parseInt(input.nextLine());
		System.out.print("Please enter the Capacity: ");
		this.passengerCapacity = Integer.parseInt(input.nextLine());
		System.out.print("Please enter the Top Speed: ");
		this.topSpeed = Integer.parseInt(input.nextLine());
		System.out.print("Please enter the Acceleration: ");
		this.accelerationRate = Double.parseDouble(input.nextLine());
		System.out.print("Please enter the Deceleration: ");
		this.decelerationRate = Double.parseDouble(input.nextLine());
	}
	//Menu function
	public void drive(){
		Scanner input = new Scanner(System.in);
		boolean stopFlag = false;
		int choice;
		int celerateSel, honkNum;
		double timeInput;
		//Loop that ends when user selects quit
		do{
			System.out.println("What would you like to do?\n1.  Accelerate\n2.  Decelerate\n3.  Honk\n4.  Get stats\n5.  Exit");
			choice = Integer.parseInt(input.nextLine());
			//Accelerate - ask for how fast and how long
			if(choice == 1){
				System.out.println("How fast do you want to accelerate?\n1. 25%\n2. 50%\n3. 100% (Pedal to the metal)");
				celerateSel = Integer.parseInt(input.nextLine());
				System.out.print("For how long do you want to accelerate? ");
				timeInput = Double.parseDouble(input.nextLine());
				this.accelerate(celerateSel, timeInput);
			}
			//Decelerate - ask how fast and how long
			else if(choice == 2){
				System.out.println("How fast do you want to decelerate?\n1. 25%\n2. 50%\n3. 100% (Pedal to the metal)");
				celerateSel = Integer.parseInt(input.nextLine());
				System.out.print("For how long do you want to decelerate? ");
				timeInput = Double.parseDouble(input.nextLine());
				this.decelerate(celerateSel, timeInput);
			}
			//Honk - ask for number of honks, call honk function
			else if(choice == 3){
				System.out.print("How many times would you like to honk? ");
				honkNum = Integer.parseInt(input.nextLine());
				honk(honkNum);
			}
			//Print travel info
			else if(choice == 4){
				printTravelInfo();
			}
			//Quit - stop loop
			else if(choice == 5){
				System.out.println("Hope you had a safe drive!");
				stopFlag = true;
			}
			//Invalid input
			else{
				System.out.println("Please enter a valid input, 1-5\n");
			}
		}while(stopFlag == false);
	}
	@Override
	public void accelerate(int level, double time){
		//accelArr stores the 3 modification values for level of acceleration
		double []accelArr = new double[3];
		double tempTime;
		accelArr[0] = 0.25;
		accelArr[1] = 0.5;
		accelArr[2] = 1.0;
		this.accelerationRate  = this.accelerationRate * accelArr[level-1];
		//When vehicle is at top speed, use formula for distance: d = v*t only
		if(this.currentSpeed >= this.topSpeed){
			this.distanceTraveled = this.distanceTraveled + (this.currentSpeed * time);
		}
		//When vehicle is not yet at top speed, must factor in acceleration as below
		else{
			//tempTime is how long it takes the vehicle to reach top speed
			tempTime = (double)this.topSpeed/this.accelerationRate;
			//If top speed is reached before user input time is up, add distance with acceleration up to when vehicle reaches top speed, then add no-accel distance calculated at top speed
			if(tempTime < time){
				this.distanceTraveled = this.distanceTraveled + ((this.currentSpeed * tempTime) + ((this.accelerationRate*Math.pow(tempTime,2))/2));
				this.distanceTraveled = this.distanceTraveled + (this.topSpeed * (time-tempTime));
			}
			//If top speed is not reached by end of user input time, use distance calculation with acceleration for entire user input time
			else{
				this.distanceTraveled = this.distanceTraveled + ((this.currentSpeed * time) + ((this.accelerationRate*Math.pow(time,2))/2));
			}
			
		}
		System.out.println("\nAccelerating at " + this.accelerationRate + "m/s^2");
		this.currentSpeed = this.currentSpeed + (this.accelerationRate * time);
		//Sets speed to top speed if acceleration would normally cause it to breach top speed
		if(this.currentSpeed > this.topSpeed){
			this.currentSpeed = this.topSpeed;
		}
		System.out.println("Now traveling at " + this.currentSpeed + "m/s");
		this.driveTime = this.driveTime + time;
	}
	@Override
	public void decelerate(int level, double time){
		//decelArr contains the three modification values based on user input
		double []decelArr = new double[3];
		double tempTime;
		decelArr[0] = -0.25;
		decelArr[1] = -0.5;
		decelArr[2] = -1.0;
		this.decelerationRate  = this.decelerationRate * decelArr[level-1];
		//tempTime is how long it takes the vehicle to come to a stop
		tempTime = ((double)this.currentSpeed/this.decelerationRate)*(-1);
		//if the vehicle comes to a stop before the user input time has elapsed, uses distance equation with deceleration only up to time vehicle stops
		if(tempTime < time){
			this.distanceTraveled = this.distanceTraveled + ((this.currentSpeed * tempTime) + ((this.decelerationRate*Math.pow(tempTime,2))/2));
		}
		//if the vehicle does not come to a stop before user input time, uses entire time in distance calculation
		else{
			this.distanceTraveled = this.distanceTraveled + ((this.currentSpeed * time) + ((this.decelerationRate*Math.pow(time,2))/2));
		}
		System.out.println("\nDecelerating at " + this.decelerationRate + "m/s^2");
		this.currentSpeed = this.currentSpeed + (this.decelerationRate * time);
		//If the vehicle's speed has gone below zero, it has stopped. Prints and changes currentSpeed accordingly
		if(this.currentSpeed < 0){
			System.out.println("Stopped");
			this.currentSpeed = 0;
		}
		//Keeps vehicle from going above top speed
		else if(this.currentSpeed > this.topSpeed){
			System.out.println("Now traveling at " + this.topSpeed + "m/s");
		}
		//Prints speed when speed > 0 and speed < top speed
		else{
			System.out.println("Now traveling at " + this.currentSpeed + "m/s");
		}
		//Updates time
		this.driveTime = this.driveTime + time;
	}
	@Override
	//Prints n honks
	public void honk(int n){
		int i;
		System.out.println();
		for(i=0;i<n;i++){
			System.out.print("HONK! ");
		}
		System.out.println("\n");
	}
	//Prints how far you have traveled, how long you have traveled, and current speed
	public void printTravelInfo(){
		System.out.println("We have traveled " + this.distanceTraveled + "m over " + this.driveTime + "s and are currently moving at " + this.currentSpeed + "m/s");
	}
}
		
		

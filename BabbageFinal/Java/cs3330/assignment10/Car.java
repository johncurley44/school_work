//--------------------------> Car Class <----------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 10	                                 ! 
//  FILENAME:   Car.java  	                                         !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Car extends Vehicle
{
	private int numDoors;
	
	public Car(){
		this.readInput();
	}
	@Override
	//Overrides the readInput method from Vehicle to include number of doors
	public void readInput(){
		Scanner input = new Scanner(System.in);
		super.readInput();
		System.out.print("Please enter the number of doors: ");
		this.numDoors = Integer.parseInt(input.nextLine());
	}
}
//-------------------------> Boat Class <----------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 10	                                 ! 
//  FILENAME:   Boat.java  	                                         !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Boat extends Vehicle
{
	private int numPropellers;
	
	public Boat(){
		this.readInput();
	}
	@Override
	//Overrides the readInput method from Vehicle to include the number of propellers
	public void readInput(){
		super.readInput();
		Scanner input = new Scanner(System.in);
		System.out.print("Please enter the number of propellers: ");
		this.numPropellers = Integer.parseInt(input.nextLine());
	}
}
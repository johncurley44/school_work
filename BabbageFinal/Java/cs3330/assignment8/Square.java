//------------------------> Square Class <---------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 8	                                 ! 
//  FILENAME:   Square.java                                          !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Square extends Rectangle
{
	//constructor that takes in the length of the sides of the square
	public Square (double sideLength)
	{
		//Sends information up to rectangle as the length and width
		super(sideLength, sideLength);
	}
	
	@Override
	//Will ask the user for the Square's side length. An IOException is checked for. If the input is successful, sets the length and
	//	width of the rectangle super class to the same value assigned by the user.
	public void readInput()
	{
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		
		System.out.print("Enter the square's side length: ");
		try 
		{
			double tempLen = Double.parseDouble(br.readLine());
			super.setLength(tempLen);
			super.setWidth(tempLen);
			//this.setLength(tempLen);
			//this.setWidth(tempLen);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
	}
	//Get methods
	public double getSideLength(){	return super.getLength();	}
	
	@Override
	//Prints the shape type (Square) and the type's relevant attributes (dimensions, area, perimeter)
	public String toString()
	{
		String infoString = "Square\n\tDimensions = "+this.getSideLength()+" x "+this.getSideLength()+"\n\tArea = "+this.calcArea()+"\n\tPerimeter = "+this.calcPerimeter();
		return infoString;
	}
}
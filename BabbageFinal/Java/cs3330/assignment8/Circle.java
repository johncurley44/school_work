//------------------------> Circle Class <---------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 8	                                 ! 
//  FILENAME:   Circle.java                                          !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Circle extends Ellipse
{
	//Constructor that takes in the radius of the circle
	public Circle(double radius)
	{
		//Uses a super call to ellipse where major axis = minor axis = radius
		super(radius, radius);
	}
	
	@Override
	//Will ask the user for the circle's radius. An IOException is checked for. If the input is successful, sets the major and minor
	//	axes of the ellipse superclass to the same value assigned by the user.
	public void readInput()
	{
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		
		System.out.print("Enter the circle's radius: ");
		try 
		{
			double tempRad = Double.parseDouble(br.readLine());
			super.setMajorAxis(tempRad);
			super.setMinorAxis(tempRad);
			//this.setMajorAxis(tempRad);
			//this.setMinorAxis(tempRad);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
	}
	
	//Get methods
	public double getRadius()	{	return super.getMajorAxis();	}
	
	@Override
	//Prints the shape type (circle) and its relevant attributes (radius, area, perimeter)
	public String toString()
	{
		String infoString = "Circle\n\tRadius = "+this.getRadius()+"\n\tArea = "+this.calcArea()+"\n\tPerimeter = "+this.calcPerimeter();
		return infoString;
	}

}
//------------------------> Ellipse Class <--------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 8	                                 ! 
//  FILENAME:   Ellipse.java                                         !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Ellipse implements Shape
{
	//Instance variables
	private double majorAxis;
	private double minorAxis;
	
	//Constructor that takes in the major and minor axes of an ellipse
	public Ellipse(double majorAxis, double minorAxis)
	{
		this.majorAxis = majorAxis;
		this.minorAxis = minorAxis;
	}
	//Public constructor that sets the Ellipse to have major and minor axes to 1
	public Ellipse()
	{
		this(1.0,1.0);
		
	}
	
	@Override
	//Will ask user for the ellipse's major and minor axes. An IOException is checked for. If input is successful, set functions
	// 	this class will be called
	public void readInput()
	{
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		
		System.out.print("Enter the ellipse's major axis length: ");
		try 
		{
			double tempMaj = Double.parseDouble(br.readLine());
			this.setMajorAxis(tempMaj);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
		System.out.print("Enter the ellipse's minor axis length: ");
		try 
		{
			double tempMin = Double.parseDouble(br.readLine());
			this.setMinorAxis(tempMin);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
	}
	
	@Override
	//Uses pi and the minor and major axis values to calculate the Ellipse's area.
	public double calcArea()
	{
		return Math.PI * this.minorAxis * this.majorAxis;
	}
	
	@Override
	//Uses pi and the minor and major axis values to calculate the Ellipse's perimeter
	public double calcPerimeter()
	{
		double perim = 2*Math.PI*(Math.sqrt((Math.pow(this.majorAxis,2) + Math.pow(this.minorAxis,2))/2));
		return perim;
	}
	//Get and set methods for Ellipse
	public double getMajorAxis(){	return this.majorAxis;	}
	public double getMinorAxis(){	return this.minorAxis;	}
	//Before setting the major or minor axis, performs a check to make sure that the major axis is larger than the minor, if not, prints
	//	a message and switches the values.
	public void setMajorAxis(double majorAxis)
	{
		if(majorAxis >= this.minorAxis){
			this.majorAxis = majorAxis;
		}
		else{
			System.out.println("NOTICE: Major axis was found to be smaller than minor axis, switching the values.");
			this.majorAxis = this.getMinorAxis();
			this.minorAxis = majorAxis;
		}
	}
	//Before setting the major or minor axis, performs a check to make sure that the major axis is larger than the minor, if not, prints
	//	a message and switches the values.
	public void setMinorAxis(double minorAxis)
	{
		if(minorAxis <= this.majorAxis){
			this.minorAxis = minorAxis;	
		}
		else{
			System.out.println("NOTICE: Major axis was found to be smaller than minor axis, switching the values.");
			this.minorAxis = this.getMajorAxis();
			this.majorAxis = minorAxis;
		}
	}
	
	@Override
	//Prints the shape type (Ellipse) and all of its relevant attributes (major axis, minor axis, area, perimeter)
	public String toString()
	{
		String infoString = "Ellipse\n\tAxis Lengths = "+this.majorAxis+" x "+this.minorAxis+"\n\tArea = "+this.calcArea()+"\n\tPerimeter = "+this.calcPerimeter();
		return infoString;
	}
}
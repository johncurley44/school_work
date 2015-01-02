//-----------------------> Rectangle Class <-------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 8	                                 ! 
//  FILENAME:   Rectangle.java                                       !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Rectangle implements Shape
{
	//Instance variables
	private double length;
	private double width;
	
	//Constructor when given length and width of rectangle
	public Rectangle(double length, double width)
	{
		this.length = length;
		this.width = width;
	}
	//Default constructor, sets sides to 1
	public Rectangle()
	{
		this(1.0,1.0);
		//System.out.println("No values given for major or minor axes, setting to default, 1");
		
	}
	 
	@Override
	//Will ask user for rectangle's length and rectangle's width. For each, the user input is read and an IOException is checked for.
	//	If no exception, the rectangle's width and length are set to user specified values.
	public void readInput()
	{
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		
		System.out.print("Enter the rectangle's length : ");
		try 
		{
			double tempLen = Double.parseDouble(br.readLine());
			this.setLength(tempLen);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
		System.out.print("Enter the rectangle's width: ");
		try 
		{
			double tempWid = Double.parseDouble(br.readLine());
			this.setWidth(tempWid);
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
	}
	
	@Override
	//Uses length and width instances of Rectangle to return the shape's area.
	public double calcArea()
	{
		return this.length * this.width;
	}
	
	@Override
	//Uses the length and width instances of Rectangle to return the shape's perimeter.
	public double calcPerimeter()
	{
		double perim = 2*this.length + 2*this.width;
		return perim;
	}
	//Get and Set methods
	public double getLength()			{		return this.length;		}
	public double getWidth()			{		return this.width;		}
	public void setLength(double length){		this.length = length;	}
	public void setWidth(double width)	{		this.width = width;		}
	
	@Override
	//Prints out a block of text containing the shape type(rectangle), and its notable atributes (length, width, area, perimeter)
	public String toString()
	{
		String infoString = "Rectangle\n\tDimensions = "+this.length+" x "+this.width+"\n\tArea = "+this.calcArea()+"\n\tPerimeter = "+this.calcPerimeter();
		return infoString;
	}
}
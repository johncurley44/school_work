//----------------------------> Reptile class <---------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Reptile.java                                              !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a reptile, a group within animals.                                !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Animal   extends the Animal class.                                !
//                                                                        !
//  ATTRIBUTES                                                            !
//      scaleThickness  All reptiles have scales. This is a measure of 	  !
//						the thickness of the reptile's scales. Measured   !
//						in inches							 	          !
//                                         								  !
//                                                                        !
//  METHODS                                                               !
//      Reptile           Constructor                                     !
//      getScaleThickness get-method for scaleThickness 				  !
//		growScales		  Increases the thickness of scales by .1 inch    !
//      printInfo         Prints the information for the animal           !
//                        (abstract method)                               !
//      stayWarm          Describes how the animal stays warm.            !
//                        (abstract method)								  !
//		getName			  Returns name of animal (abstract method)        !
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public abstract class Reptile extends Animal 
{
	protected double scaleThickness;
	
	public Reptile()
	{
		super();
		this.scaleThickness=0;
	}
	
	public Reptile(double scaleThickness, int numLegs)
	{
		super(numLegs);
		this.scaleThickness = scaleThickness;
	}
	
	public double getScaleThickness()
	{
		return scaleThickness;
	}
	
	public void growScales(){
		this.scaleThickness = this.scaleThickness + .1;
	}
	
	public abstract void printInfo();
	public abstract void stayWarm();
	public abstract String getName();
}

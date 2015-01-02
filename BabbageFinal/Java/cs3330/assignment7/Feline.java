//-----------------------------> Feline class <---------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Feline.java                                               !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a feline, a sub-group within mammal.                              !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Mammal   extends the Mammal class.                                !
//                                                                        !
//  ATTRIBUTES                                                            !
//      isExtinct	    Some felines have gone extinct, such as the 	  !
//						sabretooth tiger								  !
//		clawsOut		Boolean: true for claws extended, false if        !
//						retracted									      !
//                                                                        !
//  METHODS                                                               !
//      Feline           Constructor                                      !
//      getIsExtinct													  !
//		extendClaws		  Sets clawsOut to true                           !
//      printInfo         Prints the information for the animal           !
//                        (abstract method)                               !
//      stayWarm          Describes how the animal stays warm.            !
//                        (abstract method)								  !
//		getName			  (abstract method)								  !
//		                            								      !							
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public abstract class Feline extends Mammal
{
	protected boolean isExtinct;
	protected boolean clawsOut;
	
	public Feline()
	{
		super();
		this.isExtinct = false; 
	}
	
	public Feline(int furThickness, boolean extinctIn, boolean clawsOutIn)
	{
		super(furThickness);
		this.isExtinct = extinctIn;
		this.clawsOut = clawsOutIn;
	}
	
	public boolean getIsExtinct()
	{
		return isExtinct;
	}
	
	public void extendClaws(){
		clawsOut = true;
	}
	
	public abstract void printInfo();
	public abstract void stayWarm();
	public abstract String getName();
}

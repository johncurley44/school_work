//-----------------------------> Mammal class <---------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Mammal.java                                               !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a mammal, a group within animals.                                 !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Animal   extends the Animal class.                                !
//                                                                        !
//  ATTRIBUTES                                                            !
//      furThickness    All mammals have fur.  This is a measure of the   !
//                      thickness of the animal's fur.                    !
//                                                                        !
//  METHODS                                                               !
//      Mammal            Constructor                                     !
//      getFurThickness   get-method for furThickness                     !
//      printInfo         Prints the information for the animal           !
//                        (abstract method)                               !
//      stayWarm          Describes how the animal stays warm.            !
//                        (abstract method)                               !
//		getName			  Returns the animals name (abstract method)      !
//                                                                        !
//  CREDITS                                                               ! 
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public abstract class Mammal extends Animal
{
	protected int furThickness;
	
	public Mammal()
	{
		this.furThickness=0;
	}
	
	public Mammal(int furThickness)
	{
		this.furThickness = furThickness;
	}
	
	public int getFurThickness()
	{
		return furThickness;
	}
	
	public abstract void printInfo();
	public abstract void stayWarm();
	public abstract String getName();
}

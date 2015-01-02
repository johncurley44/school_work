//-----------------------------> Animal class <---------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00AM T, TA Michael Brush)         !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Animal.java                                               !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for an animal, a member of the zoo.                                   !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      none                                                              !
//                                                                        !
//  ATTRIBUTES                                                            !
//      numLegs     The number of legs the specific animal has.           !
//                                                                        !
//  METHODS                                                               !
//      Animal          Constructor                                       !
//      getNumLegs()	Returns the number of legs a particular animal    ! 
//						has                                               !
//      printInfo       Prints the information for the animal (abstract)  !
//      getName         Returns animal's name (abstract)	              !
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public abstract class Animal 
{
	private int numLegs;
	
	public Animal()
	{
		this.numLegs=4;
	}
	
	public Animal(int numLegs)
	{
		this.numLegs=numLegs;
	}
	
	public int getNumLegs() { return(numLegs); }
	public abstract void printInfo();
	public abstract String getName();
}

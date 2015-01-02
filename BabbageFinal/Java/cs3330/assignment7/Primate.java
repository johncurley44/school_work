//-----------------------------> Primate class <--------------------------+
//                                                                        !
//  NAME:       John Curley                                               ! 
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Primate.java                                              !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a primate, a sub-group within mammal.                             !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Mammal   extends the Mammal class.                                !
//                                                                        !
//  ATTRIBUTES                                                            !
//      canBraciate     Some primates, but not all, can braciate.  This   !
//                      boolean attribute indicates whether the primate   !
//                      defined can braciate (swing from branches).       !
//                                                                        !
//  METHODS                                                               !
//      Primate           Constructor                                     !
//      getcanBraciate                                                    !
//      printInfo         Prints the information for the animal           !
//                        (abstract method)                               !
//      stayWarm          Describes how the animal stays warm.            !
//                        (abstract method)    						      !
//		getName			  Returns name	(abstract method)				  !	
//		useThumbs()       Prints message that animal can use thumbs 	  !
//						 (abstract method)       						  !
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public abstract class Primate extends Mammal
{
	protected boolean canBraciate;
	
	public Primate()
	{
		super();
		this.canBraciate = false;
	}
	
	public Primate(int furThickness, boolean canBraciate)
	{
		super(furThickness);
		this.canBraciate = canBraciate;
	}
	
	public boolean getCanBraciate()
	{
		return canBraciate;
	}
	
	public abstract void printInfo();
	public abstract void stayWarm();
	public abstract String getName();
	public abstract void useThumbs();
}

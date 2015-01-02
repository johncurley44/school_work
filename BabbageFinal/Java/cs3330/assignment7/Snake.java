//-----------------------------> Snake class <----------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Snake.java                                                !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a snake, a sub-group within reptile.                              !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Reptile   extends the Mammal class.                               !
//                                                                        !
//  ATTRIBUTES                                                            !
//      isVenomous    Some snakes, but not all, have venom.  This boolean !
//                    attribute indicates whether the snake defined has   !
//                    venom.									          !
//                                                                        !
//  METHODS                                                               !
//      Snake	          Constructor                                     !
//      getIsVenomous                                                     !
//		hiss    	      Prints "hisssssssssssssssssss"                  !
//      printInfo         Prints the information for the animal           !
//                        (abstract method)                               !
//      stayWarm          Describes how the animal stays warm.            !
//                        (abstract method)      						  !
//		getName			  (abstract method)		                          !
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        ! 
//------------------------------------------------------------------------+

public abstract class Snake extends Reptile
{
	protected boolean isVenomous;
	
	public Snake()
	{
		super();
		this.isVenomous = false;
	}
	
	public Snake(double scaleThickness, boolean isVenomous)
	{
		super(scaleThickness, 0);
		this.isVenomous = isVenomous;
	}
	
	public boolean getIsVenomous()
	{
		return isVenomous;
	}
	
	public void hiss(){
		System.out.println("hissssssssssssssssssssssssssssss");
	}
	
	public abstract void printInfo();
	public abstract void stayWarm();
	public abstract String getName();
}

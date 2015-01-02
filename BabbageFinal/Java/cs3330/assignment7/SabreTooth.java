//-----------------------------> SabreTooth class <----------------------------+
//                                                                        	   !
//  NAME:       John Curley												  	   !
//  CLASS:      CS3330 - Object Oriented Programming                      	   !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           	   !
//  TERM:       Fall, 2013                                                	   !
//  PROJECT:    Assignment 7 -- Inheritance                              	   ! 
//  FILENAME:   SabreTooth.java                                                !
//                                                                        	   !
//  OVERALL PURPOSE                                                       	   !
//  The purpose of this object is to define the classes and attributes    	   !
//  for a sabretooth, a species within feline.                                 !
//  									                                  	   !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      	   !
//      Feline   extends the feline class.                              	   !
//                                                                       	   !
//  ATTRIBUTES                                                                 !
//      toothLength    Sabretooth tigers have different size teeth,			   !
//						measured in inches									   !
//		name			Name of sabretooth									   !
//                                                                       	   !
//  METHODS                                                                    !
//      SabreTooth      Constructor                                       	   !
//      getName              											  	   !
//      getToothLength                                                    	   !
//      printInfo       Prints the information for the animal             	   !
//      stayWarm        Describes how the animal stays warm.              	   !
//      growTeeth       Lengthen's the sabretooth's teeth by 1 inch.		   !
//																         	   !
//                                                                       	   !
//  CREDITS                                                               	   !
//    All code written by John Curley, based on a template written by Dean	   !
//    Zeller and Ankil Patel.  (c)2013 John Curley                        	   !
//                                                                             !
//-----------------------------------------------------------------------------+

public final class SabreTooth extends Feline
{
	private int toothLength;
	private String name;
	
	public SabreTooth()
	{
		super();
		this.name = "Generic Sabretooth";
		this.toothLength = 0; 
	}
	
	public SabreTooth(String name, int furThickness, int toothLengthIn, boolean extinctIn, boolean clawsOut)
	{
		super(furThickness, extinctIn, clawsOut);
		this.name = name;
		this.toothLength = toothLengthIn;
	}
	
	public String getName()
	{
		return(name);
	}
	
	public int getToothLength()
	{
		return(toothLength);
	}
	
	public void printInfo()
	{
		System.out.println("This is "+name+".  He is a sabretooth tiger.");
		System.out.println("As a sabretooth tiger, "+name+" walks on "+super.getNumLegs()+" legs.");
		this.stayWarm();
		this.growTeeth();
		System.out.println(name+"'s teeth are now "+this.getToothLength()+" inches long.");
		if(super.clawsOut == true){
			System.out.println("His claws are out.");
		}
		else{
			System.out.println("His claws are not out.");
		}
		if(super.isExtinct == true){
			System.out.println("Unfortunately for "+name+". His species, including himself, is extinct. ");
		}
		else{
			System.out.println("A sabretooth tiger has been found, and the species is no longer extinct! His name is "+name+".");
		}
	}
	
	public void stayWarm()
	{
		System.out.println(this.getName()+" stays warm with fur, with a fur thickness rating of "+this.getFurThickness()+".");
	}
	
	public void growTeeth(){
		toothLength = toothLength + 1;
	}

}

//----------------------------> RattleSnake class <----------------------------+
//                                                                        	   !
//  NAME:       John Curley												  	   !
//  CLASS:      CS3330 - Object Oriented Programming                      	   !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           	   !
//  TERM:       Fall, 2013                                                	   !
//  PROJECT:    Assignment 7 -- Inheritance                              	   ! 
//  FILENAME:   RattleSnake.java                                               !
//                                                                        	   !
//  OVERALL PURPOSE                                                       	   !
//  The purpose of this object is to define the classes and attributes    	   !
//  for a rattlesnake, a species within Snake.                                 !
//  									                                  	   !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                     	   !
//      Snake  extends the snake class.                              	       !
//                                                                    	       !
//  ATTRIBUTES                                                           	   !
//      rattleVolume	The loudness of a rattlesnake's rattle is variable.    !
//						Measured in decibals.								   !
//		name			Name of rattlesnake									   !
//                                                                        	   !
//  METHODS                                                               	   !
//      RattleSnake      Constructor                                      	   !
//      getName              											  	   !
//      getRattleVolume                                                   	   !
//      printInfo       Prints the information for the animal             	   !
//      stayWarm        Describes how the animal stays warm.             	   !
//      rattle	        Snake warms you to back off.					  	   !
//																         	   !
//                                                                       	   !
//  CREDITS                                                              	   !
//    All code written by John Curley, based on a template written by Dean	   !
//    Zeller and Ankil Patel.  (c)2013 John Curley                        	   !
//                                                                        	   !
//-----------------------------------------------------------------------------+

public final class RattleSnake extends Snake
{
	private double rattleVolume;
	private String name;
	
	public RattleSnake()
	{
		super();
		this.name = "Generic RattleSnake";
		this.rattleVolume = 0;
	}
	
	public RattleSnake(String name, double scaleThickness, double rattleVolumeIn, boolean venomousIn)
	{
		super(scaleThickness, venomousIn);
		this.name = name;
		this.rattleVolume = rattleVolumeIn;
	}
	
	public String getName()
	{
		return(name);
	}
	
	public double getRattleVolume()
	{
		return(rattleVolume);
	}
	
	public void printInfo()
	{
		System.out.println("This is "+name+".  He is a rattlesnake.");
		System.out.println("As a rattlesnake, "+name+" walks on "+super.getNumLegs()+" legs."); 
		super.growScales();
		this.stayWarm();
		super.hiss();
		this.rattle();
		System.out.println(name+" hisses at "+this.getRattleVolume()+" decibals!");
		if(super.isVenomous == true){
			System.out.println("Watch out! This guy is venomous!");
		}
		else{
			System.out.println("Pfffffff, he doesn't even have any venom!");
		}
	}
	
	public void stayWarm()
	{
		System.out.println(this.getName()+" stays warm with scales and cold blood, with a scale thickness rating of "+this.getScaleThickness()+".");
	}
	
	public void rattle(){
		System.out.println("rattlerattlerattlerattlerattlerattlerattlerattle");
	}

}

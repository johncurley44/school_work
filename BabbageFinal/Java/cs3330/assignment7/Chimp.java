//-----------------------------> Chimp class <----------------------------+
//                                                                        !
//  NAME:       John Curley												  !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Chimp.java                                                !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to define the classes and attributes    !
//  for a chimp, a species within primate.                                !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      Primate   extends the primate class.                              !
//                                                                        !
//  ATTRIBUTES                                                            !
//      bornInWild     Some chimps were born in the wild, and thus        !
//                     developed instincts and mannerisms of wild chimps. !
//                     Others were born in captivity, and matured around  !
//                     humans.  										  !
//		name		   Name of particular chimp                           !
//                                                                        !
//  METHODS                                                               !
//      Chimp           Constructor                                       !
//      getName            The name of the particular chimp in quesiton.  !
//      getBornInWild                                                     !
//      printInfo       Prints the information for the animal             !
//      stayWarm        Describes how the animal stays warm.              !
//      useThumbs       Indicates that chimps can use their thumbs        !
//                      effectively, unlike most other animals.           !
//		takeOverWorld	Message printed saying chimp takes over world if  !
//						born in captivity						          !
//                                                                        !
//  CREDITS                                                               ! 
//    All code written by John Curley, based on a template written by Dean!
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

public final class Chimp extends Primate
{
	private boolean bornInWild;
	private String name;
	
	public Chimp()
	{
		super();
		this.name = "Generic Chimp";
		this.bornInWild = false;
	}
	
	public Chimp(String name, int furThickness, boolean canBraciate, boolean bornInWild)
	{
		super(furThickness, canBraciate);
		this.name = name;
		this.bornInWild = bornInWild;
	}
	
	public String getName()
	{
		return(name);
	}
	
	public boolean getBornInWild()
	{
		return(bornInWild);
	}
	
	public void printInfo()
	{
		System.out.println("This is "+name+".  He is a chimp.");
		System.out.println("As a chimp, "+name+" walks on "+super.getNumLegs()+" legs.");
		this.stayWarm();
		this.useThumbs();
		this.takeOverWorld();
	}
	
	public void stayWarm()
	{
		System.out.println(this.getName()+" stays warm with fur, with a fur thickness rating of "+this.getFurThickness()+".");
	}

	public void useThumbs()
	{
		System.out.println("A chimp can effectively use its thumbs.");
	}

	public void takeOverWorld()
	{
		if (this.bornInWild)
			System.out.println(this.getName()+" was born in the wild.  He will pretty much act like other chimps.");
		else 
		{
			System.out.println(this.getName()+" was born in captivity, and is thus much smarter than other chimps in regards to how humans interact.");
			System.out.println("Be warned -- chimps raised in captivity can potentially rule the Earth.");
		}
	}
}

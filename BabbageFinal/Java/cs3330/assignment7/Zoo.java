//-----------------------------> Zoo Program <----------------------------+
//                                                                        !
//  NAME:       John Curley                                               !
//  CLASS:      CS3330 - Object Oriented Programming                      !
//  PROFESSOR:  Dean Zeller (Lab A -- 8:00 T, TA Michael Brush)           !
//  TERM:       Fall, 2013                                                !
//  PROJECT:    Assignment 7 -- Inheritance                               ! 
//  FILENAME:   Zoo.java                                                  !
//                                                                        !
//  OVERALL PURPOSE                                                       !
//  The purpose of this object is to create a zoo fact list that          !
//  describes animals at various levels of the classification hierarchy.  !
//  									                                  !
//  LIBRARIES AND EXTERNAL FUNCTIONS                                      !
//      ArrayList   An ArrayList is used to store the animal instances.   !
//      Animal      The abstract class defining animals.                  !
//                                                                        !
//  METHODS                                                               !
//      main:   The main program to create the animals and print the      !
//              information sheet.                                        !
//                                                                        !
//  CREDITS                                                               !
//    All code written by John Curley, based on ideas written by Dean     !
//    Zeller and Ankil Patel.  (c)2013 John Curley                        !
//                                                                        !
//------------------------------------------------------------------------+

import java.util.ArrayList;

public class Zoo {
	public static void main(String args[])
	{
		ArrayList animals;
		animals = new ArrayList();
		
		// add a series of animals with proper parameters.
		animals.add(new Chimp("Dean", 2,false, true));
		animals.add(new Chimp("Bruce", 3,true, true));
		animals.add(new Chimp("Steve", 2,true, false));

		// <further animals go here>
		animals.add(new Chimp("Rick", 4, true, true));
		
		animals.add(new SabreTooth("Tony", 1, 5, true, false));
		animals.add(new SabreTooth("Frank", 2, 6, true, true));
		animals.add(new SabreTooth("Hank", 3, 7, true, false));
		animals.add(new SabreTooth("George", 4, 8, false, true));
		
		animals.add(new RattleSnake("Sssam", 0.1, 9.2, true));
		animals.add(new RattleSnake("Ssssean", 0.2, 10.4, true));
		animals.add(new RattleSnake("Sssstan", 0.4, 15.2, true));
		animals.add(new RattleSnake("Ssssal", 1.2, 40.3, false));
		
		System.out.println("Animal Report");
		System.out.println("-------------");
		System.out.println();
		for (int i=0;i<animals.size();i++)
		{
			System.out.println("Animal "+(i+1)+":  "+((Animal) animals.get(i)).getName());
			((Animal) animals.get(i)).printInfo();
			System.out.println();
		}
		
		System.out.println("Thank you for using the animal reporting program.");
	}
}

//------------------> SentenceDriver Class <-------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 9	                                 ! 
//  FILENAME:   SentenceDriver.java                                  !
//																	 !
//-------------------------------------------------------------------+

import java.io.*;

public class SentenceDriver
{
	//Main program
	public static void main(String []args)
	{
		//Creates new string objects for user input
		String inString1 = new String();
		String inString2 = new String();
		boolean s1SubS2, s2SubS1;
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		System.out.println("Enter Sentence One:");
		//Read in user choice from menu
		try 
		{
			inString1 = br.readLine();
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
		System.out.println("Enter Sentence Two:");
		//Read in user choice from menu
		try 
		{
			inString2 = br.readLine();
		}
		catch (IOException ioe) // catch an IO exception error
		{
			System.out.println("IO error trying to read selection.");
			System.exit(1);
		}
		//Creates new sentence objects using the input strings from user
		Sentence sent1 = new Sentence(inString1);
		Sentence sent2 = new Sentence(inString2);
		//If the second sentence is a substring of the first sentence, prints so
		if(sent2.isSubstringOf(sent1) ==  true){
			System.out.println("\n\""+inString2+"\" IS a substring of \"" + inString1 + "\"");
		}
		//If the second sentence is not a substring of the first senetence, prints so
		else{
			System.out.println("\n\""+inString2+"\" is NOT a substring of \"" + inString1 + "\"");
		}
		//If the first sentence is a substring of the second sentence, prints so
		if(sent1.isSubstringOf(sent2) ==  true){
			System.out.println("\n\""+inString1+"\" IS a substring of \"" + inString2 + "\"");
		}
		//If the first sentence is not a substring of the second sentence, prints so
		else{
			System.out.println("\n\""+inString1+"\" is NOT a substring of \"" + inString2 + "\"");
		}
		//Prints histogram for each sentence
		sent1.histogram();
		sent2.histogram();
		
	}
}
		
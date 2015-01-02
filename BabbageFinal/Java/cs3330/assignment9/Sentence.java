//-----------------------> Sentence Class <--------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 9	                                 ! 
//  FILENAME:   Sentence.java                                        !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
import java.io.*;

public class Sentence
{
	//Creates public instance String
	public String theLine;
	//Object constructor
	public Sentence(String s){
		this.theLine = s;
	}
	//Method that checks if this object is a substring of input sentence object
	public boolean isSubstringOf(Sentence s){
		//Creates new string with input sentence's getLine string set to lowercase, for case insensitivity
		String lowerCaseIn = s.getLine().toLowerCase();
		//Creates new string with this sentence's getLine string set to lowercase, for case insensitivity
		String lowerCaseThis = this.theLine.toLowerCase();
		//if the input contains the current object's string, method returns true
		if (lowerCaseIn.contains(lowerCaseThis)){
			return true;
		}
		//if not, returns false
		else{
			return false;
		}
	}
	//Method that constructs and prints a histogram of frequency of case insensitive letters in sentence. Ignores non letter characters.
	public void histogram(){
		//Count array keeps track of frequency of each letter in alphabet, a-z
		int[] count = new int[26];
		int i, j;
		char temp;
		//Turns current sentence into all lowercase string
		String caseInsens = this.theLine.toLowerCase();
		//For each character in the current string
		for(i=0;i<this.theLine.length(); i++){
			//temp is the currently observed character
			temp = caseInsens.charAt(i);
			//if temps value is between a-z (ASCII 97-122)
			if(temp > 96 && temp < 123){
				//Adds one to frquency for that letter
				count[temp-97]++;
			}
		}
		//Prints Histogram header
		System.out.println("\nHistogram of \"" + this.theLine + "\":");
		//For each letter in the alphabet
		for(i=0;i<26;i++){
			//If frequency of that letter is higher than 0
			if(count[i] > 0){
				//Prints that character
				System.out.print((char)(97+i)+": ");
				//Prints number of stars equal to frequency
				for(j=0;j<count[i];j++){
					System.out.print("*");
				}
				System.out.println();
			}
		}
	}
	//Returns theLine string instance
	public String getLine(){
		return this.theLine;
	}
}
	
		
		
		
		
//---------------------> Drivable interface <------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams(Lab A -- 8:00AM T, TA Michael Brush)   !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 10	                                 ! 
//  FILENAME:   Drivable.java                                           !
//																	 !
//-------------------------------------------------------------------+

import java.util.*;
//Creates the interface for shape
public interface Drivable
{
	public void accelerate(int x, double y);
	public void decelerate(int x, double y);
	public void honk(int x);
}

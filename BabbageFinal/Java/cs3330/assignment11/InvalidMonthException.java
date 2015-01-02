//-----------------> InvalidMonthException Class <-------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 11	                                 ! 
//  FILENAME:   InvalidMonthException.java  	                     !
//																	 !
//-------------------------------------------------------------------+
public class InvalidMonthException extends Exception
{
	public InvalidMonthException()
	{
		super("Exception: Invalid Month");
	}
	
	public InvalidMonthException(String msg)
	{
		super(msg);
	}
}
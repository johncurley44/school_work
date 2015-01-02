//-------------------------> Month Class <---------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 11	                                 ! 
//  FILENAME:   Month.java  	                                	 !
//																	 !
//-------------------------------------------------------------------+

public class Month
{
	private int monthNumber;
	//Creates a month, throws exception if <1 or >12
	public Month(int monthNumber) throws InvalidMonthException
	{
		if(monthNumber < 1 || monthNumber > 12){
			throw new InvalidMonthException("Invalid month given: ("+monthNumber+")\n");
		}
		else{
			this.monthNumber = monthNumber;
		}
			
	}
	//Sets month value, throws exception if <1 or >12
	public void setMonth(int monthNumber) throws InvalidMonthException
	{
		if(monthNumber < 1 || monthNumber > 12){
			throw new InvalidMonthException("Invalid month given: ("+monthNumber+")\n");
		}
		else{
			this.monthNumber = monthNumber;
		}
			
	}
	//Returns month name based on number of month
	public String toString()
	{
		String monthName = new String();
		switch(this.monthNumber){
			case 1:
				monthName = "January";
				break;
			case 2: 
				monthName = "February";
				break;
			case 3: 
				monthName = "March";
				break;
			case 4:
				monthName = "April";
				break;
			case 5:
				monthName = "May";
				break;
			case 6:
				monthName = "June";
				break;
			case 7:
				monthName = "July";
				break;
			case 8:
				monthName = "August";
				break;
			case 9:
				monthName = "September";
				break;
			case 10:
				monthName = "October";
				break;
			case 11: 
				monthName = "November";
				break;
			case 12: 
				monthName = "December";
				break;
			default:
				break;
		}
		return ("The name of the month you entered was "+monthName);
		
				
	}
	
}
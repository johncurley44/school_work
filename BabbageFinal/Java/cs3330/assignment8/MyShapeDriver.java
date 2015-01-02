//-------------------> MyShapeDriver Class <-------------------------+
//                                                                   !
//  NAME:       John Curley                                          !
//  CLASS:      CS3330 - Object Oriented Programming                 !
//  PROFESSOR:  Don Guilliams (Lab A -- 8:00AM T, TA Michael Brush)  !
//  TERM:       Fall, 2013                                           !
//  PROJECT:    Lab Assignment 8	                                 ! 
//  FILENAME:   MyShapeDriver.java                                   !
//																	 !
//-------------------------------------------------------------------+

import java.io.*;

public class MyShapeDriver
{
	//Main program
	public static void main(String []args)
	{
		//Initialize Shape array
		Shape[] shapeArray = null;
		//Initialize BufferedReader for user input
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		//Initialize int to store size of shape array input
		int numShapesInput = 0;
		//Initialize int to store type of shape
		int shapeType = 0;
		double tempDim1 = 0, tempDim2 = 0;
		boolean continueFlag1 = true;
		int numShapesChosen = 0;
		int i;
		//Until the user passes in a valid number of shapes (greater than 0)
		while(continueFlag1 == true){
			System.out.println("How many shapes would you like to store?");
			//Read in user choice from menu
			try 
			{
				numShapesInput = Integer.parseInt(br.readLine());
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read selection.");
				System.exit(1);
			}
			if(numShapesInput > 0){
				shapeArray = new Shape[numShapesInput];
				continueFlag1 = false;
			}
			else{
				System.out.println("ERROR: You entered an invalid number");
			}
		}
		//Asks user for type of shape and values of relevant attributes (readInput()) for n shapes, where n is equal to
		//	numShapesInput (user specified)
		while(numShapesChosen < numShapesInput){
			System.out.println("Which shape would you like to enter?");
			System.out.println("1. Ellipse\n2. Circle\n3. Rectangle\n4. Square");
			System.out.print("Your Choice: ");
			try 
			{
				shapeType = Integer.parseInt(br.readLine());
			}
			catch (IOException ioe) // catch an IO exception error
			{
				System.out.println("IO error trying to read selection.");
				System.exit(1);
			}
			//Switch statement that calls methods depending on which shape was chosen by the user.
			switch(shapeType){
				//Creates a new Ellipse, then calls readInput() to set its attributes
				case 1:
					shapeArray[numShapesChosen] = new Ellipse(1, 1);
					shapeArray[numShapesChosen].readInput();
					numShapesChosen++;
					break;
				//Creates a new Circle, then calls readInput() to set its attributes
				case 2:
					shapeArray[numShapesChosen] = new Circle(1);
					shapeArray[numShapesChosen].readInput();
					numShapesChosen++;
					break;
				//Creates a new Rectangle, then calls readInput() to set its attributes
				case 3:
					shapeArray[numShapesChosen] = new Rectangle(1, 1);
					shapeArray[numShapesChosen].readInput();
					numShapesChosen++;
					break;
				//Creates a new Squaree, then calls readInput() to set its attributes
				case 4: 
					shapeArray[numShapesChosen] = new Square(1);
					shapeArray[numShapesChosen].readInput();
					numShapesChosen++;
					break;
				//The user input a number that is not 1,2,3 or 4. Prints out error message.
				default:
					System.out.println("ERROR: That number does not correspond to a valid shape");
					break;
			}
		}
		//Prints the information on each shape as specified by user. Uses the toString method from each of the shape type classes
		System.out.println("**************************\nYour shape array contains:\n");
		for(i=0;i<numShapesInput;i++){
			System.out.println("Shape "+i);
			System.out.println(shapeArray[i]);
			shapeArray[i].toString();
		}
					
	}
}	
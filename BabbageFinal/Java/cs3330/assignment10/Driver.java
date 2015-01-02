import java.util.*;

public class Driver {
	public static void main(String[] args) {
		
		int type = -1;
		Vehicle vehicle = new Vehicle();
		Scanner input = new Scanner(System.in);
		
		while (type == -1)
		{
			
			System.out.println("Please select a vehicle type:");
			System.out.println("1. Car\n2. Motorcycle\n3. Boat");
			type = Integer.parseInt(input.nextLine());
			
			
			switch(type){
				case 1:
					vehicle = new Car();
					break;
				case 2:
					vehicle = new Motorcycle();
					break;
				case 3:
					vehicle = new Boat();
					break;
				default:
					System.out.println("Invalid Entry");
					type = -1;	
			}
		}
		
		//Drive the vehicle
		vehicle.drive();
	}
}
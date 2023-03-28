import java.util.Scanner;

public class BaseConversionCalculator {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in); //User input
		int choice = 0;
		do {
			System.out.println("Please select your option:\n1. Decimal to Hexadecimal\n2. Hexadecimal to Decimal\n3.Exit");
			if (input.hasNextInt()) { //check if the input is valid (1/2/3)
				choice = input.nextInt(); //User input
				switch(choice) { //switch cases
				case 1: //if the input is a decimal number
					System.out.print("Please enter a decimal number: ");
					if (input.hasNextInt()) { //check if the input is valid - only integer)
						long decimal = input.nextInt();
						String hex = decimalToHex(decimal); //convert the input from decimal to hexadecimal
						System.out.println("Hexadecimal: " + hex);
					} else {
						System.out.println("Invalid input! Please enter an integer.");
					}
					break;
				case 2: //if the input is an hexadecimal number
					System.out.print("Enter a hexadecimal number: ");
					String hexString = input.next();
					if (hexString.matches("[0-9A-Fa-f]+")) { //check if the input is valid - only numbers and letters till 'F')
						long decValue = hexToDecimal(hexString); //convert the input from hexadecimal to decimal
						System.out.println("Decimal: " + decValue);
					}
					else {
						System.out.println("Invalid input! Please enter an hexadecimal number.");
					}
					break;
				case 3: //the user doesn't want to use the calculator
					System.out.println("Bye Bye!");
					break;
				default:  //if the input is not valid (1/2/3)
					System.out.println("Invalid choice!");
					break;
				}
			}
			else {
				System.out.println("Invalid input! Please enter an integer.");
				input.next();
			}
		}
		while (choice!=3);
	}
	public static String decimalToHex(long Decimal) { //convert decimal to hexadecimal
		StringBuilder hex = new StringBuilder();
		for(long i = 0; i< Decimal; i++) {
			long rem = Decimal % 16; //get the remainder after dividing by 16
			if(rem < 10) { //if the remainder is less than 10 --> a number between 0-9
				hex.insert(0, rem); //insert the remainder number to the beginning of the string
			} 
			else { //if the remainder is more than 10 --> a letter between A-F
				hex.insert(0, (char)('A' + rem - 10)); 
			}
			Decimal = Decimal/16; //divide the number by 16
		}

		return hex.toString(); //get the converted value
	}

	public static long hexToDecimal(String hex) { //convert hexadecimal to decimal 
		long  dec = 0;
		for(int i = 0; i < hex.length(); i++) {
			long lastVal = 0;
			char hexChar = hex.charAt(i); //get the ascii value of the char, only one char each iteration
			if(hexChar >= '0' && hexChar <= '9') { //if the char is a number
				lastVal = hexChar - '0'; //ascii value of '0' is 48 (by subtraction of zero, we get the original digit)
			} else if(hexChar >= 'a' && hexChar <= 'f') { //if the char is a letter
				lastVal = hexChar - 'a' + 10;
			} else if(hexChar >= 'A' && hexChar <= 'F') { //if the char is a letter
				lastVal = hexChar - 'A' + 10;
			}
			dec = dec * 16 + lastVal;                              
		}
		return dec;
	}
}


import java.util.Scanner;

public class calculator {



	public static void main(String[] args) {
		Menu();
	}
	public static void Menu() { 
		System.out.println("-------------MENU-------------" + "\n" + "---Choose only Integers---" + "\n" + "Choose 1 for DecToHex (10->16)" + "\n" + "Choose 2 for HexToDec (16->10)" +"\n" + "Choose 0 for EXIT");
		Scanner input = new Scanner(System.in);
		if (input.hasNextInt()) { //check for int
			int Choose=input.nextInt(); //Input for Menu
			while (Choose != 1 && Choose != 2 && Choose != 0) { 
				System.out.println("Wrong choice! Please type again");
				input = new Scanner(System.in); //User Input again
				Choose=input.nextInt();
			}
			if (Choose==1)  //Basic 10->16
				DecToHex();
			else if (Choose==2) //Basic 16->10
				HexToDec();
			else if (Choose==0) //Close Calculator
				System.exit(0);
		}
		else {
			System.out.println("Choose 0/1/2");
			Menu();
		}
	}
	public static void DecToHex() { //10->16

		System.out.print("Enter a decimal number: ");
		Scanner input = new Scanner(System.in);
		if (input.hasNextInt()) { //check for int
			int decNumber = input.nextInt();
			String hexResult = ""; 
			char[] hexDigits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; //Digits for Basic 16
			while(decNumber > 0) { 
				int remainder = decNumber % 16; // calculate remainder
				hexResult = hexDigits[remainder] + hexResult; //add remainder to the string 
				decNumber /= 16; // divide by the desired base
			}
			System.out.println("Hexadecimal number: " + hexResult);
			Menu();
		}
		else {
			System.out.println("Wrong Choice! Choose a decimal number");
			DecToHex();
		}
	}

	public static void HexToDec() { // 16->10
		Scanner input = new Scanner(System.in);
		System.out.print("Enter a hexadecimal number: ");
		String hex = input.nextLine(); //input
		int decimalNumber = 0; 
		int pow = 0;

		for(int i = hex.length() - 1; i >= 0; i--) { //starting from the right char
			char hexChar = hex.charAt(i); 
			int hexValue = CharValue(hexChar);
			if (hexValue==0) {// If the character is not set to a hexadecimal base
				System.out.println("Wrong char! Choose A,B,C,D,E,F and digits");
				HexToDec();
			}
			decimalNumber += hexValue * Math.pow(16, pow);//calculate decimal value
			pow++;
		}
		System.out.println("Decimal equivalent: " + decimalNumber);
		Menu();
	}

	public static int CharValue(char ch) {
		if(ch >= '0' && ch <= '9') { //subtraction of letter value (ascii) 
			return ch - '0';   // return the difference value 
		}
		else if(ch >= 'A' && ch <= 'F') {  //subtraction of letter value (ascii)
			return ch - 'A' + 10; // return the difference value 
		}
		else {
			return 0;
		}
	}
}
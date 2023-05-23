import java.util.Scanner;
public class EX1 {
	public static void main(String[] args) {		
		Scanner sc = new Scanner(System.in);
		int choice;
		//menu	
		do {
			System.out.println("Hello, what would you like to do in our calculator? \n 0. exit"
					+ " \n 1. convert from decimal to hexadecimal \n 2. convert from hexadecimal to decimal ");
			choice = sc.nextInt();
			if (choice == 0 ) {
				System.out.println("Bye");
				break;
			}
			if (choice == 1 ) { //from dec to hex
				System.out.print("please insert decimal input: ");
				String input;
				do {
					input = sc.nextLine();}
				while (input.length()==0);
				input = checkInput(input); //validation
				int decimal = checkInputDec(input);
				String hexadecimal = ""; //start the return string which we will add numbers to

				while(decimal > 0) {// as long as the decimal is not 0 keep dividing by 16
					int remain = decimal % 16;
					if(remain < 10) {
						hexadecimal = remain + hexadecimal;
					} else {
						hexadecimal = (char)(remain + 55)+hexadecimal;// add the ASCII value 
					}
					decimal = decimal/ 16;
				}
				System.out.println("the Hexadecimal is: " + hexadecimal);

			}
			else if (choice == 2 ){//from dec to hex

				System.out.print("Enter a hexadecimal number: ");
				String input = "";
				do {
					input = sc.nextLine();}
				while (input.length()==0);
				input = checkInput(input);
				int decimalNumber = 0;
				int power = 0; //initial power
				for (int i = input.length() - 1; i >= 0; i--) {//doing the converting
					char c = input.charAt(i);
					int digit = Character.isDigit(c) ? c - '0' : c - 'A' + 10;
					decimalNumber += digit * Math.pow(16, power); //the return value is added to the string
					power++;
				}
				System.out.println("The decimal is: " + decimalNumber);
			}
			else{
				System.out.println("invalid");
			} 
		}
		while(choice !=0); 
	}
	private static String checkInput(String input) { //validation

		Scanner sc = new Scanner(System.in);

		boolean isValid = false;
		do {
			if (!input.matches("[0-9A-F]+")) {
				System.out.print("Enter a hexadecimal number: ");
				input = sc.nextLine();
			} else {
				isValid = true;
			}
		}
		while (!isValid); 
		return input;
	}
	private static int checkInputDec(String  decimal) {
		String StringDec= decimal;
		Scanner sc = new Scanner(System.in);
		boolean isValid = false;
		do {
			if (!StringDec.matches("[0-9]+")) {
				System.out.print("Enter a decimal number: ");
				StringDec = sc.nextLine();
			} else {
				isValid = true;
			}
		}
		while (!isValid); 
		return Integer.parseInt(StringDec);
	}
}











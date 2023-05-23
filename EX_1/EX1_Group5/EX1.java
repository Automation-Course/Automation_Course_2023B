import java.util.*;  

public class EX1 {

	public static void main(String[] args)  {
		try {
			System.out.println("To start the conversion please enter 1:");
			Scanner sc2 = new Scanner(System.in);  
			int runConversion = sc2.nextInt();
			while (runConversion == 1) {
				System.out.println("Please insert the Base you want convert from: (10 or 16)");// select current base 
				Scanner sc = new Scanner(System.in);  
				int convertFrom = sc.nextInt();
				if (convertFrom == 10 || convertFrom == 16) { // if the base is valid 
					System.out.println("Please insert the number you want to convert:");// get number to convert
					Scanner sc1 = new Scanner(System.in);    
					String convertNum = sc1.next();
					if (checkValidNumber(convertNum, convertFrom)) { // gets the base and number and convert them
						System.out.print("The number after conversion is: ");
						if (convertFrom == 10) {
							System.out.println(toSixTeen(convertNum)); // send to function
						}
						if (convertFrom == 16) {
							System.out.println(toTen(convertNum));// send to function
						}
					}
					else {
						System.out.println("The number you insert is not valid!");
					}
				}
				else {
					System.out.println("The base you insert is not valid!");
				}
				System.out.println("To convert another number please enter 1");
				Scanner sc4 = new Scanner(System.in);
				runConversion = sc4.nextInt();

			}
			System.out.println("please insert you feedback between 1-5 (1-lower, 5 - higher)");
			Scanner sc3 = new Scanner(System.in);    
			int feedback = sc3.nextInt();
			System.out.println("Thank you! :-)");
		} catch (Throwable exc) {
			System.out.println("The input is not valid!");
		}
	}

	public static String toSixTeen(String NumberConv) { // to base 16
		String output = new String();
		int temp = Integer.parseInt(NumberConv);// convert string to integer
		while (temp>15) { // there is still a possibility to get a whole number when divided by 16
			int temp1 = temp%16; // get the modulu
			temp = temp/16; // get the whole number
			output = toLetters(temp1) + output ; // adding the whole answer
		}
		output = toLetters(temp) + output; 
		return output;
	}

	public static char toLetters(int temp) { // convert numbers to letters
		if (temp < 10) {
			return (char)(temp+48);
		}
		else {
			return (char)(temp+55);
		}
	}

	public static int toTen(String NumberConv) { // convert the number from base 16 to base 10
		int output = 0;
		for (int i=0; i<NumberConv.length(); i++) {
			int Temp2 = convertToInt(NumberConv.charAt(i))*((int)Math.pow(16, (NumberConv.length()-1-i)));
			output += Temp2;
		}
		return output;
	}

	public static int convertToInt(char Temp) { // convert each char from the input to int
		if (Temp > 47 && Temp < 58) { //by it ascii value
			return (Temp-48);
		}
		return (Temp-55); //by it ascii value
	}

	public static boolean checkValidNumber(String Num, int base) { // check if the input number is valid according to it base
		if (base == 10) {
			for (int i=0; i<Num.length(); i++) {
				if (Num.charAt(i) < 48 || Num.charAt(i) > 57) { //by it ascii value
					return false;
				}
			}
			return true;
		}
		if (base == 16) {
			for (int i=0; i<Num.length(); i++) { //by it ascii value
				if (Num.charAt(i) < 48) {
					return false;
				}
				if (Num.charAt(i) > 57 && Num.charAt(i) < 65) {
					return false;
				}
				if (Num.charAt(i) >  70) {
					return false;
				}
			}
			return true;
		}
		else return false;
	}
}

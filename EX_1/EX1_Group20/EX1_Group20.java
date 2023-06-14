import java.util.Scanner;
public class EX1 {
	public static Scanner reader = new Scanner(System.in);
	public static boolean checkBase(String base) {
		if(base.equals("10") || base.equals("16")) { 
			return true;
		}
		return false;
	}
	public static boolean isDecimal(String number) {
		for (int i = 0; i < number.length(); i++) {
	        char c = number.charAt(i);
	        if (!Character.isDigit(c)) {
	            // The character is not a valid decimal character
	            return false;
	        }
	    }
		return true;
	}
	public static boolean isHexadecimal(String s) {
	    // First, check if the string contains only valid hexadecimal characters
	    for (int i = 0; i < s.length(); i++) {
	        char c = s.charAt(i);
	        if (!Character.isDigit(c) && (c < 'A' || c > 'F') && (c < 'a' || c > 'f')) {
	            // The character is not a valid hexadecimal character
	            return false;
	        }
	    }
	    // All checks have passed, the string is a valid hexadecimal number
	    return true;
	}
	public static String convertRestToChar(int number) {
		if(number >= 0 && number <= 9)
			return String.valueOf(number);
		else if(number == 10)
			return "A";
		else if(number == 11)
			return "B";
		else if(number == 12)
			return "C";
		else if(number == 13)
			return "D";
		else if(number == 14)
			return "E";
		else
			return "F";
	}
	//10 -->16
	public static String decimalToHexcadcimal(int number) {
		String ans = "";
		while(number != 0) {
			ans = convertRestToChar(number%16)+ans;
			number = number/16;
		}
		return ans;
	}
	public static int hexCharToInt(char c) {
	    if (c >= '0' && c <= '9')
	        return c - '0';
	    return c - 'A' + 10;
	}
	//16-->10
	public static int hexcadcimalToDecimal(String number) {
		int ans = 0;
		int size = number.length();
		int square = size-1;
		int index = 0;
		int num = 0;
		while(index < size) {
			num = hexCharToInt(number.charAt(index));
			ans = ans + num* (int) Math.pow(16,square);
			index = index + 1;
			square = square - 1;
		}
		return ans;
	}
	public static String toUpperCaseHex(String hex) {
	    StringBuilder sb = new StringBuilder(hex.length());
	    for (int i = 0; i < hex.length(); i++) {
	        char c = hex.charAt(i);
	        if (c >= 'a' && c <= 'f') {
	            c = Character.toUpperCase(c);
	        }
	        sb.append(c);
	    }
	    return sb.toString();
	}

	public static void main (String[]args) {
		
	String end = "1";
	System.out.println("Hello, this program can convert num from base 10 to 16 and from base 16 to 10.");
	while (!end.equals("0")) {
		System.out.println("if you would like to transfer a number from 10 to 16 insert 16.");
		System.out.println("if you would like to transfer a number from 16 to 10 insert 10.");

		String base = reader.next();
		while(!checkBase(base)) {
			System.out.println("base is not valid. base should be 10 or 16");
			base = reader.next();
		}
		if(base.equals("16")) {
			System.out.println("Hello, please insert the number in base 10");
			String number10 = reader.next();
			while(!isDecimal(number10)) {
				System.out.println(number10+" is not valid. number should be in base 10 [0-9]");
				number10 = reader.next();
			}
			System.out.println(decimalToHexcadcimal(Integer.parseInt(number10)));
		}
		else if(base.equals("10")) {
			System.out.println("Hello, please insert the number in base 16");
			String number16 = reader.next();
			while(!isHexadecimal(number16)) {
				System.out.println("please insert a valid number in base 16");
				number16 = reader.next();			
			}
			System.out.println(hexcadcimalToDecimal(toUpperCaseHex(number16)));
		}
		System.out.println(
				"to end the program entern 0, to do another calculation press any button");
		
		end =reader.next();
		}
	System.out.println("Bye Bye !");
	}
}

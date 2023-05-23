import java.util.Scanner;

public class BaseConverter {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		while(true) {
			//menu
			System.out.println("Choose a option: ");
			System.out.println("1. Convert from base 10 to base 16:");
			System.out.println("2. Convert from base 16 to base 10:");
			System.out.println("3. Exit");
			String menuInput = scanner.nextLine();
			//if user enter wrong input
			if(!menuInput.equals("1") && !menuInput.equals("2") && !menuInput.equals("3")) {
				System.out.println("Enter valid input - 1/2/3");
				continue;
			}
			//if user choose 1 from menu
			if(menuInput.equals("1")) {
				System.out.print("Enter the number: ");
				String num = scanner.nextLine();
				if(!isStringInt(num)) {
					System.out.println("Enter valid input");
					continue;
				}
				int num1 = Integer.parseInt(num);
				ConvertToBase16(num1);
			}
			//if user choose 2 from menu
			if(menuInput.equals("2")) {
				System.out.print("Enter the number: ");
				String input = scanner.nextLine();
				if(!isStringHex(input)) {
					System.out.println("Enter valid input");
					continue;
				}
				hexToDecimal(input);
			}	
			//if user choose 3 from menu
			if(menuInput.equals("3")) {
				System.out.println("Bye!!");
				break; 
			}
		}
	}

	//function that convert number from base 10 to base 16
	public static void ConvertToBase16(int decimal) {
		if (decimal == 0) {
			System.out.println("0");;
		}
		String hex = "";
		while (decimal > 0) {
			int digit = decimal % 16;
			if (digit < 10) {
				hex = digit + hex;
			} else {
				hex = (char) ('A' + digit - 10) + hex;
			}
			decimal /= 16;
		}
		System.out.println(hex);
	}
	
	//function that convert number from base 16 to base 10
	public static void hexToDecimal(String hex) {
	    int decimal = 0;
	    for (int i = 0; i < hex.length(); i++) {
	        char c = hex.charAt(i);
	        int digit = Character.digit(c, 16);
	        decimal = decimal * 16 + digit;
	    }
	    System.out.println(decimal);
	}
	
	//function that check if string is number in base 10
	public static boolean isStringInt(String str) {
	    try {
	        Integer.parseInt(str);
	        return true;
	    } catch (NumberFormatException e) {
	        return false;
	    }
	}
	
	//function that check if string is number in base 16
	public static boolean isStringHex(String str) {
	    if (str == null || str.length() == 0) {
	        // String is null or empty
	        return false;
	    }
	    for (int i = 0; i < str.length(); i++) {
	        char c = str.charAt(i);
	        if (!Character.isDigit(c) && (c < 'A' || c > 'F') && (c < 'a' || c > 'f')) {
	            // Character is not a valid hexadecimal digit
	            return false;
	        }
	    }
	    return true;
	}
}

import java.util.Scanner;
public class ex1 {
	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		calculator();
	}

	// Convert Decimal (Base 10) to Hexadecimal (Base 16) 
	public static String base10_to_base16(int Decimal) {
		String digits = "0123456789ABCDEF";
		if (Decimal <= 0) return "0"; // if the input is negative return 0
		String answer = "";
		while (Decimal > 0) {
			int digit = Decimal % 16;  // remainder
			answer = digits.charAt(digit) + answer;  // add the remainder to string 
			Decimal = Decimal / 16;
		}
		return answer;
	}

	// Convert base 16 to base 10 
	public static long base16_to_base10(String hex) {
		long decimal = 0;
		hex= hex.toUpperCase(); //the function isn't case sensitive
		for (int i = 0; i < hex.length(); i++) {
			char hexChar = hex.charAt(i);
			long hexValue = 0;
			if (hexChar >= '0' && hexChar <= '9') {
				hexValue = hexChar - '0'; // save the difference between the values in ASCII table
			} else if (hexChar >= 'A' && hexChar <= 'F') {
				hexValue = hexChar - 'A' + 10;
			} else {
				System.out.println("the input contains digit out of hex range ");
				return 0; 
			}
			
			decimal = 16 * decimal + hexValue; // 16 is common factor , every digit is multiplied by 16 as many times its should 
		}
		return decimal;
	}

	// upper function
	public static  void calculator() {
		boolean run= true;
		while (run) {
			System.out.println("Hello, please choose which base you would like to transfer to ");
			System.out.println("from base 10 to 16, please enter 1");
			System.out.println("from base 16 to 10, please enter 2");
			int base = sc.nextInt();

			while ((base!=1)&&(base !=2)) {
				System.out.println("Sorry wrong input please try again");
				base = sc.nextInt();
			}

			if (base== 1) {
				System.out.println("Please enter number in base 10");
				int 	input= sc.nextInt();
				String answer= base10_to_base16(input);
				System.out.println(answer);
			}
			else {
				System.out.println("Please enter number in base 16");
				String s= sc.next();
				long ans= base16_to_base10(s);
				System.out.println(ans);
			}

			System.out.println("would you like to continue?");
			System.out.println("press no to exit or anything else to continue ");

			String running= sc.next();

			if (running.equals("no")){
				run= false;
				System.out.println("goodbye");
			}


		}
	}
}
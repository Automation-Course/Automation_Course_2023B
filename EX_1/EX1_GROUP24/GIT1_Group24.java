
	import java.util.Scanner;

	public class GIT1_Group24 {
		static Scanner sc = new Scanner(System.in);

		public static void main(String[] args) {
			Scanner scanner = new Scanner(System.in);
			boolean flag = true;
			while (flag) {
				
			// choose a conversion method 
			System.out.println("Choose a conversion:");
			System.out.println("1- decimal to hexadecimal");
			System.out.println("2- hexadecimal to decimal");
			System.out.println("3- exit");

			try {
				int choice = scanner.nextInt(); 			 
				
				if(choice == 1) {
					// decimal to hexadecimal	
					System.out.println("Choose a decimal value: ");
					int dec1 = scanner.nextInt();
					if (dec1>=0) {
					String hex = convertDecToHexa((int)dec1);
					System.out.println("Hexadecimal: " + hex);
					}
					else { 
						System.out.println("Negative input! please run the program again.");
						flag = false;	
					}
				}
				else if(choice == 2){
					// hexadecimal to decimal
					System.out.println("Choose a hexadecimal value: ");
					String hexadecimal = scanner.next();
					int dec2 = convertHexaToDec(hexadecimal);
					if (dec2==-1) {
						System.out.println("Invalid input! please run the program again.");
						flag = false;	
					}
					else
					System.out.println("Decimal form: " + dec2);
				}
				else if(choice == 3) {
					flag = false;
					System.out.println("Goodbye :)");

				}
			} catch (Exception exp) { 
				System.out.println("Invalid input! please run the program again.");
				flag = false;
			}
			}
		}

	// convert a given decimal integer value into a hexadecimal value
		public static String convertDecToHexa(int dec) {
			String hex = "";
			while (dec > 0) {
				int Sheherit = (int)dec % 16;
				if (Sheherit < 10) { // using numbers
	 				hex = Sheherit + hex;
				} else { // using letters
					char hexChar = (char) ('A' + Sheherit - 10);
					hex = hexChar + hex;
				}
				dec = (dec/16);
			}
			if (dec == 0)
				return ("0");
			return hex;	
		}

		// convert a given hexadecimal value into a decimal integer value
		public static int convertHexaToDec(String hexadecimal) {
			int dec2 = 0;
			int hezka = 0;
			for (int i = hexadecimal.length() - 1; i >= 0; i--) {
				char hex_Char = hexadecimal.charAt(i);
				if (hex_Char >= '0' && hex_Char <= '9') { //numbers
					dec2 += (hex_Char - '0') * Math.pow(16, hezka); 
				} else if (hex_Char >= 'A' && hex_Char <= 'F') { //capital Letters 
					dec2 += (hex_Char - 'A' + 10) * Math.pow(16, hezka);
				} else if (hex_Char >= 'a' && hex_Char <= 'f') { //letter case
					dec2 += (hex_Char - 'a' + 10) * Math.pow(16, hezka);
				}
				else return -1;
				hezka = hezka + 1;
			}
			return dec2;	
		}
}

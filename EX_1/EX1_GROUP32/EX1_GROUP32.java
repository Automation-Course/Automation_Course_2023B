package automation;
import java.util.Scanner;

public class automationEx1 {
	public static void main(String[] args) {
		Scanner myObj = new Scanner(System.in);
		menu();
		for(;;) {
			String option = myObj.nextLine(); //input desired option from the menu
			if(option.contains("3")) {
				System.out.print("Exiting");
				break;
			}
			else {

				for(;;) {
					if(!option.matches("[1-3]+")) {
						System.out.print("Wrong input! enter a correct number: ");
						break;
					}
					else {

						switch (option) {
						case "1":
							System.out.println("to convert from Hex to Dec enter a number");
							String hex = myObj.nextLine();

							while(!hex.matches("[0-9A-Fa-f]+")) {
								System.out.println("Invalid input. Only hexadecimal characters (0-9, A-F, a-f) are allowed. Try Again");
								hex = myObj.nextLine();
							}
							System.out.println("the hexadecimal number is: " + hexToDec(hex));
							menu();		
							break;
						case "2":
							System.out.println("to convert from dec to hex enter a number");
							String dec = myObj.nextLine();
							while(!dec.matches("[0-9]+")) {
								System.out.println("Invalid input. Only decimal characters (0-9) are allowed. Try Again");
								dec = myObj.nextLine();
							}
							int dec1 = Integer.parseInt(dec);
							System.out.println("The decimal number is: " + decToHex(dec1));   
							menu();		
							break;
						}
						break;
					}
				}
			}
		}
	}
	public static int hexToDec(String hex){
		int res = 0;
		hex = hex.toUpperCase(); 
		String digits = "0123456789ABCDEF";
		for (int i = 0; i < hex.length(); i++)  {
			char c = hex.charAt(i);
			int d = digits.indexOf(c);
			res = 16*res + d;  //result
		} // sums every single digit from the correct base 
		return res;
	}
	public static String decToHex(int dec){
		String res = "";
		int rem;
		char hexchars[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
		while(dec>0) {
			rem=dec%16; //remaining
			res=hexchars[rem]+res; //result
			dec=dec/16;
		}  // divides the hexadecimal number until there is no remaining
		return res;
	}
	public static void menu() {
		System.out.println("Welcome to Hex/Dec converter: ");
		System.out.println("1. Convert from Hex to Dec");
		System.out.println("2. Convert from Dec to Hex");
		System.out.println("3. Exit");
		System.out.print("Enter a number: ");
	} //Method that prints the menu

}
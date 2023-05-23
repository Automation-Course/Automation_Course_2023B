package aoto;
import java.util.*;
public class aoto {
	static Scanner reader= new Scanner(System.in); 
	public static void main(String[] args) {
		System.out.println(" enter 1 if you want to convert from base 16 to base 10 " +
															'\n'+" enter 2 if you want to convert from base 10 to base 16 "); 
		int choose= reader.nextInt(); //by this function the user can choose from witch base he wants to convert
		if (choose==1 ) {//call the function that convert from base 16 to base 10 
			reader.nextLine();
			System.out.println("enter base 16 number: ");	
			String number=reader.nextLine();
			System.out.println("the number in 10 base is: "+ sixteenTo10(number));
		}
		else if(choose==2) {//call the function that convert from base 10 to base 16 
			System.out.println("enter base 10 number: ");
			int decimalNumber=reader.nextInt();
			System.out.println("the number in 16 base is: "+ tento16(decimalNumber));
		} 
		else {//else 
			System.out.println("wrong number...please enter 1 or 2 ,play again");
		} 
	}
	public static int sixteenTo10(String hexNumber) {// this function convert the number in base 16 to base 10 
		int hezka = 1;
		int decimalNumber = 0;
		for (int i = hexNumber.length() - 1; i >= 0; i--) {// for each iteration we convert digit to its decimal value
			char hexDigit = hexNumber.charAt(i);
			int num = lettertonum(hexDigit);
			decimalNumber+= num *hezka;
			hezka *= 16;//multiplying it by 16
		}
		return decimalNumber;
	}

	public static int lettertonum(char hexDigit) {//give the ascii value 
		if (hexDigit >= '0' && hexDigit <= '9') {
			return hexDigit - '0';
		} else if (hexDigit >= 'A' && hexDigit <= 'F') {
			return hexDigit - 'A' + 10;
		} else  {
			return hexDigit - 'a' + 10;
		}
	}





	public static String tento16(int decimalNumber) {// this function convert the number in base 10 to base 16
		String hexNumber = new String();
		while (decimalNumber > 0) {
			int left = decimalNumber % 16;
			char hexDigit;

			if (left >= 10) {
				hexDigit = (char)('A' + left - 10);
			} else {
				hexDigit = (char)('0' +left);
			}
			hexNumber=hexDigit+hexNumber;
			decimalNumber /= 16;
		}
		return hexNumber.toString();
	}
}
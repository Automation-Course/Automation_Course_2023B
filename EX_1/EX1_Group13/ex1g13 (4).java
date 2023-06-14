package auto;

import java.util.Scanner;
public class ex1g13 {

	static Scanner sc = new Scanner(System.in);


	public static int hexToDecimal(String hexnumber){ 
		String hstring = "0123456789ABCDEF";  
		int num = 0;  
		for (int i = 0; i < hexnumber.length(); i++)  
		{  
			char ch = hexnumber.charAt(i);  
			int n = hstring.indexOf(ch);  
			num = 16*num + n;  
		}  
		return num;  
	}  

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("choose base : ");
		System.out.println("1- HexaDecimal to Decimal");
		System.out.println( "2 - Decimal to HexaDecimal");
		int a = sc.nextInt(); 
		if(a ==1) {

			boolean flag = false;;
			String hexnum = "";

			do {
				System.out.println("Please enter a hexadecimal number:");
				hexnum = scanner.nextLine();
			} 
			while (!hexnum.matches("[0-9A-F]+"));
			hexToDecimal(hexnum);
			System.out.println("Decimal equivalent  "+hexToDecimal(hexnum));  
		}

		else {

			int x = 0;
			boolean validInput = false;
			while (!validInput) {
				try {
					System.out.println("Enter a number to convert");
					x = sc.nextInt();
					validInput = true;
				} catch (Exception e) {
					System.out.println("Invalid input. Please enter an decimal number");
					sc.nextLine(); 
				}
			}
			int d=0;	
			int [] number= new int [10];
			int index =0;
			while(x!=0)
			{

				d=x%16;
				x=x/16;
				number [index]=d;
				index++; 
			}
			if(number[0] < 0)   
				System.out.print("-");

			for (int j = index - 1; j >= 0; j--) {
				if(number[j] > 0)  
				{ if (number[j] > 9)
					System.out.print((char)(55 + number[j]));
				else
					System.out.print(number[j]);
				}
				if(number[j] < 0)   {

					if (number[j] <- 9)
						System.out.print((char)(55 + number[j]*(-1)));
					else
						System.out.print(number[j]*(-1));
				}
			}
		}

	}
}
import java.util.Scanner;
public class Ex1 {
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args){
		String InputNumber="";
		printMenu();
		int input = getUserInput();

		while (input != 3) { // exit code
			switch(input) {
			case 1: //10 to 16
				 InputNumber=InputNumber(10);
				 System.out.println("your number is: "+InputNumber);
			printMenu();// print main menu
			break;
			case 2: //16 to 10
				 InputNumber=InputNumber(16);
				 System.out.println("your number is: "+InputNumber);
			printMenu();// print main menu
			break;
			default:
				System.out.print("Wrong input! enter another number: ");
				break;
			}//  switch- choose (1-3)
			input = getUserInput();// 

		}//  while - for the main menu

		System.out.print("Exiting");
		sc.close();		
			}


		private static String InputNumber(int base) { // ask from the player to choose his number he want to calc
			String number;
			String answer="";
			boolean flag=false;

			if (base== 10) {
				System.out.println("Choose your number: ");
				number= sc.next();
				answer=from10to16(number);
			}
			if (base== 16)
			{
				System.out.println("Choose your number: ");
				number= sc.next();
				do {
					if (!number.matches("[0-9]+"))
					{
						if(!number.matches("[^g-zG-Z]*")) {
							System.out.println("Please enter only digits or letters between A-F  ");
							number= sc.next(); 
						}
						else flag=true;
					}
					else flag=true;
				}while(flag== false); 
				answer=from16to10(number);
			}
			return answer;
		}


		public static String from10to16(String number) {
			int i = 0;
			String answer="";
			while(i < number.length()){			// check if the input is valid
				if((number.charAt(i) <= 57 && number.charAt(i) >= 48))
					i++;
				else{
					System.out.println("wrong input. insert characters between 0 and 9");
					number= sc.next();
					answer=from10to16(number); //user is returning to write a number
				}	
			}
			String result = "";
			long number2 = Long.parseLong(number); //change string to int
			if (number2==0)//if the user enter 0 
			{
				result="0";
			}
			while(number2 > 0){
				long modul = number2%16; //dividing the number by hex base with module
				if(modul<10){
					result = modul+result;
				}
				else{
					result = (char) (modul + 55) + result; //changing to ascii
				}
				number2 = number2/16;
			}
			return result;
		}


		public static String from16to10(String number) {
			int j=0;
			int length= number.length();
			int outPut=0;
			for (int i= length-1; i>=0; i--) {

				char Moveto16 = number.charAt(i);
				if(!Character.isDigit(Moveto16)){
					if (Moveto16=='A'||Moveto16=='a')
					{
						outPut+=10*Math.pow(16,j);
					}
					if (Moveto16=='B'||Moveto16=='b')
					{
						outPut+=11*Math.pow(16,j);
					}
					if (Moveto16=='C'||Moveto16=='c')
						outPut+=12*Math.pow(16,j);
					if (Moveto16=='D'||Moveto16=='d')
						outPut+=13*Math.pow(16,j);
					if (Moveto16=='E'||Moveto16=='e')
						outPut+=14*Math.pow(16,j);
					if (Moveto16=='F'||Moveto16=='f')
						outPut+=15*Math.pow(16,j);
				}
				else{
					outPut+=(Moveto16-'0')*Math.pow(16,j);
				}
				j++;
			}
			return Integer.toString(outPut);
		}


		// main menu
		public static void printMenu() {
			System.out.println("Welcome Calculator: ");
			System.out.println("1. calculate from 10 base to 16 base\r\n"
					+ "2. calculate from 16 base to 10 base\r\n"
					+ "3.  Exit"
					);
			System.out.print("Enter a number: ");
		}

		public static int getUserInput() {
			int input= sc.nextInt();
			return input;
		}
	}
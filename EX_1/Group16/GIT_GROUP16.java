import java.util.Scanner;
import java.util.Vector;

public class GIT_GROUP16{
	static Scanner sc = new Scanner(System.in);

	public static String SmallLetter (String number)
	{ //Converts small letters to capital, provided they are in the range between 'a' and 'f'
		for(int i=0;i<number.length();i++)
		{
			char check = number.charAt(i);
			if((int)check<103 && (int)check>96) //The ASCII value of small letters in range 'a'-'f'
			{
				number = number.replace(check, (char)((int)check-32));
			}				
		}
		return number;
	}

	public static boolean ValidNum (String number) //Check whether the number is valid
	{
		for(int i=0;i<number.length();i++)
		{
			char check = number.charAt(i);
			if((int)check<48 || ((int)check>57 && (int)check<65) ||(int)check>70 || check==' ') //Range of ASCII for characters in range A-F and 0-9
				return false;
		}
		return true;
	}

	public static boolean WhetherBase10AndNumberBase16 (String number, int base) 
	//Check whether the user insert a number in hexadecimal base, and selected the option of transformation from decimal to hexadecimal base
	{
		if (base==1)
		{
			for(int i=0;i<number.length();i++)
			{
				char check = number.charAt(i);
				if((int)check>=65 && (int)check<=70)
					return true;
			}
		}
		return false;
	}

	public static int GetBase() //Function for receiving a transformation to convert from the user
	{
		System.out.println("from what base? ");
		System.out.println("choose 1 - from 10 to 16");
		System.out.println("choose 2 - from 16 to 10");
		int base = sc.nextInt();
		while((base!=1&&base!=2))
		{
			System.out.print("choose a valid option");
			base = sc.nextInt();
		}
		return base;
	}

	public static String GetNumber(String number) //Function for receiving a number from the user
	{
		System.out.println("Which number would you like to convert?");
		if (number == null)
			number = sc.nextLine();
		else 
		{	
			sc.nextLine();
			number = sc.nextLine();
		}
		number = SmallLetter(number);
		while (ValidNum(number)==false)
		{
			System.out.println("not a valid number");
			System.out.println("Which number would you like to convert?");			
			number = sc.nextLine();
			number = SmallLetter(number);
		}
		return number;
	}

	public static String from10to16(String number) { //Function for convert a number from decimal base to hexadecimal base
		int num=Integer.parseInt(number);
		String solution="";
		Vector<Integer> leftVec = new Vector<Integer>(); //Vector for the remainders of the division of the number
		while(num !=0) {
			leftVec.add(num%16);
			num = num/16;	
		}
		for (int i=leftVec.size()-1; i>=0; i--) { //Loop for assembling the number to hexadecimal base
			if (leftVec.elementAt(i) > 9 && leftVec.elementAt(i) < 16) {
				if (leftVec.elementAt(i) == 10) {
					solution += 'A';
				}
				else if (leftVec.elementAt(i) == 11) {
					solution += 'B';
				}
				else if (leftVec.elementAt(i) == 12) {
					solution += 'C';
				}
				else if (leftVec.elementAt(i) == 13) {
					solution += 'D';
				}
				else if (leftVec.elementAt(i) == 14) {
					solution += 'E';
				}
				else 
					solution += 'F';
			}
			else {
				solution += leftVec.elementAt(i);					
			}
		}	 					
		return solution;
	}

	public static String from16to10(String number) //Function for convert a number from hexadecimal base to decimal base
	{
		int NewNum=0;
		int NumSize=number.length();
		for(int i=0;i<number.length();i++)
		{
			NewNum=NewNum+ToInt(number.substring(i, i+1))*(int)Math.pow(16, NumSize-i-1);
		}
		return String.valueOf(NewNum);			
	}
	
	public static int ToInt(String x) //Function that convert capital letters A-F to numbers in hexadecimal base
	{
		if(x.equals("A"))
			return 10;
		else if(x.equals("B"))
			return 11;
		else if(x.equals("C"))
			return 12;
		else if(x.equals("D"))
			return 13;
		else if(x.equals("E"))
			return 14;
		else if(x.equals("F"))
			return 15;
		else 
			return Integer.parseInt(x);
	}


	public static void main (String [] args) 
	{
		boolean flag=true;
		String number = null;
		int base = 0;
		System.out.println("Welcome to our base conversion calculator! \nYou can convert numbers in decimal and hexadecimal base.");
		while(flag) {
			number = GetNumber(number);
			base = GetBase();
			while (WhetherBase10AndNumberBase16(number,base)) 
			{
				System.out.println("You insert a number in hexadecimal base, but choose a transformation from decimal to hexadecimal. \nSo this number in decimal base is:");
				base = 2; //Assuming the user wants the number in decimal base
			}
			if (base == 1)
				System.out.println(from10to16(number));
			else if (base == 2)
				System.out.println(from16to10(number));
			System.out.println("Whould you like to convert another number or exit? \nIf yes- choose 1, else- choose 0");
			int answer = sc.nextInt();
			while((answer!=1 && answer!=0))
			{
				System.out.println("choose a valid option");
				answer = sc.nextInt();
			}
			if(answer== 0) {
				flag=false;
				System.out.println("Thank you, Have a good day :)");
			}
		}
	}
}
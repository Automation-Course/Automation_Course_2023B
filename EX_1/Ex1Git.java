package ex1;

import java.util.Scanner;

public class Ex1Git {
	public static String NumberToLetter(int d) //function that Replace number to Letter
	{
		if(d==10)
			return "A";
		if(d==11)
			return "B";
		if(d==12)
			return "C";
		if(d==13)
			return "D";
		if(d==14)
			return "E";
		if(d==15)
			return "F";
		return Integer.toString(d);
	}
	public static int LetterToNum(String d) //function that Replace Letter to number
	{
		if(d.compareTo("A")==0)
			return 10 ;
		if(d.compareTo("B")==0)
			return 11;
		if(d.compareTo("C")==0)
			return 12;
		if(d.compareTo("D")==0)
			return 13;
		if(d.compareTo("E")==0)
			return 14;
		if(d.compareTo("F")==0)
			return 15;
		return Integer.parseInt(d);
		
	}
	public static double Dacimal (String s) //function that replace base 16 to base 10
	{
		int length= s.length()-1;
		int x;
		int i=0;
		double a=0;
		 while(length!=-1 ) 
		 {
			x=LetterToNum(s.substring(length,length+1));
			a=a+x*Math.pow(16,i);
			i++	;	
			 length-=1;
		 }
	
		 return a;
	}


	public static String Esroni(int Dig)//function that replace base 10 to base 16
	{
		int num1=0;
		int num2=Dig;
		String Final="";
		
		while(num2/16!=0)
		{
			num1=num2%16;
			Final=NumberToLetter(num1)+Final;
			num2=num2/16;
			
			
		}
		num1=num2%16;
		Final=NumberToLetter(num1)+Final;
		num2=num2/16;
	
		return Final;
	}

	public static void main(String[] args) {
		
		System.out.println("base colculatur: ");
		System.out.println("1. 10->16");
		System.out.println("2. 16->10");
		System.out.println("3. Exit");
		Scanner sc = new Scanner(System.in);
		int dig = sc.nextInt();
		
		while(dig!=3) //menu while run until EXit
		{
		if(dig==1)
		{
			System.out.println("enter your number:");
			Scanner sc1 = new Scanner(System.in);
			int dig1 = sc1.nextInt();
			String s=Esroni(dig1);
			System.out.println(s); 
		}
		else
		{
			System.out.println("enter your number:");
			Scanner sc1 = new Scanner(System.in);
			String dig1 = sc1.nextLine();
			double s=Dacimal(dig1);
			System.out.println(s); 
		}
		System.out.println("base colculatur: ");
		System.out.println("1. 10->16");
		System.out.println("2. 16->10");
		System.out.println("3. Exit");
		 sc = new Scanner(System.in);
		 dig = sc.nextInt();
	 }
	}

}

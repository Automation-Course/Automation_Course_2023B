package myNewPro;

import java.util.Vector;
import java.util.Scanner;
import java.lang.Math;

public class myFinalTask1 {

	static Scanner sc = new Scanner(System.in);
	static boolean NegativeFlag = false;

	public static void main(String[] args) {	
		int ans = Menu();
		 
		while (ans != 3){
		 ans = 	Menu(); 
		}
	}
		
 public static int Menu () {
	   
		System.out.println("Welcome to the CALCULATOR, please choose one of the options"); 
		System.out.println("1. to convert decimal number to hex");
		System.out.println("2. to convert hex number to decimal");
		System.out.println("3.for Exit");
		String ans=sc.next();

		if(ans.equals("1")) {
			DecToHex();
			return 1;
		} 
		else if(ans.equals("2")) {
				hexToDec();
			return 2;
		}else if (ans.equals("3")) {
			System.out.println("Goodbye :)");
			return 3;
		}
      else
		  System.out.println("invalid number!");
		    return 4; 
		 
	}
 
 

	public static void hexToDec() { // if the user want to change from hex to decimal
		System.out.println("please enter hex number :)");
		String hex=sc.next();
		int totAns=0;
		int x=0;

		hex = checkIfNegativeNumber(hex);

		for (int i = hex.length()-1; i >= 0; i--) {

			char Num=hex.charAt(x);
			int myNum = 0;
			if(Num=='A' || Num=='a') {
				myNum = 10;
			}else
				if(Num=='B'|| Num=='b') {
					myNum = 11;
				}else
					if(Num=='C' || Num=='c') {
						myNum = 12;
					}else
						if(Num=='D' || Num=='d') {
							myNum = 13;
						}else
							if(Num=='E' || Num=='e') {
								myNum = 14;
							}else
								if(Num=='F' || Num=='f') {
									myNum = 15;
								}else
								{
									myNum = Character.getNumericValue(Num);

									if(myNum>9 || myNum<0) { // check if the input is valid or invalid
										System.out.println("invalid number!");
										return;
									}
								}
			
			totAns= totAns + (int)(myNum*(Math.pow(16, i)));
			x= x + 1;
		}

		// if the input is valid
		if(NegativeFlag == true){
			System.out.print("-");
		}	

		System.out.println(totAns);

	}


	public static void DecToHex() { // if the user want to change from decimal to hex 
		System.out.println("please enter dec number :)");
		String dec=sc.next();

		dec = checkIfNegativeNumber(dec);

		for (int i = 0; i <=dec.length()-1; i++) { // check if the input is valid or invalid
			char IFNumCheck=dec.charAt(i);
			int myNum = Character.getNumericValue(IFNumCheck);
			if(myNum>9 || myNum<0) { 
				System.out.println("invalid number!");
				return;	
			}
		}
		// if the input is valid
		
		if(NegativeFlag == true){
			System.out.print("-");
		}	

		int x=Integer.parseInt(dec); 		
		Vector<Integer> v = new Vector<Integer>();

		while(x>16){
			v.add(x%16);
			x=x/16;
		}

		v.add(x);
		for(int i = v.size()-1 ; i >= 0; i--) {

			int y =  v.get(i);
			switch(y){
			case 10:
				System.out.print("A");
				break;
			case 11:
				System.out.print("B");
				break;
			case 12:
				System.out.print("C");
				break;
			case 13:
				System.out.print("D");
				break;
			case 14:
				System.out.print("E");
				break;
			case 15:
				System.out.print("F");
				break;
			default:
				System.out.print(y);

			}
		}
		System.out.println("");

	}


	
	public static String checkIfNegativeNumber(String Num) { // check If the Number it is Negative 
		char IFNumNegative=Num.charAt(0);
		if (IFNumNegative == '-') {
			NegativeFlag = true;
			return Num.substring(1);
		}	
		return Num;
	}
	

	
}







	



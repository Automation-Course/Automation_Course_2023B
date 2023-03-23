package group_27;
import java.util.*;

public class group_27 {
	public static Scanner sc=new Scanner(System.in);

	public static void main(String[] args) {
		boolean check0=false;
		boolean check1=false;
		boolean check2=false;
		int F=0;

		while (check0==false) {  //Input test. Between which bases do you want to switch?

			System.out.println("Transition from decimal to hexadecimal insert 1\r\n"
					+ "Transition from hexadecimal to decimal insert 2");

			F = sc.nextInt();//User Input

			if (F==1 || F==2)
				check0= true;
			else {
				System.out.println("Invalid choice!");
				check0= false;

			}
		}



		if (F==1) {  // switch 10-->16 

			long num=0;

			while (check2==false) { //Input test

				System.out.println("Enter a decimal number");

				num=IsLong();
				if (num>=0) {
				
						check2= true;
				}
				else {
						System.out.println("Invalid Num!");
						check2= false;
					}
				}
				//Transfer to base 16
				Vector<Long> v =new Vector<>();

				long temp=num;

				while (temp > 0) { //Calculating the remainder after dividing by 16
					long k=temp;
					v.add(temp%16);
					temp=(k-temp%16)/16;

				}
				//Converting the number to hexadecimal
				String ans="";  

				for(int i=v.size() ; i>0 ; i--) {

					long t = v.elementAt(i-1);
					String s="";

					if (t<10) {
						s=String.valueOf(t);
					}
					else {
						if (t==10)
							s="A";
						if (t==11)
							s="B";
						if (t==12)
							s="C";
						if (t==13)
							s="D";
						if (t==14)
							s="E";
						if (t==15)
							s="F";
					}
					ans=ans+s;
				}
				System.out.println("The number in hexadecimal is "+ans);

			}

			if (F==2) { // switch 16-->10

				String num= "0";

				while (check1==false) { //Input test

					System.out.println("Enter a hexadecimal number");

					num = sc.next();//User Input

					if (numIsValid(num))
						check1= true;
					else {
						System.out.println("Invalid Num!");
						check1= false;
					}
				}
				
				//Transfer to base 16

				int[] arr = new int[num.length()];

				
				for (int i = 0; i < num.length(); i++) {// Copy character by character into array
					int n=num.charAt(i);

					if (n>=48 && n<=57) { //Transferring numbers
						arr[i] = n-48;	
					}

					if (n>=65 && n<=70) { //Transferring letters
						arr[i]= n-55;
					}

				}	
				//Converting the number to decimal
				long ans=0;
				for (int i = 0 ; i < arr.length; i++) {

					int t=(int)(Math.pow(16,arr.length-1-i));
					ans=ans+arr[i]*t;
				}

				System.out.println("The number in decimal is "+ans);

			}


		}
	
	//Checking the input is a valid hexadecimal number (numbers 0-9 and letters A-F)

		public static boolean numIsValid(String num) {

			for (int i = 0; i < num.length(); i++) {
				int n=num.charAt(i);

				if (n>=48 && n<=57 || n>=65 && n<=70) {

				}

				else
					return false;	
			}
			return true;
		}
		
		//Checking that the input is a number and not a string
		public static long IsLong() {
			long num = 0;
	        boolean validInput = false;
	        
	        while (!validInput) {
	            if (sc.hasNextLong()) {
	                num = sc.nextLong();
	                validInput = true;
	            } else {
	                System.out.println("Invalid input! \r\n"
	                		+ "Enter a decimal number");
	                sc.next(); // clear the invalid input from the scanner
	            }
	        }
			return num;
			
		}




	}

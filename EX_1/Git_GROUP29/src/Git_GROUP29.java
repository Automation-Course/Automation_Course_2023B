
import java.util.Scanner;
import java.util.Vector;
public class Git_GROUP29 {

	public static long returnNumber(String str) { //function that return int in decimal
		long numAt10=0;  //represents number in decimal
		int len=str.length();  
		for (int i = 0; i < str.length(); i++) { //move on char in  string input 
			char c = str.charAt(i); //take digit or letter from the number
			int n=returnVal(c);// convert to int from char 
			if(n==-1) { // check if char is invalid
				System.out.println("Invalid input, please enter new number");
				return -1;
			}
			numAt10+=n*Math.pow(16, len-i-1); 	
		}
		return numAt10;
	}

	public static int returnVal(char c) { //convert to integer from char
		if (c >= '0' && c <= '9') 
			return  c - '0'; 
		else if (c=='A')
			return 10;
		else if (c=='B')
			return 11;
		else if (c=='C')
			return 12;
		else if (c=='D')
			return 13;
		else if (c=='E')
			return 14;
		else if (c=='F')
			return 15;
		return -1;

	}

	public static void main(String[] args) {
		System.out.println("Welcome! Please choose an option:");
		boolean finish=false;//true in case 0 to exit
		while (finish==false) {//print the menu  until option 0 is chosen
			System.out.print("0. End Program\r\n"
					+ "1. Convert from heximal to decimal\r\n"
					+ "2. Convert from decimal to heximal\r\n");
			Scanner sc = new Scanner(System.in) ; //input from user
			String opt=sc.next();
			while(opt.compareTo("0")<0 || opt.compareTo("2")>0) { //check input is valid
				System.out.print("Invalid input\r\n"
						+ "0. End Program\r\n"
						+ "1. Convert from heximal to decimal\r\n"
						+ "2. Convert from decimal to heximal\r\n");
				opt=sc.next();
			}
			if(opt.equals("0")) { //finish
				System.out.print("See you!");
				finish=true; //so the menu wont be printed again
				break;// 0
			}
			else if(opt.equals("1")) { //Convert from heximal to decimal
				System.out.println("please enter heximal number");
				Scanner sc1 = new Scanner(System.in) ;
				String str=sc1.next();
				long number=returnNumber(str); //convert to decimal, if the input is not valid return -1
				while(number==-1) { //if not valid -take new input from user 
					str=sc1.next();
					number=returnNumber(str);
				}
				System.out.println("The number in decimal is:"+number);
			}

			else if(opt.equals("2")) { // Convert from decimal to heximal
				System.out.println("please enter decimal number");
				Scanner sc1 = new Scanner(System.in) ;
				String st=sc1.next();

				while(!st.matches("[0-9]+")) { //check if  input is valid
					System.out.println("Invalid input, please enter only digits");
					st=sc1.next();
				}
				String ret=new String();
				Vector <String> v= new Vector<> ();

				long s,n; //n-integer  s-division remainder
				n= Long.parseLong(st); //casting to long
				while(n!=0) { 
					s=n%16; 
					n=n/16;
					if(s==10) //convert 10-15 to A-F and insert to vector
						v.add("A");
					else if(s==11)
						v.add("B");
					else if(s==12)
						v.add("C");
					else if(s==13)
						v.add("D");
					else if (s==14)
						v.add("E");
					else if(s==15)
						v.add("F");
					else v.add(String.valueOf(s));
				}
				for (int i= v.size()-1; i>=0; i--) { //add in reverse order
					ret=ret+v.elementAt(i);
				}
				System.out.println("The number in heximal is:"+ret);

			}
		}
	}
}


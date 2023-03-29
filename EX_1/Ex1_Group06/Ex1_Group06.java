

import java.util.Scanner;

public class Ex1_Group06{
	public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
       
       boolean go=false; 
       while(!go) {     // loop for all of the code
    	   
    	   
    	int option=0;  // user can choose option for converting
        System.out.println("type 1 for converting decimal number to hexadecimal  ");
        System.out.println("type 2 for converting hexadecimal number to decimal  ");
        System.out.println("your option:  "); 
        try {
         option=scanner.nextInt();  // input option
        }
        catch (Exception e) {    // error in input
      	  scanner.next();   //clears scanner
        }
        
        if (option!=1 && option!=2) { // error in input
        	
       	 System.out.println("wrong option choose again ");
       }
       
        
        if (option==1) { //option 1 : converting decimal number to hexadecimal 
        System.out.println("Enter a decimal number to convert to hexadecimal: ");
        
        long decimal; 
        
        boolean success1 = false; // for while loop
        while (!success1) {
          try {
        	 decimal = scanner.nextLong();  // user input decimal
         	 String hexadecimal = Ex1.Esroni(decimal);  //sends to function that replace base 10 to base 16
         	 System.out.println("The equivalent hexadecimal value is: " + hexadecimal);
            success1 = true; //ends while
          }
          catch (Exception e) {	// prevents from user to enter input that is not type long	
        	  System.out.println("wrong number, please Enter a decimal number between 0 and 9223372036854775807: ");
        	 scanner.next();   //clears scanner
               }    
            }   
     
         } // if 1
        
        
        if (option==2) { //option=2 : converting hexadecimal number to decimal
        System.out.println();
        System.out.println("Enter a hexadecimal number to convert to decimal: ");
        boolean success2 = false; // for while loop
        while (!success2) {
        try {
            String hexString = scanner.next(); // user input hexadecimal
            long decimalValue = Ex1.Decimal(hexString); //sends to function that replaces base 16 to base 10
            System.out.println("The equivalent decimal value is: " + decimalValue);
            success2=true; // ends while
        }
        catch(Exception e) { // prevents from user to enter wrong input	
        	 System.out.println("wrong number, please Enter a hexadecimal number between 0 and 7FFFFFFFFFFFFFFF: ");
       	  scanner.next();   //clears scanner
  
              }
          } //while
            
             System.out.println(); 
             
        }// if 2
       
        System.out.println(); 
        System.out.println();
        
       } //while go
       
    } // main
	
	
	
	public static String NumberToLetter(long d){ //Replace number to letters
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
		return String. valueOf(d);
		}	
	
	public static int LetterToNum(String d) { //Replace Letter to number		
	if(d.compareTo("A")==0 || d.compareTo("a")==0 )			
		return 10 ;		
	if(d.compareTo("B")==0  || d.compareTo("b")==0 )			
		return 11;		
	if(d.compareTo("C")==0  || d.compareTo("c")==0)			
		return 12;		
	if(d.compareTo("D")==0  || d.compareTo("d")==0)			
		return 13;		
	if(d.compareTo("E")==0  || d.compareTo("e")==0)			
		return 14;		
	if(d.compareTo("F")==0  || d.compareTo("f")==0)			
		return 15;		
	return Integer.parseInt(d);
	}
	
	public static long Decimal(String s) {//function that replaces base 16 to base 10
		int length= s.length()-1;
		int x;
		int i=0;
		long a=0;
		while(length!=-1 ){			
			x=LetterToNum(s.substring(length,length+1));			
			a=(long) (a+x*Math.pow(16,i));			
			i++	;				
			length-=1;	
		}			
		return a;
	} 
	
	public static String Esroni(long decimal){ //function that replaces base 10 to base 16
		long num1=0;
		long num2=decimal;
		String Final="";
		while(num2/16!=0) {
			num1=num2%16;
			Final=NumberToLetter(num1)+Final;
			num2=num2/16;
		}
		num1=num2%16;
		Final=NumberToLetter(num1)+Final;
		num2=num2/16;
		return Final;
	}
}
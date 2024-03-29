import java.util.Scanner;

public class Building_aCalculator {

	public static void main(String[] args) {
		Scanner conversion=new Scanner(System.in);
		boolean Continue=true;   //A condition to continue the loop.	
        while (Continue ==true) {
        	System.out.println("To convert a number from base 10 to base 16, enter '1'.\r\n"
    				+ "To convert a number from base 16 to base 10, enter '2'.\r\n"
    				+ "If you want to stop, enter '3'.");
    		
    		int Type_ofConversion =conversion.nextInt();
    		
    		if (Type_ofConversion ==1) {   //To convert a number from base 10 to base 16.
    			System.out.println("Enter a decimal number.");
            	double numberTo_Convert =conversion.nextDouble();
            	String number_Converted = FunConvert_decimalTo_hexadecimal(numberTo_Convert);
            	System.out.println("The number value after conversion is:" + number_Converted);
            	System.out.println("------------------------------------------------------------------------------------------------------------------------------");
    		    System.out.println();
    		}
    		
            if (Type_ofConversion ==2) {   //To convert a number from base 16 to base 10.
            	System.out.println("enter hexadecimal number.");
            	String numberTo_Convert =conversion.next();
            	double number_Converted = FunConvert_hexadecimalTO_decimal(numberTo_Convert);
            	System.out.println("The number value after conversion is:" + number_Converted);    
            	System.out.println("------------------------------------------------------------------------------------------------------------------------------");
    		    System.out.println();
            }
            
            if(Type_ofConversion==3) {   //If you want to stop.
            	Continue=false;
                System.out.println("You are the running rally, thank you. :)");
            }
            
            if(Type_ofConversion!=1&& Type_ofConversion!=2&& Type_ofConversion!=3) {
            	System.out.println("You chose a wrong number, choose another number. ");
            	System.out.println();
            }
        }
	}
	
		
	public static String FunConvert_decimalTo_hexadecimal (double Num) {   //A function that accepts a number in decimal base and returns a number in base 16.
		int integerNum= (int)Num;    //The integer part from the number.
		double fractionalNum= Num- integerNum;  //The fractional part of the number.
		String Number_Converted="";    //An array into which the numbers are inserted after the conversion.
		
		while(integerNum>0) {     //to Convert the integer part of a number.
			int division_remainder = integerNum %16;
			char char_num= charNum(division_remainder);
			Number_Converted =char_num + Number_Converted;
			integerNum = integerNum/16;
		}
		
		if(fractionalNum>0) {     //If the input is a fraction then the input is also a fraction.
			Number_Converted = Number_Converted+".";
		}
		
		int numberOf_decimals=0;
		
		while (fractionalNum >0 && numberOf_decimals <4) {    ////to Convert the fractional part of a number.
			fractionalNum=fractionalNum*16;
			int INTfractionalNum=(int)fractionalNum;
			char char_num= charNum(INTfractionalNum);
			Number_Converted += char_num;
			numberOf_decimals++;
			fractionalNum -=INTfractionalNum;

		}
		return Number_Converted;
	}
	
       public static char charNum (int divisionRemainder) {    //Replaces certain numbers with letters according to what is defined in base 16 numbers.
    	   
    	   if(divisionRemainder<10) {
   			return (char)(divisionRemainder+'0');
   		}else {
   			return (char)(divisionRemainder+'A'-10);
   		}
	}

	

	public static double FunConvert_hexadecimalTO_decimal (String Num) {    //A function that accepts a number in number in base 16  and returns a decimal base.
		int Power_ofDecimals=0;
		double Number_Converted=0.0;
		boolean Fractional =false;
		boolean Fractional_2=false;
		
    	for(int j=0;j<Num.length(); j++ ) {  //A function that returns the length of fractional part.
			char num_char1 =Num.charAt(j);
			if (num_char1=='.') {
				Fractional=true;
				continue;   // skip the current iteration of a loop and move on to the next iteration.
			}
			if(Fractional) {
				Power_ofDecimals++;
			}
	    }
    	
    	int Power_ofInteger;
    	if (is_decimal(Num)==true) {
		 Power_ofInteger=Num.length()-Power_ofDecimals-2;
    	}else {
    	 Power_ofInteger=Num.length()-Power_ofDecimals-1;
    	}
		
		for(int i=0;i<Num.length(); i++ ) {
			char num_char =Num.charAt(i);
			if (num_char=='.') {
				Fractional_2=true;
				continue;    // // skip the current iteration of a loop and move on to the next iteration.
			}
			int NormalNum =0;
			if(num_char >='0'&& num_char<='9') {
			   NormalNum=num_char-'0';                      //Decrease the integer value of "0" which is equal to 48 from the CHAR array.
			} else if(num_char >='A' && num_char <='F'){    //the letters 'A' to 'F' in hexadecimal notation represent decimal values 10 to 15, respectively.
				NormalNum=num_char-'A'+10;                  //Decrease the integer value of "A" which is equal to 65 from the CHAR array.
			}else if(num_char >='a' && num_char <='f'){    
				NormalNum=num_char-'a'+10;                  ////Decrease the integer value of "a" which is equal to 97 from the CHAR array.
			}else {
				throw new IllegalArgumentException ("Exception in value"+ num_char);
			}
			Number_Converted += NormalNum*Math.pow(16,Power_ofInteger);
        	Power_ofInteger--;
		}
		return Number_Converted;
	}
	
	public static boolean is_decimal(String Num) {   //A function that returns TRUE if the number is a fractional number.
		boolean Fractional =false;
		for(int j=0;j<Num.length(); j++ ) {
			char num_char =Num.charAt(j);
			if (num_char=='.') {
				Fractional=true;
			}
		}
		return Fractional;
	}
	
	
	
	
	

	
	
}


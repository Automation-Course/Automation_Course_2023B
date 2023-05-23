
import java.util.Scanner;
import java.lang.Math;

public class Calc2 {
	static Scanner sc = new Scanner (System.in);
	public static void main(String[] args) {
		menu();
	}
	public static void menu() {
		//printing the menu for the user
		System.out.println("0. End program");
		System.out.println("1. From 10 to 16");
		System.out.println("2. From 16 to 10");
		String input = sc.next(); //getting user's input
		if(input.equals("1")){
			TenToSixteen();
		}
		else if(input.equals("2")){
			SixteenToTen();
		}
		else if(input.equals("0")){
			System.out.println("Bye Bye!");
			return;
		}
		else{
			System.out.println("Wrong Input. please enter an integer between 0 and 2");
			menu();
		}
	}


public static void TenToSixteen(){
	System.out.println("Please enter a number in the base of 10:");
	String num = sc.next();
	int i = 0;
	// check if the input is valid
	while(i < num.length()){
		// ascii code check if the string is made of numbers only
		if((num.charAt(i) <= 57 && num.charAt(i) >= 48))
			i++;
		else{
			System.out.println("wrong input. insert characters between 0 and 9");
			TenToSixteen(); //user is returning to write a number
		}	
	}
	String result = "";
	long number = Long.parseLong(num); //changing the string received by the user to int
	if (number==0)//if the user enter 0 
	{
		result="0";
	}
	
	while(number > 0){
		long modul = number%16; //dividing the number by hex base with modul
		if(modul<10){
			result = modul+result;
		}
		else{
			result = (char) (modul + 55) + result; //changing to ascii
		}
		number = number/16;
	}
	System.out.println("your number is: "+result);
	menu();
}

public static void SixteenToTen(){
	System.out.println("Please enter a number in the base of 16:");
	String num = sc.next();
	int i = 0;
	while(i < num.length()){
		//checking that user entered only valid input
		if((num.charAt(i) <= 57 && num.charAt(i) >= 48) || (num.charAt(i) <= 70 && num.charAt(i) >= 65) )
			i++;
		else{
			System.out.println("wrong input. insert characters between 0 and 9 or capital letters between A and F");
			SixteenToTen(); //user is returning to write a number
		}	
	}
	i= num.length()-1;
	int j = 0;
	long result = 0;
	while(i >= 0){
		if((num.charAt(i) <= 57 && num.charAt(i) >= 48)){ //checking if it's a letter with hex base
		result += (num.charAt(i)-48)*Math.pow(16, j); //calculation for numbers 
		}
		else
			result += ((num.charAt(i))-55)*Math.pow(16, j); //returning the letter to a number with ascii reduction and then using power 
		i--;
		j++;
	}
	System.out.println("your number is: "+result);
	menu();
}
}

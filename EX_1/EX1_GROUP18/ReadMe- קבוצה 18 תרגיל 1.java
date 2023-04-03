import java.util.Scanner;

public class EX1_GROUP18 {

    // Method to convert a decimal number to hexadecimal
    public static String decimalToHeximal(int decimalNumber) {
        String hexword = "";
        while (decimalNumber > 0) {
            int remainder = decimalNumber % 16;
            if (remainder < 10) {
                hexword = remainder + hexword;
            } else {
                char hexChar = (char) ('A' + remainder - 10);
                hexword = hexChar + hexword;
            }
            decimalNumber /= 16;
        }
        return hexword;
    }

    // Method to convert a hexadecimal number to decimal
    public static int heximalToDecimal(String hexword) {
        int decimal = 0;
        for (int i = 0; i < hexword.length(); i++) {
            char hexChar = hexword.charAt(i);
            if (hexChar >= '0' && hexChar <= '9') {
                decimal = 16 * decimal + (hexChar - '0');
            } else if (hexChar >= 'A' && hexChar <= 'F') {
                decimal = 16 * decimal + (hexChar - 'A' + 10);
            } else if (hexChar >= 'a' && hexChar <= 'f') {
                decimal = 16 * decimal + (hexChar - 'a' + 10);
            } else {
                throw new IllegalArgumentException("Invalid hexadecimal string: " + hexword);
            }
        }
        return decimal;
    }

    public static boolean ishexdecimal(String hexnum) {
        if (hexnum.length() == 0)
            return false;
        for (int i = 0; i == hexnum.length(); i++) {
            if ((int) hexnum.charAt(i) > (int) 'F' || hexnum.charAt(i) < '0')
                return false;
        }
        return true;
    }

    // Main method for testing the conversion methods
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a mode number: 1- decimal to hexdecimal , 2 - hexdecimal to decimal  ");
        int modeNum = scanner.nextInt();
        while (modeNum != 1 && modeNum != 2) {
            System.out.print("Enter a mode number: 1- decimal to hexdecimal , 2 - hexdecimal to decimal  ");
            modeNum = scanner.nextInt();
        }
        if (modeNum == 1) {
            // Convert decimal to hexadecimal
            System.out.print("Enter a decimal number: ");
            int decimalNumber = scanner.nextInt();
            String hexword = decimalToHeximal(decimalNumber);
            System.out.println(decimalNumber + " in hexadecimal is " + hexword);
        }
        if (modeNum == 2) {
            // Convert hexadecimal to decimal
            System.out.print("Enter a hexadecimal number: ");
            String hexString = scanner.next();
            while (!ishexdecimal(hexString)) {
                System.out.print("wrong decimal number ,Enter a decimal number: ");
                hexString = scanner.next();
            }
            int decimal = heximalToDecimal(hexString);
            System.out.println(hexString + " in decimal is " + decimal);

            scanner.close();

        }
    }
}
import java.util.Scanner;

public class BaseConverter {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter your number: ");
            String numberInput = scanner.next();
            System.out.print("Enter the Base of the number, it can either be 10 or 16: ");
            String baseInput = scanner.next();

            boolean isInputValid = baseInput.equals("10") || baseInput.equals("16");

            if (!isInputValid) {
                System.out.println("Invalid base input. Please enter either 10 or 16.");
                continue;
            }

            int base = baseInput.equals("10") ? 10 : 16;

            if (base == 10) {
                boolean isDecimalNumber = true;
                for (char c : numberInput.toCharArray()) {
                    if (!(c >= '0' && c <= '9')) {
                        isDecimalNumber = false;
                        break;
                    }
                }

                if (!isDecimalNumber) {
                    System.out.println("Invalid decimal number. Please enter a valid decimal number.");
                    continue;
                }

                if (numberInput.startsWith("0")) {
                    System.out.println("Decimal numbers shouldn't start with 0. Try again.");
                    continue;
                }

                int number = 0;
                for (char c : numberInput.toCharArray()) {
                    number = number * 10 + (c - '0');
                }

                StringBuilder hexResult = new StringBuilder();
                char[] hexDigits = "0123456789ABCDEF".toCharArray();

                while (number > 0) {
                    hexResult.insert(0, hexDigits[number % 16]);
                    number /= 16;
                }

                System.out.println("The hexadecimal form of your number is:");
                System.out.println(hexResult);
            } else if (base == 16) {
                boolean isHexNumber = true;

                for (char c : numberInput.toCharArray()) {
                    if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))) {
                        isHexNumber = false;
                        break;
                    }
                }

                if (!isHexNumber) {
                    System.out.println("Invalid hexadecimal number. Please enter a valid hexadecimal number.");
                    continue;
                }

                if (numberInput.startsWith("0")) {
                    System.out.println("Hexadecimal numbers shouldn't start with 0. Try again.");
                    continue;
                }

                int decResult = 0;
                int multiplier = 1;

                for (int i = numberInput.length() - 1; i >= 0; i--) {
                    char c = numberInput.charAt(i);
                    int value;

                    if (c >= '0' && c <= '9') {
                        value = c - '0';
                    } else if (c >= 'A' && c <= 'F') {
                        value = c - 'A' + 10;
                    } else {
                        System.out.println("Unexpected character in hexadecimal number.");
                        continue;
                    }

                    decResult += value * multiplier;
                    multiplier *= 16;
                }

                System.out.println("The decimal form of your number is:");
                System.out.println(decResult);
            } else {
                System.out.println("Something went wrong, please Try again.");
            }
        }

    }

}
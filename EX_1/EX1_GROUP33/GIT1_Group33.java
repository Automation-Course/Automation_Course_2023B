import java.util.*;
public class GIT1_Group33 {
    static Scanner sc = new Scanner(System.in);
    // Creating Hexadecimal char array
    public static final char hexChars[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    // Creating Hexadecimal Binary dictionary
    public static HashMap<Character,String> hexBinDictionary =new HashMap<Character,String>();

    public static void setHexBinDic() {
        // Generates the Hexadecimal Binary dictionary
        hexBinDictionary.put('0', "0000");
        hexBinDictionary.put('1', "0001");
        hexBinDictionary.put('2', "0010");
        hexBinDictionary.put('3', "0011");
        hexBinDictionary.put('4', "0100");
        hexBinDictionary.put('5', "0101");
        hexBinDictionary.put('6', "0110");
        hexBinDictionary.put('7', "0111");
        hexBinDictionary.put('8', "1000");
        hexBinDictionary.put('9', "1001");
        hexBinDictionary.put('A', "1010");
        hexBinDictionary.put('B', "1011");
        hexBinDictionary.put('C', "1100");
        hexBinDictionary.put('D', "1101");
        hexBinDictionary.put('E', "1110");
        hexBinDictionary.put('F', "1111");
    }

    public static String DestoHex(int dec){
        //Converts a Decimal number to Hexadecimal number
        int rem;
        String hex="";
        while(dec>0)
        {
            rem=dec%16;
            hex=hexChars[rem]+hex;
            dec=dec/16;
        }
        if(hex == "")
            return "0";
        return hex;
    }

    public static String HexToBinary(String hex) {
        // Converging from Hexadecimal to Binary
        String bin = "";
        for (int i = 0; i < hex.length(); i++) {
            char x = hex.charAt(i);
            if(hexBinDictionary.containsKey(x)) {
                bin += hexBinDictionary.get(x);
            }
        }
        return bin;

    }
    public static int HexToDes(String hex){
        //Converts a Hexadecimal number to Decimal number
        hex = hex.toUpperCase();
        String bin = HexToBinary(hex);
        int des = 0;
        int i;
        for ( i = 0; i < bin.length(); i++)
        {
            char c = bin.charAt(i);
            if(c == '1') {
                des += (int) Math.pow(2, bin.length()-1-i);
            }
        }
        return des;
    }

    public static boolean desNumCheck(int num) {
        // Checking Decimal number validity
        if(num<0) {
            return false;
        }
        return true;
    }
    public static boolean hexNumCheck(String num) {
        // Checking Hexadecimal number validity
        num = num.toUpperCase();
        for (int i = 0; i < num.length(); i++) {
            char x = num.charAt(i);
            boolean exist = hexBinDictionary.containsKey(x);
            if(!exist) {
                return false;
            }
        }
        return true;

    }
    public static void main(String[] args) {// To run the calculator menu
        setHexBinDic();
        int choice;
        int num1;
        String num2;
        System.out.print("Welcome To ");
        do {
            System.out.println("Number Base Calculator\nPick a convertion:\n1. " +
                    "Decimal to Hexadecimal\n2. Hexadecimal to Decimal\n0. Exit");
            choice = sc.nextInt();
            switch(choice) {
                case 0:
                    break;
                case 1:
                    System.out.println("Enter a decimal number:");
                    num1 = sc.nextInt();
                    if(desNumCheck(num1)) {
                        System.out.println("Answer in Hexadecimal: "+DestoHex(num1));
                    }
                    else {
                        System.out.println("Invalid decimal number! Try again");
                    }
                    break;
                case 2:
                    System.out.println("Enter a Hexadecimal number:");
                    num2 = sc.next();
                    if(hexNumCheck(num2)) {
                        System.out.println("Answer in Decimal: "+HexToDes(num2));
                    }
                    else {
                        System.out.println("Invalid hexadecimal number! Try again");
                    }
                    break;
                default:
                    System.out.println("Invalid choice! Try again.");
            }
        }while(choice != 0);
    }
}
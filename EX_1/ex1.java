import java.util.Scanner;
import java.util.Vector;

public class ex1 {
    static Scanner sc = new Scanner(System.in);
    static int ScanNumber2;

    public static void main(String[] args) {
        int Choice;
        // do while - for the menu
        do{
            System.out.println("If you want to move from 10 to 16 press 1");
            System.out.println("If you want to move from 16 to 10 press 2");
            System.out.println("If you want to exit press -1");
            Choice = sc.nextInt();
            // if there is a wrong input
            while (Choice != 1 && Choice != 2 && Choice != -1) {
                System.out.println("Wrong input please insert again");
                Choice = sc.nextInt();
            }
            // choise 1
            if (Choice == 1) {
                System.out.println("Insert Number to convert to base 16");
                String Num = sc.next();
                while(!Num.matches("[0-9]+")){
                    System.out.println("wrong input, please insert only positive integer");
                    Num = sc.next();
                }
                String s = fromTenToSixteen(Integer.parseInt(Num));
                System.out.println(s);
            }
            // choise 2
            if (Choice ==2) {
                System.out.println("Insert Number on base 16 to convert to base 10");
                String s;
                    s = sc.next();
                    s = s.toUpperCase();
                    while (!isHexadecimal(s)) {
                        System.out.println("wrong input, please insert only positive numbers, digits 0-9 and A-F");
                        s = sc.next();
                    }
                    ScanNumber2 = fromSixteenToTen(s);
                    System.out.println(ScanNumber2);
            }
        //for exit
        } while (Choice != -1);
            System.out.println("BYEEEEEEE :)");
    }

    //@fromTenToSixteen
    public static String fromTenToSixteen(int Num) {
        Integer LeftOver;
        Vector<String> v = new Vector<String>();
        String result="";
        if (Num >0) {
            while (Num > 0) {
                LeftOver = Num % 16;
                Num = Num / 16;
                v.add(Change(LeftOver));
            }
            StringBuilder SB = new StringBuilder(); // build a reverse string
            for (String str : v) {
                SB.append(str);
            }
            SB.reverse();
            result = SB.toString();
        }
        // if there is incorrect input
        else {
            System.out.println("Wrong input. try again!");
        }
        return result;
    }

    //@isHexadecimal - to check if the string include onle A-F and 0-9. for 16 base.
    public static boolean isHexadecimal(String str) {
        return str.matches("[A-Fa-f0-9]+");
    }

    //@Change - changing the digits to char letter
    public static String Change (int Num){
        if (Num >= 10 && Num <= 15) {
                if (Num == 10) {
                    return "A";
                }
                if (Num == 11) {
                    return "B";
                }
                if (Num == 12) {
                    return "C";
                }
                if (Num == 13) {
                    return "D";
                }
                if (Num == 14) {
                    return "E";
                }
                if (Num == 15) {
                    return "F";
                }
        }
        return Integer.toString(Num);
    }

    //@fromSixteenToTen
    public static int fromSixteenToTen(String string) {
        Vector<Integer> sixteenDoublesV = new Vector<Integer>();
        Vector<Integer> numinputV = new Vector<Integer>();
        Vector<Integer> ens = new Vector<Integer>();
        int ans = 0 ;
        // to fill the double vec
        for (int i = 0; i < string.length(); i++) {
            int inside=1;
            for (int b=0; b<i; b++){
                inside = inside*16;
            }
            sixteenDoublesV.add(inside);
        }
        // to fill the input vec
        for (int i = 0; i < string.length(); i++) {
            char value = string.charAt(i);
            numinputV.add(fromCharToNum(string, value));
        }
        int m = 0;
        // for the ens vec
        while (m < string.length()) {
            for (int j = string.length() - 1; j >= 0; j--) {
                //int ans = sixteenDoublesV*numinputV;
                ens.add((sixteenDoublesV.elementAt(m) * numinputV.elementAt(j)));
                m++;
            }
        }
        // to add it all
        for (int i = 0; i < string.length(); i++) {
            ans = ans + ens.elementAt(i);
        }
        return ans;
    }

    //@fromCharToNum- to change from char to num. for 16 base.
    public static int fromCharToNum(String string, char c) {
        String digits = "0123456789ABCDEF";
        string = string.toUpperCase();
        int val = 0;
        int d = digits.indexOf(c);
        val = 16*val + d;
        return val;
    }

}
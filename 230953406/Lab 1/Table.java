import java.util.Scanner;
class Table{
    	public static void main(String args[]) {
        	int number, i;
        	Scanner sc = new Scanner(System.in);
        	System.out.println("Enter a number to print its table:");
        	number = sc.nextInt();
        	System.out.println("Table of " + number + ":");
        	for (i = 1; i <= 10; i++) {
            	System.out.println(number + " x " + i + " = " + (number * i));
        	}
    	}
}
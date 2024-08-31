import java.util.Scanner;
class Factorial{
	public static void main(String args[]){
        	int number;
        	long factorial = 1;
        	Scanner sc = new Scanner(System.in);
        	System.out.println("Enter a number to calculate its factorial:");
        	number = sc.nextInt();
        	for (int i = 1; i <= number; i++){
            	factorial *= i;
        	}        
        	System.out.println("Factorial of " + number + " is: " + factorial);
    	}
}
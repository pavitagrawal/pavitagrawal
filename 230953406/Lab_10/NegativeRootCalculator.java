import java.util.Scanner;
class NegativeNumberException extends Exception {
    public NegativeNumberException(String message) {
        super(message);
    }
}
public class NegativeRootCalculator {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        double number = sc.nextDouble();
        try {
            if (number < 0) {
                throw new NegativeNumberException("Error: Cannot calculate the square root of a negative number.");
            }
            double root = Math.sqrt(number);
            System.out.println("The square root of " + number + " is: " + root);
        } catch (NegativeNumberException e) {
            System.out.println(e.getMessage());
        } finally {
            sc.close();
        }
    }
}
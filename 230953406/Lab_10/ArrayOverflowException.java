import java.util.Scanner;

public class ArrayOverflowException {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] numbers = new int[5];
        System.out.println("Please enter 6 numbers (array size is 5):");
        try {
            for (int i = 0; i < 6; i++) {
                System.out.print("Enter number " + (i + 1) + ": ");
                numbers[i] = sc.nextInt();
            }
        }
        catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Array overflow. You are trying to access an index beyond the array size.");
        }
        finally {
            sc.close();
        }
        System.out.println("Valid elements entered:");
        for (int i = 0; i < numbers.length; i++) {
            System.out.println("Index " + i + ": " + numbers[i]);
        }
    }
}
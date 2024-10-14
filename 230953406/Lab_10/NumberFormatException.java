import java.util.Scanner;
class NumberFormatExceptionExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter a number: ");
        String input = scanner.nextLine();
        try {
            int number = Integer.parseInt(input);
            System.out.println("You entered the number: " + number);
        } 
        catch (java.lang.NumberFormatException e) {
            System.out.println("Error: Invalid input. Please enter a valid integer.");
        } 
        finally {
            scanner.close();
        }
    }
}
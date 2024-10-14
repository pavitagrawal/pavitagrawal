import java.util.Arrays;
import java.util.Scanner;
public class StringManipulator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String originalString;
        System.out.println("Enter a string:");
        originalString = scanner.nextLine();
        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Check if the string is a palindrome");
            System.out.println("2. Sort the string in alphabetical order");
            System.out.println("3. Reverse the string");
            System.out.println("4. Concatenate the original and reversed string");
            System.out.println("5. Exit");
            System.out.print("Choose an option (1-5): ");
            int choice = scanner.nextInt();
            scanner.nextLine();
            switch (choice) {
                case 1:
                    checkPalindrome(originalString);
                    break;
                case 2:
                    sortString(originalString);
                    break;
                case 3:
                    reverseString(originalString);
                    break;
                case 4:
                    concatenateStrings(originalString);
                    break;
                case 5:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
    private static void checkPalindrome(String str) {
        String reversed = new StringBuilder(str).reverse().toString();
        if (str.equalsIgnoreCase(reversed)) {
            System.out.println("The string is a palindrome.");
        } else {
            System.out.println("The string is not a palindrome.");
        }
    }

    private static void sortString(String str) {
        char[] characters = str.toCharArray();
        Arrays.sort(characters);
        System.out.println("Sorted string: " + new String(characters));
    }

    private static void reverseString(String str) {
        String reversed = new StringBuilder(str).reverse().toString();
        System.out.println("Reversed string: " + reversed);
    }

    private static void concatenateStrings(String str) {
        String reversed = new StringBuilder(str).reverse().toString();
        String concatenated = str + reversed;
        System.out.println("Concatenated string: " + concatenated);
    }
}
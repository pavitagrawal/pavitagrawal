import java.util.Scanner;
public class wordReplacer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a sentence:");
        String original = sc.nextLine();
        System.out.println("Enter the word to be replaced:");
        String toReplace = sc.nextLine();
        System.out.println("Enter the replacement word:");
        String replacement = sc.nextLine();
        String result = original.replace(toReplace, replacement);
        System.out.println("Updated sentence:");
        System.out.println(result);
    }
}
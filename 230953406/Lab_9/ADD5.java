import java.util.Scanner;

public class ThreeLetterWords {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a five-letter word: ");
        String word = scanner.nextLine();
        
        System.out.println("Possible three-letter words:");
        generateThreeLetterWords(word);
    }

    static void generateThreeLetterWords(String word) {
        for (int i = 0; i < word.length(); i++) {
            for (int j = 0; j < word.length(); j++) {
                for (int k = 0; k < word.length(); k++) {
                    if (i != j && j != k && i != k) {
                        System.out.println("" + word.charAt(i) + word.charAt(j) + word.charAt(k));
                    }
                }
            }
        }
    }
}

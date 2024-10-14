import java.util.Scanner;
class q1 {
    public static void main(String[] args) {
        String input;
        int chars = 0, words = 0, lines = 0, vowels = 0;
        char[] vowelArr = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter string: ");
        input = sc.nextLine();
        String[] inputLines = input.split("\n");
        lines = inputLines.length;
        for (String line : inputLines) {
            String[] lineWords = line.trim().split("\\s+");
            words += lineWords.length;
            for (int i = 0; i < line.length(); i++) {
                char ch = line.charAt(i);
                boolean isVowel = false;
                for (int j = 0; j < vowelArr.length; j++) {
                    if (ch == vowelArr[j]) {
                        isVowel = true;
                        break;
                    }
                }
                if (isVowel) {
                    vowels++;
                }
            }
            chars += line.replaceAll("\\s+", "").length();
        }
        System.out.println("Number of characters (excluding whitespace): " + chars);
        System.out.println("Number of words: " + words);
        System.out.println("Number of lines: " + lines);
        System.out.println("Number of vowels: " + vowels);
    }
}
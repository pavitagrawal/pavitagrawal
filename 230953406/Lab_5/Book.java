import java.util.Scanner;
class Book {
    String title;
    String author;
    int edition;
    Book(String title, String author, int edition) {
        this.title = title;
        this.author = author;
        this.edition = edition;
    }
}
class BookDemo {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        Book[] books = new Book[6];
        for (int i = 0; i < 6; i++) {
            System.out.println("Enter title of book " + (i + 1) + ":");
            String title = sc.nextLine();
            System.out.println("Enter author of book " + (i + 1) + ":");
            String author = sc.nextLine();
            System.out.println("Enter edition of book " + (i + 1) + ":");
            int edition = sc.nextInt();
            sc.nextLine();
            books[i] = new Book(title, author, edition);
        }
        System.out.println("Enter author name to display books:");
        String inputAuthor = sc.nextLine();
        System.out.println("Books by " + inputAuthor + ":");
        for (Book book : books) {
            if (book.author.equalsIgnoreCase(inputAuthor)) {
                System.out.println("Title: " + book.title + ", Edition: " + book.edition);
            }
        }
    }
}
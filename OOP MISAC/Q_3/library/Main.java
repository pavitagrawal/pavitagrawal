package library;

import users.LibraryUser;
import books.Book;
import exceptions.BookNotAvailableException;
import exceptions.BookNotBorrowedException;
import exceptions.BookCannotBeIssued;

public class Main {
    public static void main(String[] args) {
        LibraryUser user = new LibraryUser("Pavit", "U001");
        Book book = new Book("Harry Potter");

        try {
            user.borrowBook(book);
            System.out.println("Book borrowed: " + book.getTitle());
        } catch (BookNotAvailableException | BookCannotBeIssued e) {
            System.out.println("Error: " + e.getMessage());
        }

        try {
            user.returnBook();
            System.out.println("Book returned: " + book.getTitle());
        } catch (BookNotBorrowedException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
package users;

import books.Book;
import exceptions.BookNotAvailableException;
import exceptions.BookNotBorrowedException;
import exceptions.BookCannotBeIssued;

public class LibraryUser extends user implements LibraryOperations {
    private Book borrowedBook;

    public LibraryUser(String name, String userId) {
        super(name, userId);
    }

    @Override
    public void borrowBook(Book book) throws BookNotAvailableException, BookCannotBeIssued {
        if (book.isAvailable()) {
            borrowedBook = book;
            book.setAvailable(false);
        } else {
            throw new BookNotAvailableException("Book is not available for borrowing.");
        }
    }

    @Override
    public void returnBook() throws BookNotBorrowedException {
        if (borrowedBook != null) {
            borrowedBook.setAvailable(true);
            borrowedBook = null;
        } else {
            throw new BookNotBorrowedException("No book has been borrowed.");
        }
    }
    @Override
    public double calculatePenalty(int daysLate) {
        return daysLate * 0.5; // Example penalty calculation
    }
}
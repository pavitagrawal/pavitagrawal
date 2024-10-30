package users;

import books.Book;
import exceptions.BookNotAvailableException;
import exceptions.BookNotBorrowedException;
import exceptions.BookCannotBeIssued;

public interface LibraryOperations {
    void borrowBook(Book book) throws BookNotAvailableException, BookCannotBeIssued;
    void returnBook() throws BookNotBorrowedException;
    double calculatePenalty(int daysLate);
}
package exceptions;

public class BookCannotBeIssued extends Exception {
    public BookCannotBeIssued(String message) {
        super(message);
    }
}
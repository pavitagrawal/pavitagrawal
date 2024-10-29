import java.util.*;

class SeatAlreadyBookedException extends Exception {
    public SeatAlreadyBookedException(String message) {
        super(message);
    }
}

class SeminarHall {
    private final boolean[] seats = new boolean[15];

    public synchronized void bookSeat(int seatNumber, String userName, String aadharNumber) throws SeatAlreadyBookedException {
        if (seats[seatNumber]) {
            throw new SeatAlreadyBookedException("Seat " + seatNumber + " is already booked.");
        } else {
            seats[seatNumber] = true;
            System.out.println("Booking successful for " + userName + " with Aadhar " + aadharNumber + " for seat " + seatNumber);
        }
    }

    public synchronized void displaySeats() {
        System.out.print("Available seats: ");
        for (int i = 0; i < seats.length; i++) {
            if (!seats[i]) {
                System.out.print(i + " ");
            }
        }
        System.out.println();
    }
}

class BookingTask extends Thread {
    private final SeminarHall seminarHall;
    private final int seatNumber;
    private final String userName;
    private final String aadharNumber;

    public BookingTask(SeminarHall seminarHall, int seatNumber, String userName, String aadharNumber) {
        this.seminarHall = seminarHall;
        this.seatNumber = seatNumber;
        this.userName = userName;
        this.aadharNumber = aadharNumber;
    }

    public void run() {
        try {
            seminarHall.bookSeat(seatNumber, userName, aadharNumber);
        } catch (SeatAlreadyBookedException e) {
            System.out.println(e.getMessage());
        }
    }
}

public class BookingSystem {
    public static void main(String[] args) {
        SeminarHall seminarHall = new SeminarHall();
        List<BookingTask> tasks = new ArrayList<>();

        for (int i = 0; i < 20; i++) {
            int seatNumber = i % 15;
            String userName = "User" + (i + 1);
            String aadharNumber = "Aadhar" + (i + 1);

            BookingTask task = new BookingTask(seminarHall, seatNumber, userName, aadharNumber);
            tasks.add(task);
            task.start();
        }

        // Wait for all threads to complete
        for (BookingTask task : tasks) {
            try {
                task.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Thread interrupted: " + e.getMessage());
            }
        }

        seminarHall.displaySeats();
    }
}

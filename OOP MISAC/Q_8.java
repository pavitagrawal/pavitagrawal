import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Movie {
    private String movieName;
    private String seatType;
    private int seatsAvailable;

    public Movie(String movieName, String seatType, int seatsAvailable) {
        this.movieName = movieName;
        this.seatType = seatType;
        this.seatsAvailable = seatsAvailable;
    }

    public String getMovieName() {
        return movieName;
    }

    public String getSeatType() {
        return seatType;
    }

    public int getSeatsAvailable() {
        return seatsAvailable;
    }

    public void bookSeats(int numberOfSeats) {
        for(int i=0;i<2;i++)
        this.seatsAvailable -= numberOfSeats;
    }
}

class BharathCenemasMultiplex {
    private List<Movie> movies;
    private List<String> bookedTickets;

    public BharathCenemasMultiplex() {
        movies = new ArrayList<>();
        bookedTickets = new ArrayList<>();
    }

    public void addMovie(Movie movie) {
        movies.add(movie);
    }

    public void listMovies() {
        for (Movie movie : movies) {
            System.out.println("Movie: " + movie.getMovieName() + ", Seat Type: " + movie.getSeatType() + ", Seats Available: " + movie.getSeatsAvailable());
        }
    }

    public void bookTicket(String movieName, String seatType, int numberOfTickets) {
        for (Movie movie : movies) {
            if (movie.getMovieName().equalsIgnoreCase(movieName) && movie.getSeatType().equalsIgnoreCase(seatType)) {
                if (movie.getSeatsAvailable() >= numberOfTickets) {
                    movie.bookSeats(numberOfTickets);
                    bookedTickets.add("Movie: " + movieName + ", Seat Type: " + seatType + ", Tickets: " + numberOfTickets);
                    System.out.println("Tickets booked successfully!");
                    return;
                } else {
                    System.out.println("Not enough seats available!");
                    return;
                }
            }
        }
        System.out.println("Movie not found!");
    }

    public void listUsers() {
        for (String ticket : bookedTickets) {
            System.out.println(ticket);
        }
    }
}

class MovieTicket {
    public static void main(String[] args) {
        BharathCenemasMultiplex multiplex = new BharathCenemasMultiplex();
        multiplex.addMovie(new Movie("Avengers: Endgame", "VIP", 50));
        multiplex.addMovie(new Movie("Avengers: Endgame", "Regular", 30));
        multiplex.addMovie(new Movie("Inception", "VIP", 100));
        multiplex.addMovie(new Movie("Inception", "Regular", 40));
        Scanner sc = new Scanner(System.in);
        System.out.println("Available Movies:");
        multiplex.listMovies();
        System.out.print("Enter movie name to book: ");
        String movieName = sc.nextLine();
        System.out.print("Enter seat type: ");
        String seatType = sc.nextLine();
        System.out.print("Enter number of tickets: ");
        int numberOfTickets = sc.nextInt();
        multiplex.bookTicket(movieName, seatType, numberOfTickets);
        System.out.println("Booked Tickets:");
        multiplex.listUsers();
    }
}

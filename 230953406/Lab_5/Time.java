import java.util.Scanner;
class Time {
    int hours;
    int minutes;
    int seconds;
    Time() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
    Time(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
    }
    void displayTime() {
        System.out.printf("%02d:%02d:%02d%n", hours, minutes, seconds);
    }
    Time addTime(Time t) {
        Time result = new Time();
        result.seconds = this.seconds + t.seconds;
        result.minutes = this.minutes + t.minutes + result.seconds / 60;
        result.hours = this.hours + t.hours + result.minutes / 60;
        result.seconds %= 60;
        result.minutes %= 60;
        return result;
    }
}
class TimeDemo {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter first time (hours minutes seconds): ");
        Time time1 = new Time(scanner.nextInt(), scanner.nextInt(), scanner.nextInt());
        System.out.println("Enter second time (hours minutes seconds): ");
        Time time2 = new Time(scanner.nextInt(), scanner.nextInt(), scanner.nextInt());
        System.out.print("First Time: ");
        time1.displayTime();
        System.out.print("Second Time: ");
        time2.displayTime();
        Time addedTime = time1.addTime(time2);
        System.out.print("Added Time: ");
        addedTime.displayTime();
        scanner.close();
    }
}
import java.util.Scanner;
class Number {
    private double value;
    public Number(double value) {
        this.value = value;
    }
    public boolean isZero() {
        return value == 0;
    }
    public boolean isPositive() {
        return value > 0;
    }
    public boolean isNegative() {
        return value < 0;
    }
    public boolean isOdd() {
        return (int) value % 2 != 0;
    }
    public boolean isEven() {
        return (int) value % 2 == 0;
    }
    public boolean isPrime() {
        if (value <= 1) return false;
        for (int i = 2; i <= Math.sqrt(value); i++) {
            if (value % i == 0) return false;
        }
        return true;
    }
    public boolean isArmstrong() {
        int sum = 0, temp, digits = 0;
        temp = (int) value;
        while (temp != 0) {
            temp /= 10;
            digits++;
        }
        temp = (int) value;
        while (temp != 0) {
            int remainder = temp % 10;
            sum += Math.pow(remainder, digits);
            temp /= 10;
        }
        return sum == (int) value;
    }
}
class NumberDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        double inputValue = sc.nextDouble();
        Number number = new Number(inputValue);
        System.out.println("Is Zero: " + number.isZero());
        System.out.println("Is Positive: " + number.isPositive());
        System.out.println("Is Negative: " + number.isNegative());
        System.out.println("Is Odd: " + number.isOdd());
        System.out.println("Is Even: " + number.isEven());
        System.out.println("Is Prime: " + number.isPrime());
        System.out.println("Is Armstrong: " + number.isArmstrong());
    }
}

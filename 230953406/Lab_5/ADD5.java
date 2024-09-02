class SquareCalculator {
    public static void main(String[] args) {
        System.out.println(square(3));    // Output: 9
        System.out.println(square(0.2));  // Output: 0.04
    }

    public static double square(double number) {
        return number * number;
    }
}
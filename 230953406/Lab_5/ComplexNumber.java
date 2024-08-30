import java.util.Scanner;
class ComplexNumber {
    double real;
    double imaginary;
    ComplexNumber(double r, double i) {
        real = r;
        imaginary = i;
    }
    ComplexNumber add(int integer, ComplexNumber c) {
        return new ComplexNumber(real + integer, imaginary);
    }
    ComplexNumber add(ComplexNumber c1, ComplexNumber c2) {
        return new ComplexNumber(c1.real + c2.real, c1.imaginary + c2.imaginary);
    }
    void display() {
        System.out.println(real + " + " + imaginary + "i");
    }
}
class ComplexNumberDemo {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter real part of first complex number: ");
        double real1 = sc.nextDouble();
        System.out.print("Enter imaginary part of first complex number: ");
        double imaginary1 = sc.nextDouble();
        ComplexNumber c1 = new ComplexNumber(real1, imaginary1);
        System.out.print("Enter integer to add: ");
        int integer = sc.nextInt();
        ComplexNumber result1 = c1.add(integer, c1);
        System.out.print("Result of adding integer to complex number: ");
        result1.display();
        System.out.print("Enter real part of second complex number: ");
        double real2 = sc.nextDouble();
        System.out.print("Enter imaginary part of second complex number: ");
        double imaginary2 = sc.nextDouble();
        ComplexNumber c2 = new ComplexNumber(real2, imaginary2);
        ComplexNumber result2 = c1.add(c1, c2);
        System.out.print("Result of adding two complex numbers: ");
        result2.display();
    }
}
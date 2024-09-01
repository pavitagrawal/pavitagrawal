import java.util.Scanner;
class ExpressionCalc {
    public static void main(String args[]) {
        int a, b;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter value for a: ");
        a = sc.nextInt();
        System.out.println("Enter value for b: ");
        b = sc.nextInt();
        int result1 = (a << 2) + (b >> 2);
        System.out.println("Result of (a << 2) + (b >> 2) = " + result1);
        boolean result2 = (b > 0);
        System.out.println("Result of (b > 0) = " + result2);
        float result3 = (a + b * 100) / 10.0f;
        System.out.println("Result of (a + b * 100) / 10 = " + result3);
        int result4 = a & b;
        System.out.println("Result of a & b = " + result4);
    }
}

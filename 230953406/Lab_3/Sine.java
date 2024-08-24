import java.util.Scanner;
import java.math.*;
public class Sine {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double x, ans = 0, radians, n;
        System.out.println("Enter x:");
        x = sc.nextDouble();
        System.out.println("Enter the no. of terms: ");
        n = sc.nextDouble();
        radians = Math.toRadians(x);

        for (int i = 0; i < n; i++) {
            ans += Math.pow(-1, i) * Math.pow(radians, 2 * i + 1) / factorial(2 * i + 1);
        }

        System.out.println("Sin(" + x + " degrees) = " + ans);
    }

    public static int factorial(int n) {
        if (n == 0) {
            return 1;
        }
        else {
            return n * factorial(n - 1);
        }
    }
}

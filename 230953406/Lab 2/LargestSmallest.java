import java.util.Scanner;
class LargestSmallest {
    public static void main(String args[]) {
        float num1, num2, num3;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter three numbers: ");
        num1 = sc.nextFloat();
        num2 = sc.nextFloat();
        num3 = sc.nextFloat();
        float largest = (num1 > num2) ? ((num1 > num3) ? num1 : num3) : ((num2 > num3) ? num2 : num3);
        float smallest = (num1 < num2) ? ((num1 < num3) ? num1 : num3) : ((num2 < num3) ? num2 : num3);
        System.out.println("Largest number: " + largest);
        System.out.println("Smallest number: " + smallest);
    }
}
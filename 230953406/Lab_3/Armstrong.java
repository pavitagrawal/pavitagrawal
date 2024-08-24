import java.util.Scanner;
public class Armstrong {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number to check: ");
        int n, num, temp, sum = 0;
        n = sc.nextInt();
        num = n;
        while(n>0){
            temp = (n%10)*(n%10)*(n%10);
            sum += temp;
            n = n/10;
        }
        if (sum == num) {
            System.out.println(num + " is an armstrong no.");
        } 
        else {
            System.out.println(num + " is not an armstrong no.");
        }
    }
}

import java.util.Scanner;
public class Prime{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n, m, check = 0;
        System.out.println("Enter n: ");
        n = sc.nextInt();
        System.out.println("Enter m: ");
        m = sc.nextInt();
        System.out.println("The prime numbers are:");
        for(int i=n; i<=m; i++){
            for(int j=2;j<i;j++){
                if(i%j!=0){
                    check = 1;
                }
                else{
                    check = 0;
                    break;
                }
            }
            if(check == 1){
                System.out.print(i+" ");
            }
        }
    }
}
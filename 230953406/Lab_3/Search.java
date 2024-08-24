import java.util.Scanner;
public class Search {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n;
        int a[]={1, 2, 3, 1, 2, 1, 5, 6, 7};
        System.out.println("Enter the value to search:");
        n = sc.nextInt();
        System.out.print("Digit found at ");
        for(int i=0; i<9; i++){
            if(a[i]==n){
                System.out.print("a["+i+"] ");
            }
        }
        System.out.print("positions");
    }
}
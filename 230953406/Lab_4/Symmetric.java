import java.util.Scanner;
class Symmetric {
    public static void main(String[] args) {
        int sum=0, check = 0;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the square matrix dimension: ");
        int n=sc.nextInt();
        int matrix[][]=new int[n][n];
        System.out.println("Enter the elements of the matrix:");
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                matrix[i][j]=sc.nextInt();
            }
        }
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if(matrix[i][j]==matrix[j][i]){
                    check = 1;
                }
                else{
                    check = 0;
                    break;
                }
            }
        }
        if(check==1){
            System.out.println("It is a symmetric matrix.");
        }
        else{
            System.out.println("It is not a symmetric matrix.");
        }
    }
}

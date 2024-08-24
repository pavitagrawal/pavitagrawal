import java.util.Scanner;
class Non_diagnal{
    public static void main(String[] args) {
        int sum=0;
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
        System.out.println("Non-diagnal elements:");
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if (i!=j && i+j!=n-1){
                    System.out.println(matrix[i][j]);
                    sum+=matrix[i][j];
                }
            }
        }
        System.out.println("The sum is: "+ sum);
    }
}
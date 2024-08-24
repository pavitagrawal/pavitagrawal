import java.util.Scanner;
class Principal {
    public static void main(String[] args) {
        int sum=0;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter no. of rows: ");
        int m=sc.nextInt();
        System.out.print("Enter no. of columns: ");
        int n=sc.nextInt();
        int matrix[][]=new int[m][n];
        System.out.println("Enter the elements of the matrix:");
        for(int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                matrix[i][j]=sc.nextInt();
            }
        }
        System.out.println("Principal diagnal elements:");
        for(int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                if (i==j){
                    System.out.println(matrix[i][j]);
                    sum+=matrix[i][j];
                }
            }
        }
        System.out.println("The sum is: "+ sum);
    }
}

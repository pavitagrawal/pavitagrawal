import java.util.Scanner;
class MatrixOperations{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter no. of rows of mat1: ");
        int m = sc.nextInt();
        System.out.print("Enter no. of columns of mat1: ");
        int n = sc.nextInt();
        int mat1[][] = new int[m][n];
        System.out.println("Enter the elements of the mat1:");
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                mat1[i][j] = sc.nextInt();
            }
        }
        System.out.print("Enter no. of rows of mat2: ");
        int p = sc.nextInt();
        System.out.print("Enter no. of columns of mat2: ");
        int q = sc.nextInt();
        int mat2[][] = new int[p][q];
        System.out.println("Enter the elements of the mat2:");
        for(int i = 0; i < p; i++){
            for(int j = 0; j < q; j++){
                mat2[i][j] = sc.nextInt();
            }
        }
        if(m == p && n == q){
            int sum[][] = new int[m][n];
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    sum[i][j] = mat1[i][j] + mat2[i][j];
                }
            }
            System.out.println("Sum of matrices:");
            for(int i = 0; i < m; i++){
                for(int j = 0; j < n; j++){
                    System.out.print(sum[i][j] + " ");
                }
                System.out.print("\n");
            }
        }
        else{
            System.out.println("Matrix addition not possible.");
        }
        if(n != p){
            System.out.println("Matrix multiplication not possible.");
        }
        else{
            int product[][] = new int[m][q];
            for(int i = 0; i < m; i++){
                for(int j = 0; j < q; j++){
                    product[i][j] = 0;
                    for(int k = 0; k < n; k++){
                        product[i][j] += (mat1[i][k] * mat2[k][j]);
                    }
                }
            }
            System.out.println("Product of matrices:");
            for(int i = 0; i < m; i++){
                for(int j = 0; j < q; j++){
                    System.out.print(product[i][j] + " ");
                }
                System.out.print("\n");
            }
        }
    }
}

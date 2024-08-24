import java.util.Scanner;
class MagicSquare{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the order of the matrix (n x n): ");
        int n = sc.nextInt();
        int matrix[][] = new int[n][n];
        System.out.println("Enter the elements of the matrix:");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrix[i][j] = sc.nextInt();
            }
        }
        int magicSum = 0;
        for (int j = 0; j < n; j++) {
            magicSum += matrix[0][j];
        }
        boolean isMagicSquare = true;
        for (int i = 0; i < n; i++) {
            int rowSum = 0;
            for (int j = 0; j < n; j++) {
                rowSum += matrix[i][j];
            }
            if (rowSum != magicSum) {
                isMagicSquare = false;
                break;
            }
        }
        for (int j = 0; j < n && isMagicSquare; j++) {
            int colSum = 0;
            for (int i = 0; i < n; i++) {
                colSum += matrix[i][j];
            }
            if (colSum != magicSum) {
                isMagicSquare = false;
                break;
            }
        }
        int principalDiagonalSum = 0;
        for (int i = 0; i < n; i++) {
            principalDiagonalSum += matrix[i][i];
        }
        if (principalDiagonalSum != magicSum) {
            isMagicSquare = false;
        }
        int nonPrincipalDiagonalSum = 0;
        for (int i = 0; i < n; i++) {
            nonPrincipalDiagonalSum += matrix[i][n - 1 - i];
        }
        if (nonPrincipalDiagonalSum != magicSum) {
            isMagicSquare = false;
        }
        if (isMagicSquare) {
            System.out.println("The matrix is a magic square.");
        } else {
            System.out.println("The matrix is not a magic square.");
        }
    }
}

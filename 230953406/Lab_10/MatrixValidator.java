import java.util.Scanner;
class NonSquareMatrixException extends Exception {
    public NonSquareMatrixException(String message) {
        super(message);
    }
}
public class MatrixValidator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter the number of rows: ");
            int rows = scanner.nextInt();

            System.out.print("Enter the number of columns: ");
            int cols = scanner.nextInt();
            if (rows != cols) {
                throw new NonSquareMatrixException("Error: Matrix is not square. Number of rows and columns must be equal.");
            }
            int[][] matrix = new int[rows][cols];
            System.out.println("Enter the elements of the matrix:");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    System.out.print("Enter element at [" + i + "][" + j + "]: ");
                    matrix[i][j] = scanner.nextInt();
                }
            }
            System.out.println("Matrix entered:");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }
        } catch (NonSquareMatrixException e) {
            System.out.println(e.getMessage());
        } catch (Exception e) {
            System.out.println("Error: Invalid input.");
        } finally {
            scanner.close();
        }
    }
}
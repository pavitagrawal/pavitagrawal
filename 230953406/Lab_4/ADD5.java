public class MatrixOperations {
    public static void main(String[] args) {
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        int trace = calculateTrace(matrix);
        double norm = calculateNorm(matrix);

        System.out.println("Trace: " + trace);
        System.out.println("Norm: " + norm);
    }

    public static int calculateTrace(int[][] matrix) {
        int trace = 0;
        for (int i = 0; i < matrix.length; i++) {
            trace += matrix[i][i];
        }
        return trace;
    }

    public static double calculateNorm(int[][] matrix) {
        double sumOfSquares = 0;
        for (int[] row : matrix) {
            for (int element : row) {
                sumOfSquares += element * element;
            }
        }
        return Math.sqrt(sumOfSquares);
    }
}

import java.util.Scanner;

class NumArray {
    int arr[] = new int[10];

    int arrayMin() {
        int min = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }

    int arrayAvg() {
        int sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        int avg = sum / arr.length;
        return avg;
    }

    void arraySearch(int key) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == key) {
                System.out.println(key + " at position " + i);
            }
        }
    }

    public static void main(String args[]) {
        NumArray numArray = new NumArray();
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < 10; i++) {
            numArray.arr[i] = sc.nextInt();
        }
        int min = numArray.arrayMin();
        int avg = numArray.arrayAvg();
        System.out.println("min: " + min + " avg: " + avg);
        numArray.arraySearch(3);
    }
}

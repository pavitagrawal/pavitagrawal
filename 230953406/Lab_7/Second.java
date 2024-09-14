import java.util.Scanner;
class Counter {
    static int count = 0;
    int value;
    Counter(int value) {
        this.value = value;
        count += 1;
    }
    int add(int i1, int i2) {
        return i1 + i2;
    }
}
public class Second {
    public static void main(String args[]) {
        Counter c1 = new Counter(0);
        Counter c2 = new Counter(0);
        Counter c3 = new Counter(0);
        Counter c4 = new Counter(0);
        System.out.println(c2.add(3, 4));
        System.out.println("No. of objects created: " + Counter.count);
    }
}
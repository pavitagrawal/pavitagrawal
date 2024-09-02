 class SwapExample {

    // Call by Value
    public static void swapByValue(int a, int b) {
        int temp = a;
        a = b;
        b = temp;
        System.out.println("Inside swapByValue: a = " + a + ", b = " + b);
    }

    // Call by Reference
    public static void swapByReference(IntegerWrapper a, IntegerWrapper b) {
        IntegerWrapper temp = new IntegerWrapper(a.value);
        a.value = b.value;
        b.value = temp.value;
        System.out.println("Inside swapByReference: a = " + a.value + ", b = " + b.value);
    }

    public static void main(String[] args) {
        // Call by Value
        int x = 5, y = 10;
        System.out.println("Before swapByValue: x = " + x + ", y = " + y);
        swapByValue(x, y);
        System.out.println("After swapByValue: x = " + x + ", y = " + y);

        // Call by Reference
        IntegerWrapper a = new IntegerWrapper(5);
        IntegerWrapper b = new IntegerWrapper(10);
        System.out.println("Before swapByReference: a = " + a.value + ", b = " + b.value);
        swapByReference(a, b);
        System.out.println("After swapByReference: a = " + a.value + ", b = " + b.value);
    }
}

class IntegerWrapper {
    int value;

    IntegerWrapper(int value) {
        this.value = value;
    }
}

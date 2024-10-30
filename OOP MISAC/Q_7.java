class NonNumericTypeException extends Exception {
    public NonNumericTypeException(String msg) {
        super(msg);
    }
}
class Task {
    void executeTask() {
        System.out.println("Task is being executed");
    }
}
class SumTask<T extends Number> extends Task {
    public synchronized T sum(T a, T b) throws NonNumericTypeException {
        if (a == null || b == null) {
            throw new NonNumericTypeException("Null values are not allowed");
        }
        if (!(a instanceof Number && b instanceof Number)) {
            throw new NonNumericTypeException("Invalid format: Both inputs must be numbers");
        }

        if (a instanceof Integer) {
            return (T) Integer.valueOf(a.intValue() + b.intValue());
        } else if (a instanceof Double) {
            return (T) Double.valueOf(a.doubleValue() + b.doubleValue());
        } else {
            throw new NonNumericTypeException("Type Mismatch: Unsupported number type");
        }
    }
}
public class Q_7 {
    public static void main(String[] args) {
        SumTask<Number> task = new SumTask<>();
        task.executeTask();
        try {
            System.out.println("Sum of 5 and 10: " + task.sum(5, 10));
            System.out.println("Sum of 5.5 and 10.5: " + task.sum(5.5, 10.5));
            System.out.println("Sum of null and 10: " + task.sum(null, 10));
        } catch (NonNumericTypeException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}

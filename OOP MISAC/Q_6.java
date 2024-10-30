import java.util.Scanner;

// Custom exception for a full queue
class QueueFullException extends Exception {
    public QueueFullException(String message) {
        super(message);
    }
}

// Custom exception for an empty queue
class QueueEmptyException extends Exception {
    public QueueEmptyException(String message) {
        super(message);
    }
}

// Thread-safe generic queue class
class ThreadSafeQueue<T> {
    private static final int MAX_SIZE = 10;
    private Object[] queue;
    private int front, rear, currentSize;

    // Constructor
    public ThreadSafeQueue() {
        this.queue = new Object[MAX_SIZE];
        this.front = 0;
        this.rear = 0;
        this.currentSize = 0;
    }

    // Method to add an item to the queue
    public synchronized void enqueue(T item) throws QueueFullException {
        if (currentSize == MAX_SIZE) {
            throw new QueueFullException("Queue is full!");
        }
        queue[rear] = item;
        rear = (rear + 1) % MAX_SIZE;
        currentSize++;
        System.out.println("Enqueued: " + item);
    }

    // Method to remove an item from the queue
    public synchronized T dequeue() throws QueueEmptyException {
        if (currentSize == 0) {
            throw new QueueEmptyException("Queue is empty!");
        }
        T item = (T) queue[front];
        front = (front + 1) % MAX_SIZE;
        currentSize--;
        System.out.println("Dequeued: " + item);
        return item;
    }
}

public class Q_6 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ThreadSafeQueue<Object> queue = new ThreadSafeQueue<>();
        System.out.print("Enter the number of elements to enqueue (max 10): ");
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            try {
                System.out.print("Enter an integer: ");
                queue.enqueue(sc.nextInt());
            } catch (QueueFullException e) {
                System.out.println(e.getMessage());
                break;
            }
        }
        System.out.println("Dequeuing elements:");
        for (int i = 0; i <= n; i++) {
            try {
                queue.dequeue();
            } catch (QueueEmptyException e) {
                System.out.println(e.getMessage());
                break;
            }
        }
    }
}

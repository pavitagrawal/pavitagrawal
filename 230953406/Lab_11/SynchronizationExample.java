// Shared resource class
class Counter {
    private int count = 0;

    // a. Synchronized method for incrementing the counter
    public synchronized void incrementSynchronizedMethod() {
        count++;
        System.out.println("Incremented using synchronized method. Current count: " + count);
    }

    // b. Synchronized block for incrementing the counter
    public void incrementSynchronizedBlock() {
        synchronized (this) {
            count++;
            System.out.println("Incremented using synchronized block. Current count: " + count);
        }
    }

    // Method to get the current count
    public int getCount() {
        return count;
    }
}

// Thread that increments counter using synchronized method
class ThreadA extends Thread {
    private Counter counter;

    public ThreadA(Counter counter) {
        this.counter = counter;
    }

    @Override
    public void run() {
        // Increment the counter 5 times using synchronized method
        for (int i = 0; i < 5; i++) {
            counter.incrementSynchronizedMethod();
            try {
                Thread.sleep(100);  // Sleep to simulate some time delay
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

// Thread that increments counter using synchronized block
class ThreadB extends Thread {
    private Counter counter;

    public ThreadB(Counter counter) {
        this.counter = counter;
    }

    @Override
    public void run() {
        // Increment the counter 5 times using synchronized block
        for (int i = 0; i < 5; i++) {
            counter.incrementSynchronizedBlock();
            try {
                Thread.sleep(100);  // Sleep to simulate some time delay
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class SynchronizationExample {

    public static void main(String[] args) {
        // Create a shared counter object
        Counter counter = new Counter();

        // Create two threads: ThreadA (using synchronized method) and ThreadB (using synchronized block)
        ThreadA threadA = new ThreadA(counter);
        ThreadB threadB = new ThreadB(counter);

        // Start both threads
        threadA.start();
        threadB.start();

        // Wait for both threads to finish
        try {
            threadA.join();
            threadB.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Final counter value after both threads have finished
        System.out.println("Final count: " + counter.getCount());
    }
}

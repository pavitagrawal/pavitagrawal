class MyTask extends Thread {
    private String taskName;

    public MyTask(String taskName) {
        this.taskName = taskName;
    }

    @Override
    public void run() {
        try {
            System.out.println(taskName + " started. Thread priority: " + this.getPriority());
            
            // Simulate some processing time
            for (int i = 1; i <= 5; i++) {
                // Check if the thread has been interrupted
                if (Thread.currentThread().isInterrupted()) {
                    System.out.println(taskName + " is interrupted during execution.");
                    return;  // Exit the thread if it is interrupted
                }
                
                System.out.println(taskName + " is working... Count: " + i);
                Thread.sleep(1000);  // Simulate time-consuming task
            }
            System.out.println(taskName + " completed successfully.");
        } catch (InterruptedException e) {
            // Handle the interrupt exception if it occurs during sleep or processing
            System.out.println(taskName + " was interrupted! Exiting...");
        }
    }
}

public class ThreadPriorityAndInterruptExample {
    public static void main(String[] args) {
        // Create thread instances with task names
        MyTask t1 = new MyTask("Task 1");
        MyTask t2 = new MyTask("Task 2");
        MyTask t3 = new MyTask("Task 3");

        // Set different priorities for threads
        t1.setPriority(Thread.MIN_PRIORITY);  // Lowest priority
        t2.setPriority(Thread.NORM_PRIORITY); // Normal priority
        t3.setPriority(Thread.MAX_PRIORITY);  // Highest priority

        // Start the threads
        t1.start();
        t2.start();
        t3.start();

        try {
            // Let the threads run for 2 seconds
            Thread.sleep(2000);

            // Interrupt the thread with the lowest priority (t1)
            System.out.println("Interrupting Task 1...");
            t1.interrupt();
            
            // Wait for all threads to complete
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");
        }

        System.out.println("All threads have finished execution.");
    }
}

import java.util.Scanner;
public class ThreadExample {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter:\n1. Inheriting thread class\n2. Runnable interface");
        int n = sc.nextInt();
        switch(n) {
            case 1:
                class A extends Thread {
                    @Override
                    public void run() {
                        for(int i = 0; i < 5; i++) {
                            System.out.println("Implementing by Inheriting thread class");
                        }
                    }
                }
                A t = new A();
                t.start();
                for(int i = 0; i < 5; i++) {
                    System.out.println("main Thread");
                }
                break;
            case 2:
                class B implements Runnable {
                    public void run() {
                        for(int i = 0; i < 5; i++) {
                            System.out.println("Implementing by Runnable interface");
                        }
                    }
                }
                B r = new B();
                Thread t2 = new Thread(r);
                t2.start();
                for(int i = 0; i < 5; i++) {
                    System.out.println("main Thread");
                }
                break;
            default:
                System.out.println("Invalid option");
                break;
        }
    }
}

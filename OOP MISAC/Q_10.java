import java.util.Scanner;

class FullException extends Exception {
    public FullException(String message) {
        super(message);
    }
}

class Box<T> {
    private T[] elements;
    private int top;
    private int size;

    @SuppressWarnings("unchecked")
    public Box(int size) {
        this.size = size;
        elements = (T[]) new Object[size];
        top = -1;
    }

    public void add(T element) throws FullException {
        if (top == size - 1) {
            throw new FullException("Box is full!");
        }
        elements[++top] = element;
    }

    public T retrieve() {
        if (top == -1) {
            System.out.println("Box is empty!");
            return null;
        } else {
            return elements[top--];
        }
    }

    public void clear() {
        for (int i = 0; i <= top; i++) {
            elements[i] = null;
        }
        top = -1;
        System.out.println("Box is cleared!");
    }
}

class Student {
    String name;
    int studentId;

    public Student(String name, int studentId) {
        this.name = name;
        this.studentId = studentId;
    }

    @Override
    public String toString() {
        return "Student [Name=" + name + ", Student ID=" + studentId + "]";
    }
}

public class genericBoxDemo {
    public static void main(String[] args) {
        boolean choice = true;
        Scanner sc = new Scanner(System.in);
        
        Box<Student> studentBox = new Box<>(3);
        
        while (choice) {
            System.out.print("Enter Student name and ID: ");
            try {
                String name = sc.next();
                int id = sc.nextInt();
                studentBox.add(new Student(name, id));
            } catch (FullException e) {
                System.out.println(e.getMessage());
            }

            System.out.println("Enter choice:\n1. Continue 2. Exit");
            int temp = sc.nextInt();
            
            if (temp == 2) {
                choice = false;
            }
        }
        
        System.out.println("Retrieved Student: " + studentBox.retrieve());
        studentBox.clear();
        
        Box<Integer> integerBox = new Box<>(3);
        choice = true;
        
        while (choice) {
            System.out.print("Enter number: ");
            try {
                integerBox.add(sc.nextInt());
            } catch (FullException e) {
                System.out.println(e.getMessage());
            }

            System.out.println("Enter choice:\n1. Continue 2. Exit");
            int temp = sc.nextInt();
            
            if (temp == 2) {
                choice = false;
            }
        }
        
        System.out.println("Retrieved Integer: " + integerBox.retrieve());
        integerBox.clear();
        
        sc.close();
    }
}

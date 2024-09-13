import java.util.Scanner;

class Student {
    int rno, age;
    String name;
}

class UG extends Student {
    Scanner sc = new Scanner(System.in);
    int semester;
    double fees;

    void getdata() {
        System.out.println("Enter name of the UG student: ");
        name = sc.next();
        System.out.println("Enter registration number of the UG student: ");
        rno = sc.nextInt();
        System.out.println("Enter age of the UG student: ");
        age = sc.nextInt();
        System.out.println("Enter semester for the UG student: ");
        semester = sc.nextInt();
        System.out.println("Enter fees for the UG student: ");
        fees = sc.nextDouble();
    }

    void displaydata() {
        System.out.println("Name: " + name);
        System.out.println("Registration number: " + rno);
        System.out.println("Age: " + age);
        System.out.println("Semester: " + semester);
        System.out.println("Fees: " + fees);
    }
}

class PG extends Student {
    Scanner sc = new Scanner(System.in);
    int semester;
    double fees;

    void getdata() {
        System.out.println("Enter name of the PG student: ");
        name = sc.next();
        System.out.println("Enter registration number of the PG student: ");
        rno = sc.nextInt();
        System.out.println("Enter age of the PG student: ");
        age = sc.nextInt();
        System.out.println("Enter semester for the PG student: ");
        semester = sc.nextInt();
        System.out.println("Enter fees for the PG student: ");
        fees = sc.nextDouble();
    }

    void displaydata() {
        System.out.println("Name: " + name);
        System.out.println("Registration number: " + rno);
        System.out.println("Age: " + age);
        System.out.println("Semester: " + semester);
        System.out.println("Fees: " + fees);
    }
}

public class Studentexecute {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        Student s = new Student();
        int option;
        do {
            System.out.println("\nEnter details for\n1.Undergraduate\n2.Postgraduate\n3.Exit\n");
            option = sc.nextInt();
            switch (option) {
                case 1:
                    UG u = new UG();
                    u.getdata();
                    System.out.println("The details are: \n");
                    u.displaydata();
                    break;
                case 2:
                    PG p = new PG();
                    p.getdata();
                    System.out.println("The details are: \n");
                    p.displaydata();
                    break;
                case 3:
                    break;
            }
        } while (option != 3);
    }
}

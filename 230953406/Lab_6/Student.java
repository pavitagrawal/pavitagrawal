import java.util.Scanner;

class Student {
    String regNo;
    String name;
    int age;

    Student(String regNo, String name, int age) {
        this.regNo = regNo;
        this.name = name;
        this.age = age;
    }
}

class UGStudent extends Student {
    int semester;
    double fees;
    static int totalUGAdmissions = 0;
    UGStudent(String regNo, String name, int age, int semester, double fees) {
        super(regNo, name, age);
        this.semester = semester;
        this.fees = fees;
        totalUGAdmissions++;
    }
    void display() {
        System.out.println("UG Student - RegNo: " + regNo + ", Name: " + name + ", Age: " + age + ", Semester: " + semester + ", Fees: " + fees);
    }
}
class PGStudent extends Student {
    int semester;
    double fees;
    static int totalPGAdmissions = 0;
    PGStudent(String regNo, String name, int age, int semester, double fees) {
        super(regNo, name, age);
        this.semester = semester;
        this.fees = fees;
        totalPGAdmissions++;
    }
    void display() {
        System.out.println("PG Student - RegNo: " + regNo + ", Name: " + name + ", Age: " + age + ", Semester: " + semester + ", Fees: " + fees);
    }
}
class StudentApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter number of UG Students: ");
        int ugCount = scanner.nextInt();
        UGStudent[] ugStudents = new UGStudent[ugCount];
        for (int i = 0; i < ugCount; i++) {
            System.out.print("Enter RegNo for UG Student " + (i + 1) + ": ");
            String regNo = scanner.next();
            System.out.print("Enter Name for UG Student " + (i + 1) + ": ");
            String name = scanner.next();
            System.out.print("Enter Age for UG Student " + (i + 1) + ": ");
            int age = scanner.nextInt();
            System.out.print("Enter Semester for UG Student " + (i + 1) + ": ");
            int semester = scanner.nextInt();
            System.out.print("Enter Fees for UG Student " + (i + 1) + ": ");
            double fees = scanner.nextDouble();
            ugStudents[i] = new UGStudent(regNo, name, age, semester, fees);
        }
        System.out.print("Enter number of PG Students: ");
        int pgCount = scanner.nextInt();
        PGStudent[] pgStudents = new PGStudent[pgCount];
        for (int i = 0; i < pgCount; i++) {
            System.out.print("Enter RegNo for PG Student " + (i + 1) + ": ");
            String regNo = scanner.next();
            System.out.print("Enter Name for PG Student " + (i + 1) + ": ");
            String name = scanner.next();
            System.out.print("Enter Age for PG Student " + (i + 1) + ": ");
            int age = scanner.nextInt();
            System.out.print("Enter Semester for PG Student " + (i + 1) + ": ");
            int semester = scanner.nextInt();
            System.out.print("Enter Fees for PG Student " + (i + 1) + ": ");
            double fees = scanner.nextDouble();
            pgStudents[i] = new PGStudent(regNo, name, age, semester, fees);
        }
        System.out.println("UG Students:");
        for (UGStudent ugStudent : ugStudents) {
            ugStudent.display();
        }
        System.out.println("Total UG Admissions: " + UGStudent.totalUGAdmissions);

        System.out.println("PG Students:");
        for (PGStudent pgStudent : pgStudents) {
            pgStudent.display();
        }
        System.out.println("Total PG Admissions: " + PGStudent.totalPGAdmissions);
    }
}
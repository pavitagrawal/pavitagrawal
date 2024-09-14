import java.util.Scanner;

class Student_Detail {
    String name;
    int id;
    final String college_name = "MIT";

    Student_Detail(String s, int id) {
        this.id = id;
        this.name = s;
    }

    void display_details() {
        System.out.println("College: " + college_name);
        System.out.println("Name: " + name);
        System.out.println("Id: " + id);
    }
}

public class StudentRecord {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the name and id:");
        String name = sc.nextLine();
        int id = sc.nextInt();
        Student_Detail s1 = new Student_Detail(name, id);
        s1.display_details();
        sc.close();
    }
}
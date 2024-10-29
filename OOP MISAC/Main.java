import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

interface Func {
    void sort(int no);
    void sort_date(String doj) throws InvalidDateFormatException;
}

class InvalidDateFormatException extends Exception {
    public InvalidDateFormatException(String message) {
        super(message);
    }
}

class Student implements Func {
    String name;
    int rank;
    String regNo;
    String branchCode;

    public Student(String name, int rank, String branchCode) {
        this.name = name;
        this.rank = rank;
        this.branchCode = branchCode;
    }

    @Override
    public void sort(int no) {
    }

    @Override
    public void sort_date(String doj) {
    }

    public void assignRegNo(int counter) {
        this.regNo = "2022" + branchCode + String.format("%03d", counter);
    }

    @Override
    public String toString() {
        return "Name: " + name + ", Rank: " + rank + ", RegNo: " + regNo + ", BranchCode: " + branchCode;
    }
}
class Faculty implements Func {
    String name;
    String DOI;
    String dept;
    String empCode;

    public Faculty(String name, String DOI, String dept) {
        this.name = name;
        this.DOI = DOI;
        this.dept = dept;
    }

    @Override
    public void sort(int no) {
    }

    @Override
    public void sort_date(String doj) throws InvalidDateFormatException {
        // Validate and parse date format
        SimpleDateFormat sdf1 = new SimpleDateFormat("dd-MMM-yyyy");
        SimpleDateFormat sdf2 = new SimpleDateFormat("dd-MM-yyyy");
        sdf1.setLenient(false);
        sdf2.setLenient(false);

        try {
            sdf1.parse(doj);
        } catch (ParseException e1) {
            try {
                sdf2.parse(doj);
            } catch (ParseException e2) {
                throw new InvalidDateFormatException("Invalid date format");
            }
        }
    }

    public void assignEmpCode(int counter) {
        this.empCode = "MAHE" + dept + String.format("%03d", counter);
    }

    @Override
    public String toString() {
        return "Name: " + name + ", DOI: " + DOI + ", Dept: " + dept + ", EmpCode: " + empCode;
    }
}

// Main class to demonstrate the functionality
public class Main {
    public static void main(String[] args) {
        List<Student> students = new ArrayList<>();
        List<Faculty> faculties = new ArrayList<>();

        // Adding sample students
        students.add(new Student("Raju", 3, "CCE"));
        students.add(new Student("Bheem", 1, "IT"));
        students.add(new Student("Pavit", 2, "CCE"));

        // Adding sample faculties with correct and incorrect date formats
        faculties.add(new Faculty("Dr. Lokesh", "10-Mar-2002", "ICT"));
        faculties.add(new Faculty("Dr. Additya", "15-08-2002", "ECE"));
        faculties.add(new Faculty("Dr. Arjun", "25/08/2002", "ICT"));

        students.sort(Comparator.comparingInt(s -> s.rank));
        Map<String, Integer> branchCounters = new HashMap<>();
        for (Student student : students) {
            branchCounters.putIfAbsent(student.branchCode, 0);
            int counter = branchCounters.get(student.branchCode) + 1;
            student.assignRegNo(counter);
            branchCounters.put(student.branchCode, counter);
        }

        faculties.sort(Comparator.comparing(f -> f.DOI));
        Map<String, Integer> deptCounters = new HashMap<>();
        for (Faculty faculty : faculties) {
            try {
                faculty.sort_date(faculty.DOI);
                deptCounters.putIfAbsent(faculty.dept, 0);
                int counter = deptCounters.get(faculty.dept) + 1;
                faculty.assignEmpCode(counter);
                deptCounters.put(faculty.dept, counter);
            } catch (InvalidDateFormatException e) {
                System.out.println("Error for faculty " + faculty.name + ": " + e.getMessage());
            }
        }

        // Displaying sorted Students
        System.out.println("Sorted Students:");
        for (Student student : students) {
            System.out.println(student);
        }

        // Displaying sorted Faculties
        System.out.println("\nSorted Faculties:");
        for (Faculty faculty : faculties) {
            System.out.println(faculty);
        }
    }
}

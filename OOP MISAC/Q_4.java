import java.util.*;

class EmployeeNotFoundException extends Exception {
    EmployeeNotFoundException(String msg) {
        super(msg);
    }
}

class NoLeavesException extends Exception {
    NoLeavesException(String msg) {
        super(msg);
    }
}

class Employee {
    String empName, empCode, leaveType;
    int comp, cas, other;

    Employee(String n, String c) {
        this.empName = n;
        this.empCode = c;
        comp = 13; 
        cas = 12; 
        other = 10;
    }

    synchronized void applyLeave(String ltype, int days) throws NoLeavesException {
        this.leaveType = ltype;
        if (leaveType.equals("co")) {
            if (comp < days) {
                throw new NoLeavesException("Insufficient Leaves");
            }
            comp -= days;
        } else if (leaveType.equals("ca")) {
            if (cas < days) {
                throw new NoLeavesException("Insufficient Leaves");
            }
            cas -= days;
        } else {
            if (other < days) {
                throw new NoLeavesException("Insufficient leaves");
            }
            other -= days;
        }
        System.out.println("Successful Leave Application for " + empName + " for " + days + " days of " + leaveType + " leave.");
    }

    String getInfo() {
        return "Emp Name: " + empName + ", Emp Code: " + empCode + ", Comp Leaves: " + comp + ", Casual Leaves: " + cas + ", Other Leaves: " + other;
    }

    String getType() {
        return leaveType;
    }
}

class EmployeeDatabase {
    ArrayList<Employee> ed = new ArrayList<>();

    synchronized void addE(Employee emp) {
        ed.add(emp);
    }

    synchronized ArrayList<Employee> getAll() {
        return ed;
    }
}

class T1 extends Thread {
    EmployeeDatabase ed;
    Scanner sc = new Scanner(System.in);

    T1(EmployeeDatabase ed) {
        this.ed = ed;
    }

    public void run() {
        System.out.println("Enter Emp Name and Code for 5 employees:");
        for (int i = 0; i < 5; i++) {
            String name = sc.next();
            String code = sc.next();
            Employee emp = new Employee(name, code);
            ed.addE(emp);
        }
    }
}

class T2 extends Thread {
    EmployeeDatabase ed;
    Scanner sc = new Scanner(System.in);

    T2(EmployeeDatabase ed) {
        this.ed = ed;
    }

    public void run() {
        System.out.println("Enter Emp Code to apply leave, Leave Type (co/ca/other), and No. of Days:");
        String code = sc.next();
        String leaveType = sc.next();
        int days = sc.nextInt();
        boolean found = false;

        for (Employee emp : ed.getAll()) {
            if (emp.empCode.equals(code)) {
                found = true;
                try {
                    emp.applyLeave(leaveType, days);
                } catch (NoLeavesException e) {
                    System.out.println(e.getMessage());
                }
                break;
            }
        }
        if (!found) {
            try {
                throw new EmployeeNotFoundException("Employee Not Found");
            } catch (EmployeeNotFoundException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}

public class Q_4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        EmployeeDatabase ed = new EmployeeDatabase();
        
        T1 t1 = new T1(ed);
        t1.start();
        try {
            t1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        T2 t2 = new T2(ed);
        t2.start();
        try {
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("\nEmployees with updated leave information:");
        for (Employee e : ed.getAll()) {
            if ("ca".equals(e.getType())) {
                System.out.println(e.getInfo());
            }
        }
        
        sc.close();
    }
}

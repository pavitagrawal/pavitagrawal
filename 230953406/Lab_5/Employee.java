import java.util.Scanner;
class Employee {
    String employeeName;
    String city;
    double basicSalary;
    double dearnessAllowance;
    double houseRent;
    void getdata() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter employee name: ");
        employeeName = sc.nextLine();
        System.out.print("Enter city: ");
        city = sc.nextLine();
        System.out.print("Enter basic salary: ");
        basicSalary = sc.nextDouble();
        System.out.print("Enter dearness allowance percentage: ");
        dearnessAllowance = sc.nextDouble();
        System.out.print("Enter house rent allowance percentage: ");
        houseRent = sc.nextDouble();
    }
    double calculate() {
        return basicSalary + (basicSalary * dearnessAllowance / 100) + (basicSalary * houseRent / 100);
    }
    void display() {
        double totalSalary = calculate();
        System.out.println("Total salary of " + employeeName + " from " + city + " is: " + totalSalary);
    }
    public static void main(String[] args) {
        Employee emp = new Employee();
        emp.getdata();
        emp.display();
    }
}

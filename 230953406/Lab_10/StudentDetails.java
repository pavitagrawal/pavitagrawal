import java.util.Scanner;

public class StudentDetails {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter student details:");
        System.out.print("Name: ");
        String name = scanner.nextLine();
        System.out.print("Roll Number: ");
        String rollNumber = scanner.nextLine();
        double marks1 = 0, marks2 = 0, marks3 = 0;
        try {
            System.out.print("Enter marks in subject 1: ");
            marks1 = Double.parseDouble(scanner.nextLine());

            System.out.print("Enter marks in subject 2: ");
            marks2 = Double.parseDouble(scanner.nextLine());

            System.out.print("Enter marks in subject 3: ");
            marks3 = Double.parseDouble(scanner.nextLine());

        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid input. Please enter valid numerical values for marks.");
            return;
        }
        double totalMarks = marks1 + marks2 + marks3;
        double percentage = (totalMarks / 300) * 100;
        String grade = "";
        if (percentage >= 90) {
            grade = "A+";
        } else if (percentage >= 80) {
            grade = "A";
        } else if (percentage >= 70) {
            grade = "B+";
        } else if (percentage >= 60) {
            grade = "B";
        } else if (percentage >= 50) {
            grade = "C";
        } else {
            grade = "F";
        }
        System.out.println("\nStudent Details:");
        System.out.println("Name: " + name);
        System.out.println("Roll Number: " + rollNumber);
        System.out.println("Marks in Subject 1: " + marks1);
        System.out.println("Marks in Subject 2: " + marks2);
        System.out.println("Marks in Subject 3: " + marks3);
        System.out.println("Total Marks: " + totalMarks);
        System.out.println("Percentage: " + String.format("%.2f", percentage) + "%");
        System.out.println("Grade: " + grade);
    }
}
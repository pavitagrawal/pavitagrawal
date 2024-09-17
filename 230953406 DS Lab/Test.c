//Write a C program to perform the following:
//Create a structure called 'Employee' with members, Emp name, Emp no, Basic Pay and Total Salary.
//Read the values for data members of 'n' employees in main function and compute Total Salary of each employee in a separate function.
//Use pointer to structure concept.
//Dearness allowance is 40% of basic pay, hra is 15% of basic pay, ts=da+basicsalary+hra
#include<stdio.h>
typedef struct employee{
    char Empname[50];
    int Empno;
    int BasicSal;
    int totalSalary;
}Employee;
void computeTotalSalary(Employee *emp){
    int hra = emp->BasicSal * 0.15;
    int da = emp->BasicSal * 0.40;
    emp->totalSalary = emp->BasicSal + hra + da;
}
int main(){
    int i, n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);
    Employee s[50];
    for(i = 0; i < n; i++){
        printf("Enter Empname%d: ", i + 1);
        scanf("%s", s[i].Empname);
        printf("Enter Empno%d: ", i + 1);
        scanf("%d", &s[i].Empno);
        printf("Enter BasicSal%d: ", i + 1);
        scanf("%d", &s[i].BasicSal);
    }
    for(i = 0; i < n; i++){
        computeTotalSalary(&s[i]);
    }
    printf("Employee list:\n");
    for(i=0;i<n;i++){
        printf("Empname: %s\n", s[i].Empname);
        printf("Empno: %d\n", s[i].Empno);
        printf("Basic Salary: %d\n", s[i].BasicSal);
        printf("Total Salary: %d\n", s[i].totalSalary);
    }
    return 0;
}

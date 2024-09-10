#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    char name[50];
    int rollNo;
    char grade;
    char branch[50];
};
void writeRecords() {
    FILE *file = fopen("students.txt", "w");
    struct Student s;
    for (int i = 0; i < 3; i++) { // Example for 3 students
        printf("Enter Name, Roll No, Grade, Branch: ");
        scanf("%s %d %c %s", s.name, &s.rollNo, &s.grade, s.branch);
        fprintf(file, "%s %d %c %s\n", s.name, s.rollNo, s.grade, s.branch);
    }
    fclose(file);
}
void readRecords() {
    FILE *file = fopen("students.txt", "r");
    struct Student s;
    FILE *branchFile;
    char branch[50];
    
    while (fscanf(file, "%s %d %c %s", s.name, &s.rollNo, &s.grade, s.branch) != EOF) {
        branchFile = fopen(strcat(s.branch, ".txt"), "a");
        fprintf(branchFile, "%s %d %c\n", s.name, s.rollNo, s.grade);
        fclose(branchFile);
    }
    fclose(file);
}
int main() {
    writeRecords();
    readRecords();
    return 0;
}
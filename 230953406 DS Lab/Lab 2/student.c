#include<stdio.h>
typedef struct student{
    char name[50];
    int grade;
    int rollno;
};
int main(){
    int i, n, j;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct student s[50];
    for(i=0;i<n;i++){
        printf("Enter name%d: ", i+1);
        scanf("%s", s[i].name);
        printf("Enter grade%d: ", i+1);
        scanf("%d", &s[i].grade);
        printf("Enter rollno%d: ", i+1);
        scanf("%d", &s[i].rollno);
    }
    struct student temp;
    for(i=0;i<n;i++){
        for(j=0;j<n-1-i;j++){
            if(s[j].rollno>s[j+1].rollno){
                temp = s[j+1];
                s[j+1]=s[j];
                s[j] = temp;
            }
        }
    }
    printf("Sorted student list:\n");
    for(i=0;i<n;i++){
        printf("%s\n", s[i].name);
        printf("%d\n", s[i].grade);
        printf("%d\n", s[i].rollno);
    }
}

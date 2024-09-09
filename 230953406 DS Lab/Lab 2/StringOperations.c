#include<stdio.h>

int strLength(char* str){
    int i=0;
    while (str[i]!=NULL)
    {
        i++;
    }
    return i;
}

void strConcat(char* str1, char* str2, char* str){
    int i=0, j=0;
    while (str1[i]!=NULL)
    {
        str[i]=str1[i];
        i++;
    }
    while (str2[j]!=NULL)
    {
        str[i]=str2[j];
        j++;
        i++;
    }
    str[i]='\0';
}

int strCompare(char* str1, char* str2){
    int i=0;

    while (str1[i]!=NULL || str2[i]!=NULL)
    {
        if(str1[i]>str2[i]){
            return 1;
        }
        else if(str1[i]<str2[i]){
            return -1;
        }
        i++;
    }
    return 0;
}

void insertSubstring(char* str, char* substr, int pos){
    int i;
    int substrLen = strLength(substr);
    int mainstrLen = strLength(str);
    for(i=mainstrLen; i>=pos; i--){
        str[i+substrLen]=str[i];
    }
    for(i=0; i<substrLen; i++){
        str[pos+i]=substr[i];
    }
}

void delSubstring(char* str, char* substr){
    int i,j,flag;
    int substrLen = strLength(substr);
    i=0;
    while(str[i]!=NULL){
        j = 0;
        flag = 1;
        while (substr[j]!=NULL)
        {
            if(str[i+j]!=substr[j]){
                flag = 0;
                break;
            }
            j++;
        }
        if(flag==1){
            break;
        }
        i++;
    }
    if(flag==1){
        j = 0;
        while(str[i+j+substrLen]!=NULL)
        {
            str[i+j]=str[i+j+substrLen];
            j++;
        }
        str[i+j]='\0';
    }
}

int main(){
    char str[200];
    char str1[100];
    char str2[100];
    char choice;
    int pos;

    while (1)
    {
        printf("\n\na - Length of String\nb - String Concatenation\nc - String Comparision\nd - To insert a Substring\ne - To delete a Substring\nf - exit\n\n");
        printf("Enter Choice: ");
        scanf("%c", &choice);
        printf("\n\n");

        fflush(stdin);
        switch (choice)
        {
        case 'a':
            printf("Enter the string: ");
            gets(str);
            fflush(stdin);
            printf("Length = %d", strLength(str));
            break;
        case 'b':
            printf("Enter string 1: ");
            gets(str1);
            fflush(stdin);
            printf("Enter string 2: ");
            gets(str2);
            fflush(stdin);
            strConcat(str1,str2,str);
            printf("Merged String = %s", str);
            break;
        case 'c':
            printf("Enter string 1: ");
            gets(str1);
            fflush(stdin);
            printf("Enter string 2: ");
            gets(str2);
            fflush(stdin);
            printf("Comparision Result = %d", strCompare(str1,str2));
            break;
        case 'd':
            printf("Enter main string: ");
            gets(str1);
            fflush(stdin);
            printf("Enter substring: ");
            gets(str2);
            fflush(stdin);
            printf("Enter Position: ");
            scanf("%d", &pos);
            insertSubstring(str1,str2,pos);
            printf("Updated main string : %s", str1);
            break;
        case 'e':
            printf("Enter main string: ");
            gets(str1);
            fflush(stdin);
            printf("Enter substring: ");
            gets(str2);
            fflush(stdin);
            delSubstring(str1, str2);
            printf("Updated main string : %s", str1);
            break;
        case 'f':
            return 0;
            break;
        default:
            printf("Invalid choice");
            break;
        }
    }

    return 0;
}
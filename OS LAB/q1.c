#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
        pid_t pid;
        pid = fork();
        if(pid ==  0){
                printf("This is the child \n");
                printf("PID:%d\n",getpid());
                printf("PPID:%d\n",getppid());
                
        }else if(pid>0){
                printf("This is the parent \n");
                printf("PID:%d\n",getpid());
                printf("PPID:%d\n",getppid());
        }else{
                printf("Error");
        }
        return 0;
}

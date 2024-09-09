#include<stdio.h>
#include<stdlib.h>

struct time
{
    int hour, min, sec;
};

struct time addTime(struct time t1, struct time t2) {
    struct time result;

    result.sec = (t1.sec + t2.sec) % 60;
    result.min = (t1.min + t2.min + (t1.sec + t2.sec) / 60) % 60;
    result.hour = t1.hour + t2.hour + (t1.min + t2.min + (t1.sec + t2.sec) / 60) / 60;

    return result;
}

struct time diffTime(struct time t1, struct time t2) {
    struct time result;

    if (t2.sec > t1.sec) {
        t1.sec += 60;
        t1.min -= 1;
    }
    result.sec = t1.sec - t2.sec;

    if (t2.min > t1.min) {
        t1.min += 60;
        t1.hour -= 1;
    }
    result.min = t1.min - t2.min;

    result.hour = t1.hour - t2.hour;

    return result;
}

int main(){
    struct time t[2];

    for (int i = 0; i < 2; i++)
    {
        printf("\nTime %d\n",i+1);

        printf("Hour: ");
        scanf("%d", &t[i].hour);

        printf("Minute: ");
        scanf("%d", &t[i].min);

        printf("Second: ");
        scanf("%d", &t[i].sec);
    }
    
    struct time addResult = addTime(t[0],t[1]);
    printf("\nAdded time: %d hours %d minutes %d seconds\n", addResult.hour, addResult.min, addResult.sec);

    struct time diffResult = diffTime(t[0],t[1]);
    printf("\nTime Difference: %d hours %d minutes %d seconds\n", diffResult.hour, diffResult.min, diffResult.sec);

    return 0;
}
#include <stdio.h>

int main()
{
    int arrival[] = {1,2,3,5,6,8,11,12,15,16,19};
    int n = 11;

    int bucket_size = 10;
    int output_rate = 1;   // 1 byte per second
    int packet_size = 4;

    int bucket = 0;
    int current_time = 0;
    int i;

    printf("Leaky Bucket Simulation\n");
    printf("--------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        // Leak data until next packet arrival
        while(current_time < arrival[i])
        {
            if(bucket > 0)
                bucket -= output_rate;

            if(bucket < 0)
                bucket = 0;

            current_time++;
        }

        printf("Time %d sec: Packet arrives (4 bytes)\n", arrival[i]);

        // Check if packet can be accommodated
        if(bucket + packet_size <= bucket_size)
        {
            bucket += packet_size;
            printf("  Conforming Packet (Accepted)\n");
        }
        else
        {
            printf("  Non-Conforming Packet (Rejected)\n");
        }

        printf("  Current bucket content: %d bytes\n\n", bucket);
    }

    printf("Simulation Ended\n");

    return 0;
}
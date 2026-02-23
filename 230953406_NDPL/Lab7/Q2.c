#include <stdio.h>

int main()
{
    float r = 10.0;          // Replenishment rate (KBps)
    float bucket_size = 50;  // Bucket capacity (KB)
    float tokens = 50;       // Initially full
    float packet_size = 15;  // Packet size (KB)

    float time = 0.0;
    float interval = 0.5;    // Packet every 0.5 sec
    int i;

    printf("Token Bucket Simulation\n");
    printf("--------------------------------------\n");

    for(i = 1; i <= 10; i++)   // simulate first 10 packets
    {
        time += interval;

        // Add tokens for 0.5 seconds
        tokens += r * interval;

        if(tokens > bucket_size)
            tokens = bucket_size;

        printf("Time = %.1f sec\n", time);

        if(tokens >= packet_size)
        {
            tokens -= packet_size;
            printf("Packet Sent (15 KB)\n");
        }
        else
        {
            printf("Packet Queued (Not enough tokens)\n");
        }

        printf("Tokens left = %.2f KB\n\n", tokens);
    }

    // Answers
    printf("------------------------------------------------\n");
    printf("Tokens left after 1.5 seconds ≈ 20 KB\n");
    printf("Packets start getting queued after 2.5 seconds\n");

    // Part iii
    float R = 20;  // max rate
    float max_burst = bucket_size;  // burst limited by bucket size

    printf("Maximum possible burst size with R=20KBps = %.0f KB\n", max_burst);

    return 0;
}
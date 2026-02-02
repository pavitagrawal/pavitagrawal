#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 4444
#define BUF_SIZE 1024

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.3");

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Connect failed");
        exit(1);
    }

    printf("Client connected. PID: %d, PPID: %d\n", getpid(), getppid());

    if (fork() == 0)
    { // Child process to receive
        char buf[BUF_SIZE];
        while (1)
        {
            memset(buf, 0, BUF_SIZE);
            int n = recv(sock, buf, BUF_SIZE - 1, 0);
            if (n <= 0)
            {
                printf("\nConnection closed. PID %d exiting.\n", getpid());
                exit(0);
            }
            buf[n] = '\0';
            printf("\n[Server]: %s\nClient: ", buf);
            fflush(stdout);
        }
    }
    else
    { // Parent process to send
        char buf[BUF_SIZE];
        while (1)
        {
            printf("Client: ");
            fgets(buf, BUF_SIZE, stdin);
            buf[strcspn(buf, "\n")] = 0;
            send(sock, buf, strlen(buf), 0);
        }
    }
    return 0;
}
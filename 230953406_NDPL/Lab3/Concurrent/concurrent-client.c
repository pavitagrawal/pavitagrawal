// client.c
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
    int sock;
    struct sockaddr_in serverAddr;
    char buffer[BUF_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.3");

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to server. Start chatting...\n");

    if (fork() == 0)
    {
        /* RECEIVER */
        while (1)
        {
            int bytes = recv(sock, buffer, BUF_SIZE - 1, 0);
            if (bytes <= 0)
            {
                printf("\n[SERVER DISCONNECTED]\n");
                exit(0);
            }
            buffer[bytes] = '\0';
            printf("\n[SERVER] %s\n> ", buffer);
            fflush(stdout);
        }
    }
    else
    {
        /* SENDER */
        while (1)
        {
            printf("> ");
            fflush(stdout);

            if (fgets(buffer, BUF_SIZE, stdin) == NULL)
                break;

            buffer[strcspn(buffer, "\n")] = 0;
            send(sock, buffer, strlen(buffer), 0);
        }
    }

    close(sock);
    return 0;
}

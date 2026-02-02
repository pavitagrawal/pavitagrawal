// server.c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 4444
#define BUF_SIZE 1024

void handle_client(int clientSocket, struct sockaddr_in cliAddr)
{
    char buffer[BUF_SIZE];
    char clientIP[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &cliAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(cliAddr.sin_port);

    printf("[CLIENT CONNECTED] %s:%d\n", clientIP, clientPort);

    if (fork() == 0)
    {
        /* RECEIVER */
        while (1)
        {
            int bytes = recv(clientSocket, buffer, BUF_SIZE - 1, 0);
            if (bytes <= 0)
            {
                printf("[CLIENT DISCONNECTED] %s:%d\n", clientIP, clientPort);
                close(clientSocket);
                exit(0);
            }
            buffer[bytes] = '\0';
            printf("\n[%s:%d] %s\n> ", clientIP, clientPort, buffer);
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
            send(clientSocket, buffer, strlen(buffer), 0);
        }
    }
}

int main()
{
    int sockfd, clientSocket;
    struct sockaddr_in serverAddr, cliAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.3");

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    listen(sockfd, 10);
    printf("Server running on 127.0.0.3:%d\n", PORT);

    while (1)
    {
        addr_size = sizeof(cliAddr);
        clientSocket = accept(sockfd, (struct sockaddr *)&cliAddr, &addr_size);

        if (clientSocket < 0)
            continue;

        if (fork() == 0)
        {
            close(sockfd);
            handle_client(clientSocket, cliAddr);
            exit(0);
        }

        close(clientSocket);
    }

    return 0;
}

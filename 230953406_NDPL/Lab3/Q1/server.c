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
    int sockfd, clientSocket;
    struct sockaddr_in serverAddr, cliAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.3");

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(sockfd, 10);

    printf("Server Main PID: %d, PPID: %d\n", getpid(), getppid());
    printf("Server listening on 127.0.0.1:%d\n", PORT);

    while (1)
    {
        addr_size = sizeof(cliAddr);
        clientSocket = accept(sockfd, (struct sockaddr *)&cliAddr, &addr_size);

        if (fork() == 0)
        { // Child for this client
            close(sockfd);
            printf("\n[New Client] PID: %d, PPID: %d\n", getpid(), getppid());

            if (fork() == 0)
            { // Sub-child for Receiving
                char buf[BUF_SIZE];
                while (1)
                {
                    memset(buf, 0, BUF_SIZE);
                    int n = recv(clientSocket, buf, BUF_SIZE - 1, 0);
                    if (n <= 0)
                    {
                        printf("\nClient disconnected. PID %d exiting.\n", getpid());
                        exit(0);
                    }
                    buf[n] = '\0';
                    printf("\n[Client]: %s\nServer: ", buf);
                    fflush(stdout);
                }
            }
            else
            { // Parent-child for Sending
                char buf[BUF_SIZE];
                while (1)
                {
                    printf("Server: ");
                    fgets(buf, BUF_SIZE, stdin);
                    buf[strcspn(buf, "\n")] = 0;
                    send(clientSocket, buf, strlen(buf), 0);
                }
            }
        }
        close(clientSocket);
    }
    return 0;
}
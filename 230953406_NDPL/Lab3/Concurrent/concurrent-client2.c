#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6969
#define BUF_SIZE 1024

void handle_communication(int sock)
{
	char buffer[BUF_SIZE];
	if (fork() == 0)
	{
		// Receiver Child
		while (1)
		{
			memset(buffer, 0, BUF_SIZE);
			int bytes = recv(sock, buffer, BUF_SIZE - 1, 0);
			if (bytes <= 0)
			{
				printf("\n[LOST CONNECTION]\n");
				exit(0);
			}
			buffer[bytes] = '\0';
			printf("\n[INCOMING] %s\n> ", buffer);
			fflush(stdout);
		}
	}
	else
	{
		// Sender Parent
		while (1)
		{
			printf("> ");
			fgets(buffer, BUF_SIZE, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			if (strcmp(buffer, "back") == 0)
				return;
			send(sock, buffer, strlen(buffer), 0);
		}
	}
}

int main()
{
	int clientSocket;
	struct sockaddr_in serverAddr;
	int choice;

	while (1)
	{
		printf("\n--- CLIENT MENU ---\n");
		printf("1. Connect to Server\n");
		printf("2. Exit Program\n");
		printf("Choice: ");
		scanf("%d", &choice);
		getchar(); // clean newline

		if (choice == 1)
		{
			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(PORT);
			serverAddr.sin_addr.s_addr = inet_addr("127.0.0.3");

			if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
			{
				printf("Connection failed!\n");
			}
			else
			{
				printf("Connected! Type messages (type 'back' to return to menu)\n");
				handle_communication(clientSocket);
				close(clientSocket);
			}
		}
		else if (choice == 2)
		{
			exit(0);
		}
	}
	return 0;
}

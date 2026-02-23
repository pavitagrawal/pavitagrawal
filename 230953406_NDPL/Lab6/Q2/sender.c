#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9090
#define MAXLINE 5000

// XOR operation
void xorOperation(char *dividend, char *divisor, int divisorLen) {
    for (int i = 1; i < divisorLen; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

// CRC computation
void computeCRC(char *data, char *divisor, char *remainder) {
    int dataLen = strlen(data);
    int divisorLen = strlen(divisor);
    char temp[MAXLINE];
    
    strcpy(temp, data);
    
    for (int i = 0; i <= dataLen - divisorLen; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], divisor, divisorLen);
        }
    }
    
    strncpy(remainder, &temp[dataLen - divisorLen + 1], divisorLen - 1);
    remainder[divisorLen - 1] = '\0';
}

// Convert string to binary
void stringToBinary(char *str, char *binary) {
    binary[0] = '\0';
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 7; j >= 0; j--) {
            strcat(binary, ((str[i] >> j) & 1) ? "1" : "0");
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char message[500], binary[MAXLINE], dataWithZeros[MAXLINE];
    char codeword[MAXLINE], remainder[50], buffer[MAXLINE];
    int choice;
    
    // CRC Polynomials
    char *crc12 = "1100000001111";
    char *crc16 = "11000000000000101";
    char *crcCCITT = "10001000000100001";
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    // Server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Connect
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }
    
    printf("Connected to CRC Receiver\n");
    printf("========================================\n");
    
    while (1) {
        printf("\nEnter message to send (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';
        
        if (strcmp(message, "exit") == 0) {
            send(sockfd, "EXIT", 4, 0);
            break;
        }
        
        // Choose CRC
        printf("\nChoose CRC:\n1. CRC-12\n2. CRC-16\n3. CRC-CCITT\nChoice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        char *generator, crcType[20];
        switch (choice) {
            case 1: generator = crc12; strcpy(crcType, "CRC-12"); break;
            case 2: generator = crc16; strcpy(crcType, "CRC-16"); break;
            case 3: generator = crcCCITT; strcpy(crcType, "CRC-CCITT"); break;
            default: 
                printf("Invalid choice!\n");
                continue;
        }
        
        // Convert to binary
        stringToBinary(message, binary);
        
        // Append zeros
        strcpy(dataWithZeros, binary);
        int genLen = strlen(generator);
        for (int i = 0; i < genLen - 1; i++) {
            strcat(dataWithZeros, "0");
        }
        
        // Compute CRC
        computeCRC(dataWithZeros, generator, remainder);
        
        // Create codeword
        strcpy(codeword, binary);
        strcat(codeword, remainder);
        
        printf("\n--- TRANSMISSION ---\n");
        printf("Original: %s\n", message);
        printf("CRC Type: %s\n", crcType);
        printf("CRC Bits: %s\n", remainder);
        printf("Codeword length: %lu bits\n", strlen(codeword));
        
        // Send CRC type
        send(sockfd, crcType, strlen(crcType), 0);
        usleep(100000); // Small delay
        
        // Send codeword
        send(sockfd, codeword, strlen(codeword), 0);
        
        // Receive response
        memset(buffer, 0, MAXLINE);
        recv(sockfd, buffer, MAXLINE, 0);
        printf("\n--- RECEIVER RESPONSE ---\n%s\n", buffer);
        printf("========================================\n");
    }
    
    close(sockfd);
    printf("Sender terminated\n");
    return 0;
}
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

void xorOperation(char *dividend, char *divisor, int divisorLen) {
    for (int i = 1; i < divisorLen; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

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

void binaryToString(char *binary, char *str) {
    int len = strlen(binary);
    int idx = 0;
    
    for (int i = 0; i < len; i += 8) {
        char byte[9];
        strncpy(byte, &binary[i], 8);
        byte[8] = '\0';
        str[idx++] = (char)strtol(byte, NULL, 2);
    }
    str[idx] = '\0';
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLINE], crcType[20], remainder[50], response[MAXLINE];
    
    char *crc12 = "1100000001111";
    char *crc16 = "11000000000000101";
    char *crcCCITT = "10001000000100001";
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }
    
    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        exit(1);
    }
    
    printf("CRC Receiver listening on port %d...\n", PORT);
    
    len = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if (newsockfd < 0) {
        perror("Accept failed");
        exit(1);
    }
    
    printf("Sender connected\n");
    printf("========================================\n");
    
    while (1) {
        // Receive CRC type
        memset(crcType, 0, sizeof(crcType));
        int n = recv(newsockfd, crcType, sizeof(crcType), 0);
        if (n <= 0) break;
        crcType[n] = '\0';
        
        if (strcmp(crcType, "EXIT") == 0) {
            printf("Exit command received\n");
            break;
        }
        
        // Receive codeword
        memset(buffer, 0, MAXLINE);
        n = recv(newsockfd, buffer, MAXLINE, 0);
        buffer[n] = '\0';
        
        printf("\n--- RECEIVED DATA ---\n");
        printf("CRC Type: %s\n", crcType);
        printf("Codeword: %s\n", buffer);
        printf("Length: %lu bits\n", strlen(buffer));
        
        // Select generator
        char *generator;
        if (strcmp(crcType, "CRC-12") == 0) generator = crc12;
        else if (strcmp(crcType, "CRC-16") == 0) generator = crc16;
        else generator = crcCCITT;
        
        // Compute CRC
        computeCRC(buffer, generator, remainder);
        
        printf("CRC Remainder: %s\n", remainder);
        
        // Check errors
        int error = 0;
        for (int i = 0; remainder[i] != '\0'; i++) {
            if (remainder[i] == '1') {
                error = 1;
                break;
            }
        }
        
        if (error) {
            sprintf(response, "✗ ERROR DETECTED\nData is CORRUPTED");
            printf("Status: ERROR DETECTED\n");
        } else {
            // Extract original data
            int genLen = strlen(generator);
            char originalBinary[MAXLINE];
            strncpy(originalBinary, buffer, strlen(buffer) - (genLen - 1));
            originalBinary[strlen(buffer) - (genLen - 1)] = '\0';
            
            char originalData[500];
            binaryToString(originalBinary, originalData);
            
            sprintf(response, "✓ NO ERROR\nData is VALID\nOriginal Message: %s", originalData);
            printf("Status: NO ERROR\n");
            printf("Original: %s\n", originalData);
        }
        
        send(newsockfd, response, strlen(response), 0);
        printf("========================================\n");
    }
    
    close(newsockfd);
    close(sockfd);
    printf("Receiver terminated\n");
    return 0;
}
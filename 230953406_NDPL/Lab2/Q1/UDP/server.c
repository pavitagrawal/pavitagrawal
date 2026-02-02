#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAXSIZE 1024

/* Comparison function for qsort - compares two characters by ASCII value */
int char_cmp(const void *a, const void *b) {
    return *(char*)a - *(char*)b;  // Cast void* to char* then dereference
}

int main(void)
{
    int sockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE], filename[MAXSIZE], str1[MAXSIZE], str2[MAXSIZE], filecontent[MAXSIZE * 10];
    int option, count;
    FILE *fp;

    /* Create a UDP socket
     * AF_INET: IPv4 address family
     * SOCK_DGRAM: UDP (connectionless, datagram-based)
     * 0: Default protocol for SOCK_DGRAM (UDP)
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        printf("\nSocket creation error");
        exit(0);
    }

    /* Configure server address structure
     * sin_family: Address family (IPv4)
     * sin_port: Port number in network byte order
     * sin_addr.s_addr: Local IP address
     */
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3389);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Bind the socket to the configured address and port */
    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    if (retval == -1)
    {
        printf("Binding error");
        close(sockfd);
        exit(0);
    }

    actuallen = sizeof(clientaddr);

    /* Receive filename from client */
    recedbytes = recvfrom(sockfd, filename, sizeof(filename), 0, (struct sockaddr*)&clientaddr, &actuallen);

    if (recedbytes == -1)
    {
        close(sockfd);
        exit(0);
    }

    /* Check if file exists */
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        strcpy(buff, "File not present");
        sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, actuallen);
        close(sockfd);
        return 0;
    }

    /* Read file content */
    fread(filecontent, sizeof(char), sizeof(filecontent), fp);
    fclose(fp);

    /* Send file present confirmation */
    strcpy(buff, "File present");
    sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, actuallen);

    while (1)
    {
        /* Receive option from client */
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, &actuallen);
        if (recedbytes == -1) break;

        option = atoi(buff);

        if (option == 4)
        {
            break;
        }

        if (option == 1)
        {
            /* Receive string to search */
            recedbytes = recvfrom(sockfd, str1, sizeof(str1), 0, (struct sockaddr*)&clientaddr, &actuallen);
            if (recedbytes == -1) break;

            /* Count occurrences of str1 in file */
            count = 0;
            char *pos = filecontent;
            while ((pos = strstr(pos, str1)) != NULL)
            {
                count++;
                pos += strlen(str1);
            }

            if (count > 0)
            {
                sprintf(buff, "%d", count);
            }
            else
            {
                strcpy(buff, "String not found");
            }

            sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, actuallen);
        }
        else if (option == 2)
        {
            /* Receive str1 and str2 */
            recedbytes = recvfrom(sockfd, str1, sizeof(str1), 0, (struct sockaddr*)&clientaddr, &actuallen);
            if (recedbytes == -1) break;

            recedbytes = recvfrom(sockfd, str2, sizeof(str2), 0, (struct sockaddr*)&clientaddr, &actuallen);
            if (recedbytes == -1) break;

            /* Check if str1 exists in file */
            if (strstr(filecontent, str1) == NULL)
            {
                strcpy(buff, "String not found");
            }
            else
            {
                /* Replace str1 with str2 */
                char *pos;
                while ((pos = strstr(filecontent, str1)) != NULL)
                {
                    memmove(pos + strlen(str2), pos + strlen(str1), strlen(pos + strlen(str1)) + 1);
                    memcpy(pos, str2, strlen(str2));
                }

                /* Write back to file */
                fp = fopen(filename, "w");
                fwrite(filecontent, sizeof(char), strlen(filecontent), fp);
                fclose(fp);

                strcpy(buff, "String replaced");
            }

            sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, actuallen);
        }
        else if (option == 3)
        {
            /* Reorder file content by ASCII value using qsort */
            int len = strlen(filecontent);

            /* qsort(array, count, element_size, comparison_function) */
            /* Sorts array in-place using quicksort algorithm */
            qsort(filecontent, len, sizeof(char), char_cmp);

            /* Write back to file */
            fp = fopen(filename, "w");
            fwrite(filecontent, sizeof(char), len, fp);
            fclose(fp);

            strcpy(buff, "File reordered");
            sentbytes = sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientaddr, actuallen);
        }
    }

    close(sockfd);

    return 0;
}
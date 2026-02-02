#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 1024

/* Comparison function for qsort - compares two characters by ASCII value */
int char_cmp(const void *a, const void *b) {
    return *(char*)a - *(char*)b;  // Cast void* to char* then dereference
}

int main(void)
{
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE], filename[MAXSIZE], str1[MAXSIZE], str2[MAXSIZE], filecontent[MAXSIZE * 10];
    int option, count;
    FILE *fp;

    /* Create a TCP socket
     * AF_INET: IPv4 address family
     * SOCK_STREAM: TCP (reliable, connection-oriented byte stream)
     * 0: Default protocol for SOCK_STREAM (TCP)
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("\nSocket creation error");
        exit(0);
    }

    /* Configure server address structure
     * sin_family: Address family (IPv4)
     * sin_port: Port number in network byte order
     * sin_addr.s_addr: Any local IP address
     */
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

    /* Bind the socket to the configured address and port */
    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    if (retval == -1)
    {
        printf("Binding error");
        close(sockfd);
        exit(0);
    }

    /* Mark the socket as passive (listening for incoming connections) */
    retval = listen(sockfd, 1);

    if (retval == -1)
    {
        close(sockfd);
        exit(0);
    }

    actuallen = sizeof(clientaddr);

    /* Accept an incoming connection from a client */
    newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &actuallen);

    if (newsockfd == -1)
    {
        close(sockfd);
        exit(0);
    }

    /* Receive filename from client */
    recedbytes = recv(newsockfd, filename, sizeof(filename), 0);

    if (recedbytes == -1)
    {
        close(sockfd);
        close(newsockfd);
        exit(0);
    }

    /* Check if file exists */
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        strcpy(buff, "File not present");
        sentbytes = send(newsockfd, buff, sizeof(buff), 0);
        close(sockfd);
        close(newsockfd);
        return 0;
    }

    /* Read file content */
    fread(filecontent, sizeof(char), sizeof(filecontent), fp);
    fclose(fp);

    /* Send file present confirmation */
    strcpy(buff, "File present");
    sentbytes = send(newsockfd, buff, sizeof(buff), 0);

    while (1)
    {
        /* Receive option from client */
        recedbytes = recv(newsockfd, buff, sizeof(buff), 0);
        if (recedbytes == -1) break;

        option = atoi(buff);

        if (option == 4)
        {
            break;
        }

        if (option == 1)
        {
            /* Receive string to search */
            recedbytes = recv(newsockfd, str1, sizeof(str1), 0);
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

            sentbytes = send(newsockfd, buff, sizeof(buff), 0);
        }
        else if (option == 2)
        {
            /* Receive str1 and str2 */
            recedbytes = recv(newsockfd, str1, sizeof(str1), 0);
            if (recedbytes == -1) break;

            recedbytes = recv(newsockfd, str2, sizeof(str2), 0);
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

            sentbytes = send(newsockfd, buff, sizeof(buff), 0);
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
            sentbytes = send(newsockfd, buff, sizeof(buff), 0);
        }
    }

    close(sockfd);
    close(newsockfd);

    return 0;
}
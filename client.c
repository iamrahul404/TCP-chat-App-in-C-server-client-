//
// Created by root on 10/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUFFER 1024

int main() {
    int clntSock,a;
    struct sockaddr_in servAddr;
    char *servIP = "127.0.0.1";
    char str[25],str1[25];
    char *string;
    int stringLen;
    int totalBytesRcvd, bytesRcvd;

    if ((clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("error here at socket creation");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8877);
    servAddr.sin_addr.s_addr = inet_addr(servIP);
    if (connect(clntSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        printf("error in connection making");
    //memset(string,'\0', sizeof(string));

    printf("\n we are connected to %s",servIP);
    printf("\nCLIENT::: ");
    scanf("%s",str);
    if (write(clntSock,str, sizeof(str))<0)
        printf("data could not be send");

    do{
        listen(clntSock,1);
        read(clntSock,str1, sizeof(str1));
        printf("\nSERVER MSG::: %s",str1);
        printf("\nCLIENT MSG::: ");
        scanf("%s",str);
        a = strcmp(str1,"BYE");
        write(clntSock,str, sizeof(str1));
    }while (a!=0);
    close(clntSock);

    return 0;
}
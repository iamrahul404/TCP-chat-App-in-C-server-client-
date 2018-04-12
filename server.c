//
// Created by root on 10/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXPENDING 5


int main(){
    int serverSock,clntSock,clntLen,n,a;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    unsigned int servPort;
    char str[25],str1[25];
    servPort = 8877;
    if((serverSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
        printf("Problem in creating socket\n");
    memset(&servAddr,0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);
    if (bind(serverSock,(struct sockaddr*)&servAddr, sizeof(servAddr))<0)
        printf("error in binding");

    if (listen(serverSock,1)<0)
        printf("error here at listening");
    clntLen = sizeof(clntAddr);

    if ((clntSock = accept(serverSock,(struct sockaddr *)&clntAddr ,&clntLen ))<0)
        printf("error in accept");
    else
        printf("\n now connected to %s\n",inet_ntoa(clntAddr.sin_addr));

    read(clntSock,str, sizeof(str));

    do{
        printf("\nCLIENT MSG::: %s",str);
        printf("\nSERVER MSG::: ");
        scanf("%s",str1);
        write(clntSock,str1, sizeof(str1));
        listen(clntSock,1);
        read(clntSock,str, sizeof(str));
        n = strcmp(str,"BYE");
        a = strcmp(str1,"BYE");

    }while(n!=0 && a!=0);

    close(clntSock);
    close(serverSock);
    return 0;

}


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 2048
#define PORT 8000
int main()
{
    int sock_fd,rec_len;
    char recvline[2048],sendline[2048];
    char buf[MAXLINE];
    struct sockaddr_in clientaddr;


    if((sock_fd = socket(AF_INET, SOCK_STREAM,0))==-1)
    {
        printf("socket link error\n");
    }
    memset(&clientaddr,0,sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port =htons( PORT);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((connect(sock_fd,(struct sockaddr*)&clientaddr,sizeof(clientaddr)))==-1)
    {
        printf("connect errot\n");
        exit(0);
    }
    while(fgets(sendline,2048,stdin) != NULL)
    {

        printf("send message to sever:%s\n",sendline);

        send(sock_fd,sendline, sizeof(sendline),0);

        rec_len = recv(sock_fd,buf,MAXLINE,0);
        if(sendline=="exit")
        {
            printf("exit link\n");
            break;
        }
        buf[rec_len] = '\0';
        printf("receive:%s\n",buf);


    }

    close(sock_fd);

    exit(0);
}

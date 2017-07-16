#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

#define PORT 8000
#define QUEN 20
#define MAXLINE 2048
int main()
{
    int sock_fd,connect_fd;
    char BUFFER[2048];
    int n;
    struct sockaddr_in severaddr;
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    memset(&severaddr,0,sizeof(severaddr));
    severaddr.sin_family = AF_INET;
    severaddr.sin_port = htons(PORT);
    severaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(sock_fd,(struct sockaddr*)&severaddr, sizeof(severaddr)))==-1)
    {
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    if(listen(sock_fd,QUEN)==-1)
    {
        printf("listen error");
    }
    printf("=============wating for client=========================\n");

    connect_fd = accept(sock_fd,(struct sockaddr*)NULL, NULL);
    while((n = recv(connect_fd,BUFFER,MAXLINE,0))>0)
    {
        if(!fork())  //son
        {
            if((send(connect_fd,BUFFER,sizeof(BUFFER),0)) == -1)
                perror("send error");
            BUFFER[n]='\0';
            printf("receive message from client:  %s\n",BUFFER);
            close(connect_fd);
            exit(0);
        }
        if((strcmp(BUFFER,"exit"))==0)
        {
            printf("exit link");
            break;
        }
    }

    close(connect_fd);
    close(sock_fd);

}

#include <stdio.h>

#include <sys/socket.h>

#include <string.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <stdlib.h>

#define FILE_NAME_SIZE 512

#define PORT 8000

#define BUFFERSIZE 1024

int main()

{

        int sock_id, bind_id;

        struct sockaddr_in severaddr;

        if((sock_id = socket(AF_INET,SOCK_DGRAM,0)) == -1)

        {

                printf("socket error");

                exit(0);

        }

        memset(&severaddr,0, sizeof(severaddr));

        severaddr.sin_family = AF_INET;

        severaddr.sin_port = htons(PORT);

        severaddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if((bind_id = bind(sock_id, (struct sockaddr*)&severaddr, sizeof(severaddr))) == -1)

        {                 printf("bind error");                 exit(0);         }

        while(1)

        {

                struct sockaddr_in clientaddr;

                socklen_t clientaddr_length = sizeof(clientaddr);

                char recvbuf[BUFFERSIZE];

                bzero(recvbuf, BUFFERSIZE);

                if((recvfrom(sock_id,recvbuf,BUFFERSIZE,0,(struct sockaddr*)&clientaddr,&clientaddr_length))==-1)

                {                         printf("recv error");                         exit(0);                 }

                char file_name[FILE_NAME_SIZE];

                bzero(file_name, FILE_NAME_SIZE);

                strncpy(file_name,recvbuf,strlen(recvbuf)>FILE_NAME_SIZE?FILE_NAME_SIZE:strlen(recvbuf));
                printf("%s\n",file_name);
        }
        close(sock_id);
        return 0;
}

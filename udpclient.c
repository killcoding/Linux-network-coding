#include <stdio.h>

#include <stdlib.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>

#include <errno.h>

#define PORT 8000

#define BUFFER_SIZE 1024

int main()

{

        int sock_id;

        struct sockaddr_in clientaddr;

        if((sock_id = socket(AF_INET, SOCK_DGRAM, 0)) == -1)

        {                 perror("sock error");                 exit(1);         }

        memset(&clientaddr, 0, sizeof(clientaddr));

        clientaddr.sin_family = AF_INET;

        clientaddr.sin_port   = htons(PORT);

        clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        char file_name[BUFFER_SIZE];

        bzero(file_name, BUFFER_SIZE);

        scanf("%s\n",file_name);

        if(sendto(sock_id, file_name, BUFFER_SIZE, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) <0)

        {                 perror("send error");                 exit(1);         }

        close(sock_id);

        return 0;

}

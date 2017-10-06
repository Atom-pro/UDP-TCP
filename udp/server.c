/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Thu Oct  5 23:34:13 2017
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main()
{
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd == -1){
        perror("socket"), exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000);
    inet_aton("127.0.0.1", &addr.sin_addr);
    
    int r = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    if(r == -1){
        perror("bind");
        exit(1);
    }

    char buf[1024];
    struct sockaddr_in paddr;
    socklen_t addrlen;
    for(;;){
        memset(buf, 0, sizeof(buf));
        addrlen = sizeof(paddr);
        recvfrom(sfd, buf, 1024, 0, (struct sockaddr*)&paddr, &addrlen);
        sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&paddr, addrlen);
        printf("%s\n", buf);
    }
}

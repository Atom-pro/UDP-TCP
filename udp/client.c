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
    char buf[1024] = {};
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sfd == -1){
        perror("socket"), exit(0);
    }

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000);
    inet_aton("127.0.0.1", &addr.sin_addr);
    
    while(fgets(buf, 1024, stdin) != NULL){
        sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, len);
        recvfrom(sfd, buf, 1024, 0, NULL, NULL);
        printf("buf = %s", buf);
    }
}

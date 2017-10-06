/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 Oct 2017 01:09:40 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>



int main(int argc, char* argv[])
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket\n");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    int cli = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(cli == -1){
        perror("connect\n");
        exit(2);
    }

    while( 1 ){
        char buf[1024];
        printf("Please Enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf, 1024);
        if(s <= 0){
            perror("read\n");
            exit(3);
        }
        buf[s-1] = 0;
        write(sock, buf, strlen(buf));
        ssize_t r = read(sock, buf, sizeof(buf));
        printf("server say#  %s\n", buf);
        memset(buf, 0, sizeof(buf));
    }
    close(sock);
    close(cli);
}

/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 04 Oct 2017 12:32:08 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<signal.h>
        
int main(int arg, char* argv[])
{
    /*
     * struct sigaction act;
     * act.sa_handler = handler;
     * sigemptyset(&act.sa_mask);
     * act.sa_flags = 0;
     * sigaction(SIGCHLD, &act, NULL);
    */
    if(arg != 3){
        printf("Usage \n");
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket\n");
        exit(2);
    }
    
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        perror("bind\n");
        exit(3);
    }
    if(listen(sock, 10) < 0){
        perror("listen\n"); 
        exit(4);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    while(1){
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int newsock = accept(sock, (struct sockaddr*)&peer, &len );
        if(newsock < 0){
            perror("accept\n");
            exit(5);
        }

        printf("get new client [%s:%d]\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));

        pid_t id = fork();
        if(id < 0){
            perror("fork");
            exit(6);
        }else if(id == 0){
            close(sock);
            if(fork() > 0){
                exit(0);
            }
            while(1){
                char buf[1024];
                ssize_t s = read(newsock, buf, 1024);
                if(s > 0){
                    buf[s] = 0;
                    printf("client say# %s\n", buf);
                    write(newsock, buf, sizeof(buf));
                }else if(s == 0){
                    printf("client quit...\n");
                    break;
                }
            }
            close(sock);    
        }else{
            close(newsock); 
        }
}
}

/*************************************************************************
	> File Name: Server.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月06日 星期二 19时12分05秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"
int socket_create(int port) {
    int sockfd;
    int yes = 1;
    struct sockaddr_in sock_addr;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket() error: ");
        return -1;
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        close(sockfd);
        perror("setsockopt() error\n");
    }
    if (bind(sockfd, (struct sockaddr *)&sock_addr, sizeof (sock_addr))) {
        close(sockfd);
        perror("bind() error\n");
        return -1;
    }
    if (listen(sockfd, 20) < 0) {
        close(sockfd);
        perror("listen error:");
        return -1;
    }
    return sockfd;
}


int main(int argc, char *argv[]) {
	int a = 0;
	
    int server_listen, socketfd, port, pid;

	if (argc != 2) {
		printf("Usage: ./tcp_server port\n");
		exit(0);
	}

	port = atoi(argv[1]);

	if ((server_listen = socket_create(port)) < 0 ) {
		printf("Error creating server_listen socket");
		exit(1);
	}
    char name[1000];

	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	socketfd = accept(server_listen, (struct sockaddr*) &client_addr, &len);
	struct sockaddr_in peer;
	socklen_t peer_len = sizeof(struct sockaddr_in);
	bzero(&peer, sizeof(struct sockaddr_in));
	getpeername(socketfd, (struct sockaddr *)&peer, &peer_len);
	char buff_peer[64] = {'\0'};
	inet_ntop(AF_INET, (void*)&peer.sin_addr, buff_peer, 63);
	char buffer[10];    
	while (1) {
        if (recv(socketfd, buffer, 10, 0)) {
            printf("%s", buffer);
            fflush(stdout);
            memset(buffer, 0, sizeof(buffer));
        }
    }
}

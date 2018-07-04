/*************************************************************************
	> File Name: server.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月04日 星期日 19时56分34秒
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
int socket_accept(int sock_listen) {
    int sockfd;
    struct sockaddr_in client_addr, server_addr;
    char buffer[1000];
    socklen_t len = sizeof(client_addr);
    sockfd = accept(sock_listen, (struct sockaddr *)&client_addr, &len);
    getsockname(sockfd, (struct sockaddr *)&server_addr, &len);
    if (sockfd < 0) {
        perror("accept () error\n");
        return -1;
    }
    sprintf(buffer, "%s:%d ---> you have connnected to Server !!", inet_ntoa(server_addr.sin_addr), sock_listen);
    send(sockfd, buffer, strlen(buffer),0);
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

	while(1) {
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);
		if((socketfd = accept(server_listen, (struct sockaddr*) &client_addr, &len)) < 0)
			break;


		struct sockaddr_in peer;
		socklen_t peer_len = sizeof(struct sockaddr_in);
		bzero(&peer, sizeof(struct sockaddr_in));
		getpeername(socketfd, (struct sockaddr *)&peer, &peer_len);
		char buff_peer[64] = {'\0'};
		inet_ntop(AF_INET, (void*)&peer.sin_addr, buff_peer, 63);


		if ((pid = fork()) < 0)
			printf("Error forking child process");
		if (pid == 0) {
			close(server_listen);
			char buffer[1000];
            memset(buffer, 0, sizeof(char) * 1000);//用之前保证reset,否则第一次结尾可能有乱码
			while ((a = recv(socketfd, buffer, 1000, 0)) >  0 ) {
                printf ("buffer = %s\n", buffer);
				printf("%s:%d : recv %d 字节  %s\n", buff_peer, ntohs(peer.sin_port), a, buffer);
				fflush(stdout);
				memset(buffer, 0, sizeof(buffer));
			}
			printf("\n");
			close(socketfd);
			exit(0);

		}
		close(socketfd);
	}
	return 0;
}

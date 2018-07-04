/************************************mZ************************************
	> File Name: client.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月06日 星期二 17时27分24秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"

int socket_connect(int port, char *host) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() error");
        return -1;
    }
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if (connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("connect perror");
        printf ("connect wrong!\n");
        fflush(stdout);
        return -1;
    }
    return sockfd;
}


       
int main() {
    char host[20] = "192.168.0.114";
    int sockfd = socket_connect(6666, host);
    printf ("sockfd = %d\n", sockfd);
    char buffer[100];
    while (~scanf("%s", buffer)) {
        fflush(stdout);
        send(sockfd, buffer, strlen(buffer), 0);
        fflush(stdout);
        memset(buffer, 0, sizeof(char) * 100);
    }
    return 0;
}

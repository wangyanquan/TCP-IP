/*************************************************************************
	> File Name: my_client.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月07日 星期三 08时57分26秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"

//#define host "192.168.0.114"
//#define port 6666
int main() {
    int PID;
    int count = 0;
    int sockfd;
    for (int i = 0; i < 3; i++) {
        count++;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("count = %d, sockfd = %d\n", count, sockfd);
        PID = fork();
        if (PID == 0) break;
    }
    int port = 6666;
    char host[] = "192.168.1.82";
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof (dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(host);
    dest_addr.sin_port = htons(port);
    if (PID != 0) 
        return 0;
    else {
        while(1) {
            if (count == 1) {
                printf("count = %d, sockfd = %d\n", count, sockfd);
                connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                sleep(5);
                sleep(0.3);
                FILE *f = popen("ls", "r");
                char *buffer = calloc(1000, sizeof(char));
                while (fgets(buffer, 1000, f)) {
                    send(sockfd, buffer, strlen(buffer), 0);
                 //   printf("buffer = %s\n", buffer);
                    memset(buffer, 0, sizeof(buffer));
                }
                pclose(f);
            }
            else if (count == 2) {
                printf("count = %d, sockfd = %d\n", count, sockfd);
                connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                sleep(5);
                sleep(0.6);
                FILE *f = popen("uname -a", "r");
                char *buffer = calloc(1000, sizeof(char));
                while (fgets(buffer, 1000, f)) {
                    send(sockfd, buffer, strlen(buffer), 0);
                 //   printf("buffer = %s\n", buffer);
                    memset(buffer, 0, sizeof(buffer));
                }
                pclose(f);
            } 
            else if (count == 3) {
                printf("count = %d, sockfd = %d\n", count, sockfd);
                connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
                sleep(5);
                sleep(0.9);
                FILE *f = popen("pwd", "r");
                char *buffer = calloc(1000, sizeof(char));
                while (fgets(buffer, 1000, f)) {
                    send(sockfd, buffer, strlen(buffer), 0);
                 //   printf("buffer = %s\n", buffer);
                    memset(buffer, 0, sizeof(buffer));
                }
                pclose(f);
            }   
        }
    }
    return 0;
}

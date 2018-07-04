/*************************************************************************
	> File Name: my_server.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月07日 星期三 13时51分53秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("need argv!\n");
        return 0;
    }
    // 1 socket()
    int my_sockfd;
    my_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sockfd < 0) {
        printf("socket() wrong!\n");
        perror("socket() wrong: ");
    }
    else {
        printf("socket() OK!\n ");
    }
    // 2 bind()
    struct sockaddr_in sock_addr;
    int port = atoi(argv[1]);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_addr.sin_port = htons(port);
    if (bind(my_sockfd, (struct sockaddr *)&sock_addr, sizeof (sock_addr))) {
        printf ("bind() wrong!\n");
        perror("bind() error: ");
        return 0;
    }
    else {
        printf ("bind() ok!\n");
    }
    // 3 listen() 
    if (listen(my_sockfd, 20) < 0) {
        close(my_sockfd);
        printf ("listen() wrong!\n");
        perror("listrn() wrong!\n");
    }
    else {
        printf ("listen() ok!\n");
    }
    // 4 accept()
    int rec_sockfd;
    struct sockaddr_in client_message;
    socklen_t len = sizeof(struct sockaddr_in);
    while(1) {
        int PID;
        int count = 0;
        for (int i = 0; i < 3; i++) {
            PID = fork();
            count++;
            if (PID == 0) break;
        }
        if(PID != 0) return 0;
        else {
            if (count == 1) {
               
                rec_sockfd = accept(my_sockfd, (struct sockaddr *)&client_message, &len);
                printf("rec_sockfd = %d\n", rec_sockfd);
                if (rec_sockfd < 0) {
                    printf ("accpet() wrong!\n");
                    return 0;
                }
                else {
                    printf ("accept() success!\n");
                }
                getpeername(rec_sockfd, (struct sockaddr *)&client_message, &len);
                char rec_addr[50] = {'\0'};
                int rec_port;
                inet_ntop(AF_INET, (void *)&client_message.sin_addr, rec_addr, 49);
                rec_port = ntohs(client_message.sin_port);
                printf ("rec_port = %d\n", rec_port);
                printf ("rec_addr = %s\n", rec_addr);
                // 接受字符串

                char command[100] = "/home/quan/linux/TCP项目/output/";
                char *file_name = (char *) calloc (10, sizeof(char));
                file_name[0] = '0' + count;
                strcat(command, file_name);
                FILE *pout = fopen(command, "a+");
                char *rec_buf = (char *) calloc(1000, sizeof(char));
                int rec_count;
                while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) {
                    FILE *pout = fopen(command, "a+");
                    fprintf(pout, "%s", rec_buf);
                    printf("-------------------------------------\n");
                    printf("count = %d, rec_sockfd = %d\n", count, rec_sockfd);
                    printf("rec_buf = %s\n", rec_buf);
                    fflush(stdout);
                    memset(rec_buf, 0, 1000);
                    fclose(pout);
                }
                fclose(pout);
            }

            else if (count == 2) {
               
                rec_sockfd = accept(my_sockfd, (struct sockaddr *)&client_message, &len);
                printf("rec_sockfd = %d\n", rec_sockfd);
                if (rec_sockfd < 0) {
                    printf ("accpet() wrong!\n");
                    return 0;
                }
                else {
                    printf ("accept() success!\n");
                }
                getpeername(rec_sockfd, (struct sockaddr *)&client_message, &len);
                char rec_addr[50] = {'\0'};
                int rec_port;
                inet_ntop(AF_INET, (void *)&client_message.sin_addr, rec_addr, 49);
                rec_port = ntohs(client_message.sin_port);
                printf ("rec_port = %d\n", rec_port);
                printf ("rec_addr = %s\n", rec_addr);
                // 接受字符串

                char command[100] = "/home/quan/linux/TCP项目/output/";
                char *file_name = (char *) calloc (10, sizeof(char));
                file_name[0] = '0' + count;
                strcat(command, file_name);
                FILE *pout = fopen(command, "a+");
                char *rec_buf = (char *) calloc(1000, sizeof(char));
                int rec_count;
                while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) {
                    FILE *pout = fopen(command, "a+");
                    fprintf(pout, "%s", rec_buf);
                    printf("-------------------------------------\n");
                    printf("count = %d, rec_sockfd = %d\n", count, rec_sockfd);
                    printf("rec_buf = %s\n", rec_buf);
                    fflush(stdout);
                    memset(rec_buf, 0, 1000);
                    fclose(pout);
                }
                fclose(pout);
            }

            else if (count == 3) {
               
                rec_sockfd = accept(my_sockfd, (struct sockaddr *)&client_message, &len);
                printf("rec_sockfd = %d\n", rec_sockfd);
                if (rec_sockfd < 0) {
                    printf ("accpet() wrong!\n");
                    return 0;
                }
                else {
                    printf ("accept() success!\n");
                }
                getpeername(rec_sockfd, (struct sockaddr *)&client_message, &len);
                char rec_addr[50] = {'\0'};
                int rec_port;
                inet_ntop(AF_INET, (void *)&client_message.sin_addr, rec_addr, 49);
                rec_port = ntohs(client_message.sin_port);
                printf ("rec_port = %d\n", rec_port);
                printf ("rec_addr = %s\n", rec_addr);
                // 接受字符串

                char command[100] = "/home/quan/linux/TCP项目/output/";
                char *file_name = (char *) calloc (10, sizeof(char));
                file_name[0] = '0' + count;
                strcat(command, file_name);
                FILE *pout = fopen(command, "a+");
                char *rec_buf = (char *) calloc(1000, sizeof(char));
                int rec_count;
                while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) {
                    FILE *pout = fopen(command, "a+");
                    fprintf(pout, "%s", rec_buf);
                    printf("-------------------------------------\n");
                    printf("count = %d, rec_sockfd = %d\n", count, rec_sockfd);
                    printf("rec_buf = %s\n", rec_buf);
                    fflush(stdout);
                    memset(rec_buf, 0, 1000);
                    fclose(pout);
                }
                fclose(pout);
            }
        }
    }
    return 0;
}

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
        rec_sockfd = accept(my_sockfd, (struct sockaddr *)&client_message, &len);
        if (rec_sockfd < 0) {
            printf ("accpet() wrong!\n");
            return 0;
        }
        else {
            printf ("accept() success!\n");
            printf("rec_sockfd = %d\n", rec_sockfd);
        }
        getpeername(rec_sockfd, (struct sockaddr *)&client_message, &len);
        char rec_addr[50] = {'\0'};
        int rec_port;
        inet_ntop(AF_INET, (void *)&client_message.sin_addr, rec_addr, 49);
        rec_port = ntohs(client_message.sin_port);
        printf ("rec_port = %d\n", rec_port);
        printf ("rec_addr = %s\n", rec_addr);
        // 接受字符串,区分操作opt
        int rec_count;
        char *rec_buf = (char *) calloc (1000, sizeof(char));
        char one[] = "1", two[] = "2", three[] = "3";
        recv(rec_sockfd, rec_buf, 1000, 0);  //接受opt

        if ((strcmp(rec_buf, one)) == 0) {
            printf ("opt = 1\n");
            memset(rec_buf, 0, sizeof(rec_buf));
            while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) { 
                printf("rec_count = %d. rec_buf = %s\n", rec_count, rec_buf);
                memset(rec_buf, 0, sizeof(rec_buf)); //recv函数不像scanf函数,接收到的变量结尾不会自动加\0
            }                                        //所以每次用完memset一下,否则乱码
        }

        else if ((strcmp(rec_buf, two) == 0)) {
            printf("opt = 2\n");
            memset(rec_buf, 0, sizeof(rec_buf));
            char locate[100] = "/home/quan/linux/TCP项目/output/";
            recv(rec_sockfd, rec_buf, 1000, 0);
            strcat(locate, rec_buf);
            memset(rec_buf, 0, sizeof(rec_buf));
            printf("locate = %s locate done\n", locate);
            fflush(stdout);
            FILE *fout = fopen(locate, "w");
            memset(rec_buf, 0, sizeof(rec_buf));
            fflush(stdout);
            while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) {
                fflush(stdout);
                fprintf(fout, "%s", rec_buf);
                printf ("test = %s\n", rec_buf);
                fflush(stdout);
                memset(rec_buf, 0, sizeof(rec_buf));
            }
            fclose(fout);
        }
            
        else if ((strcmp(rec_buf, three) == 0)) {
            printf("opt = 3\n");
            memset(rec_buf, 0, sizeof(rec_buf));
            char command[100] = "/home/quan/linux/TCP项目/output/command";
            FILE *f_com = fopen(command, "w");
            while ((rec_count = recv(rec_sockfd, rec_buf, 1000, 0)) > 0) {
                fprintf(f_com, "%s", rec_buf);
                printf ("command = %s\n", rec_buf);
                fflush(stdout);
                memset(rec_buf, 0, sizeof(rec_buf));
            }
            fclose(f_com);

        }
    }    
    return 0;
}

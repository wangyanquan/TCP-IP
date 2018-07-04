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
    // 1 socket()
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf ("wrong socket()!\n");
        perror("socket() error");
    }
    else {
        printf ("socket() ok, sockfd = %d\n", sockfd);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf ("wrong socket()!\n");
        perror("socket() error");
    }
    else {
        printf ("socket() ok, sockfd = %d\n", sockfd);
    }
    // 2 connect()
    int port = 6666;
    char host[] = "192.168.1.82";
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof (dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(host);
    dest_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf ("connect() wrong!\n");
        perror("connect perror");
    }
    else {
        printf ("connect() ok\n");
    }
    // 3 send()
    char *buffer = (char *) calloc(1000, sizeof(char));
    char opt;
    printf ("please input opt\n");
    scanf("%c", &opt);            //千万不能写成%s,否则无法发送
    switch(opt) {
        case '1':
            send(sockfd, "1", 1, 0);
            printf("please input buffer\n");
            getchar();
            while(~scanf("%[^\n]s", buffer)) {
                getchar();
                printf ("buffer = %s\n", buffer);
                send(sockfd, buffer, strlen(buffer), 0);
                memset(buffer, 0, sizeof(buffer));
            }
        break;
        case '2':
            send(sockfd, "2", 1, 0);
            printf ("please input filename\n");
            scanf("%s", buffer);
            send(sockfd, buffer, strlen(buffer), 0);
            sleep(1);   //不加sleep会导致服务端来不及创建文件,导致段错误
            FILE *f = fopen(buffer, "r");
            memset(buffer, 0, 1000);
            while (fgets(buffer, 1000, f)) {   //fgets函数的第二个参数为buffer空间大小,不是strlen大小
              //  printf("content = %s\n", buffer);    //fgets每次会读空间大小减一个字符,最后添'\0'
                send(sockfd, buffer, strlen(buffer), 0); //如果改为strlen大小,每次都会读入比上次少一个,直到为0个
                memset(buffer, 0, sizeof (buffer));      //printf打印到屏幕上会影响输出
            }
            fclose(f);
        break;
        case '3':
            send(sockfd, "3", 1, 0);
            printf("please input command\n");
            getchar();
            scanf("%[^\n]s", buffer);
            FILE *fp = NULL;
            fp = popen(buffer, "r");
            memset(buffer, 0, sizeof(buffer));
            while (fgets(buffer, 1000, fp)) {
               // printf("%s", buffer);      //此输出会影响传输
                send(sockfd, buffer, strlen(buffer), 0);
                memset(buffer, 0, sizeof(buffer));
            }
            pclose(fp);
        
        break;
    }
}

/*************************************************************************
	> File Name: my.h
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月04日 星期日 19时47分39秒
 ************************************************************************/

#ifndef _MY_H
#define _MY_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#define IP "192.168.1.121"
#define share_con_port "17207"
#define link_con_port 17207

#define need_cpu 11
#define need_mem 12
#define need_disk 13
#define need_sys 14
#define need_user 15
#define send_cpu "11"
#define send_mem "12"
#define send_disk "13"
#define send_sys "14"
#define send_user "15"

#define share_cpu_port "17307"
#define share_mem_port "17407"
#define share_disk_port "17507"
#define share_sys_port "17607"
#define share_user_port "17707"
#define share_warning_port "17807"

#define link_cpu_port 17307
#define link_mem_port 17407
#define link_disk_port 17507
#define link_sys_port 17607
#define link_user_port 17707
#define link_warning_port 17807

#define yes 1
#define no 0
#define pi1_host "192.168.1.40"
#define pi2_host "192.168.1.41"
#define pi3_host "192.168.1.42"
#define pi4_host "192.168.1.43"
#define pi5_host "192.168.1.44"
#define pi6_host "192.168.1.45"
#define pi7_host "192.168.1.46"
#define pi8_host "192.168.1.47"
#define pi9_host "192.168.1.48"
#define pi10_host "192.168.1.49"
#define DEBUG
#ifdef DEBUG
#define p(format, a...) {\
    printf(format, ##a);\
}

#else
#define p(a) {}
#endif
int stringtoint(char *str);
int create_socket();
void begin_connect(int sockfd, int port, char *host);
void begin_bind(int my_sockfd, char *str_port);
void begin_listen(int my_sockfd);
int begin_accept(int my_sockfd, struct sockaddr_in *master_message, socklen_t *len);

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        p ("wrong socket()!\n");
        perror("socket() error");
    }
    else {
        p ("socket() ok, sockfd = %d\n", sockfd);
    }
    return sockfd;
}
void set_socket(int sockfd) {
    int Yes = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &Yes, sizeof(int)) == -1) {
        close(sockfd);
        perror("setsockopt() error\n");
    }
}

void begin_connect(int sockfd, int port, char *host) {
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof (dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(host);
    dest_addr.sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        p ("connect() wrong!\n");
        perror("connect perror");
        char *path_master = "/home/quan/linux/TCP项目/master/log";
        FILE *f_master = fopen(path_master, "a+");
        fprintf(f_master, "connect to %s failed, port is %d.\n", host, port);
        fclose(f_master);
    }
    else {
        p ("you have connect() ok\n");
        p ("his IP is %s\n", host);
    }
}
int stringtoint(char *str) {
    int ret;
    sscanf(str, "%d", &ret);
    return ret;
}
void begin_bind(int my_sockfd, char *str_port) {
    struct sockaddr_in sock_addr;
    int port = atoi(str_port);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_addr.sin_port = htons(port);
    if (bind(my_sockfd, (struct sockaddr *)&sock_addr, sizeof (sock_addr))) {
        p ("bind() wrong!\n");
        perror("bind() error: ");
        char *path_master = "/home/quan/linux/TCP项目/master/log";
        FILE *f_master = fopen(path_master, "a+");
        fprintf(f_master, "bind socket %d failed, port is %s.\n", my_sockfd, str_port);
        fclose(f_master);
        return ;
    }
    else {
        p ("bind() ok!\n");
    }
    return;
}
void begin_listen(int my_sockfd) {
    if (listen(my_sockfd, 20) < 0) {
        close(my_sockfd);
        p ("listen() wrong!\n");
        perror("listrn() wrong!\n");
        char *path_master = "/home/quan/linux/TCP项目/master/log";
        FILE *f_master = fopen(path_master, "a+");
        fprintf(f_master, "lsten socket %d failed.\n", my_sockfd);
        fclose(f_master);
    }
    else {
        p ("listen() ok!\n");
    }
    return;
}
int begin_accept(int my_sockfd, struct sockaddr_in *master_message, socklen_t *len) {
    int rec_sockfd = accept(my_sockfd, (struct sockaddr *)master_message, len);
    if (rec_sockfd < 0) {
        p ("accpet() wrong!\n");
        char *path_master = "/home/quan/linux/TCP项目/master/log";
        FILE *f_master = fopen(path_master, "a+");
        fprintf(f_master, "accept socket %d failed.\n", my_sockfd);
        fclose(f_master);
        return 0;
    }
    else {
        p ("accept() success!\n");
        p("rec_sockfd = %d\n", rec_sockfd);
    }
    return rec_sockfd;
}
void master_log(char *ip, int con_port, char *type, int type_port) {
    char *path_master = "/home/quan/linux/TCP项目/master/log";
    FILE *f_master = fopen(path_master, "a+");
    fprintf(f_master, "his IP is %s, control link port is %d, receive type is %s, type port is %d\n", ip, con_port, type, type_port);
    fclose(f_master);
}
#endif

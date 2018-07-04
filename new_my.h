/*************************************************************************
	> File Name: new_my.h
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 19时30分30秒
 ************************************************************************/

#ifndef _NEW_MY_H
#define _NEW_MY_H
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

#define IP "192.168.1.81"
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

 
#define _1_path_cpu "/home/quan/linux/TCP项目/1/save_cpu"
#define _1_path_mem "/home/quan/linux/TCP项目/1/save_mem"
#define _1_path_disk "/home/quan/linux/TCP项目/1/save_disk"
#define _1_path_sys "/home/quan/linux/TCP项目/1/save_sys"
#define _1_path_user "/home/quan/linux/TCP项目/1/save_user"

#define _2_path_cpu "/home/quan/linux/TCP项目/2/save_cpu"
#define _2_path_mem "/home/quan/linux/TCP项目/2/save_mem"
#define _2_path_disk "/home/quan/linux/TCP项目/2/save_disk"
#define _2_path_sys "/home/quan/linux/TCP项目/2/save_sys"
#define _2_path_user "/home/quan/linux/TCP项目/2/save_user"

#define _3_path_cpu "/home/quan/linux/TCP项目/3/save_cpu"
#define _3_path_mem "/home/quan/linux/TCP项目/3/save_mem"
#define _3_path_disk "/home/quan/linux/TCP项目/3/save_disk"
#define _3_path_sys "/home/quan/linux/TCP项目/3/save_sys"
#define _3_path_user "/home/quan/linux/TCP项目/3/save_user"

#define _4_path_cpu "/home/quan/linux/TCP项目/4/save_cpu"
#define _4_path_mem "/home/quan/linux/TCP项目/4/save_mem"
#define _4_path_disk "/home/quan/linux/TCP项目/4/save_disk"
#define _4_path_sys "/home/quan/linux/TCP项目/4/save_sys"
#define _4_path_user "/home/quan/linux/TCP项目/4/save_user"

#define _5_path_cpu "/home/quan/linux/TCP项目/5/save_cpu"
#define _5_path_mem "/home/quan/linux/TCP项目/5/save_mem"
#define _5_path_disk "/home/quan/linux/TCP项目/5/save_disk"
#define _5_path_sys "/home/quan/linux/TCP项目/5/save_sys"
#define _5_path_user "/home/quan/linux/TCP项目/5/save_user"

#define _6_path_cpu "/home/quan/linux/TCP项目/6/save_cpu"
#define _6_path_mem "/home/quan/linux/TCP项目/6/save_mem"
#define _6_path_disk "/home/quan/linux/TCP项目/6/save_disk"
#define _6_path_sys "/home/quan/linux/TCP项目/6/save_sys"
#define _6_path_user "/home/quan/linux/TCP项目/6/save_user"

#define _7_path_cpu "/home/quan/linux/TCP项目/7/save_cpu"
#define _7_path_mem "/home/quan/linux/TCP项目/7/save_mem"
#define _7_path_disk "/home/quan/linux/TCP项目/7/save_disk"
#define _7_path_sys "/home/quan/linux/TCP项目/7/save_sys"
#define _7_path_user "/home/quan/linux/TCP项目/7/save_user"

#define _8_path_cpu "/home/quan/linux/TCP项目/8/save_cpu"
#define _8_path_mem "/home/quan/linux/TCP项目/8/save_mem"
#define _8_path_disk "/home/quan/linux/TCP项目/8/save_disk"
#define _8_path_sys "/home/quan/linux/TCP项目/8/save_sys"
#define _8_path_user "/home/quan/linux/TCP项目/8/save_user"

#define _9_path_cpu "/home/quan/linux/TCP项目/9/save_cpu"
#define _9_path_mem "/home/quan/linux/TCP项目/9/save_mem"
#define _9_path_disk "/home/quan/linux/TCP项目/9/save_disk"
#define _9_path_sys "/home/quan/linux/TCP项目/9/save_sys"
#define _9_path_user "/home/quan/linux/TCP项目/9/save_user"

#define _10_path_cpu "/home/quan/linux/TCP项目/10/save_cpu"
#define _10_path_mem "/home/quan/linux/TCP项目/10/save_mem"
#define _10_path_disk "/home/quan/linux/TCP项目/10/save_disk"
#define _10_path_sys "/home/quan/linux/TCP项目/10/save_sys"
#define _10_path_user "/home/quan/linux/TCP项目/10/save_user"

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

void receive_message(char *client_IP, char *path_cpu, char *path_mem, char *path_disk, char *path_sys, char *path_user) {
    // 1 socket()
    int sockfd;
    sockfd = create_socket();
    // 2 connect()
    begin_connect(sockfd, link_con_port, client_IP);
    // 3 send() 
    char *buffer = (char *) calloc (2000, sizeof(char));

    // receive cpu
    send(sockfd, send_cpu, strlen(send_cpu), 0);
    memset(buffer, 0, 2000);
    recv(sockfd, buffer, 2000, 0);
    if (stringtoint(buffer) == yes) {
        sleep(0.5);
        memset(buffer, 0, 2000);
        int my_cpu_socketfd = create_socket();
        begin_connect(my_cpu_socketfd, link_cpu_port, client_IP);
        FILE *save_cpu = fopen(path_cpu, "a+");
        while (recv(my_cpu_socketfd, buffer, 2000, 0)) {
            fprintf(save_cpu, "%s", buffer);
            memset(buffer, 0., 2000);
        }
        fclose(save_cpu);
        close(my_cpu_socketfd);
        master_log(client_IP, link_con_port, "cpu", my_cpu_socketfd);
        p("%s cpu close done\n", client_IP);
    }

    // receive mem
    send(sockfd, send_mem, strlen(send_mem), 0);
    memset(buffer, 0, 2000);
    recv(sockfd, buffer, 2000, 0);
    if(stringtoint(buffer) == yes) {
        sleep(0.5);
        memset(buffer, 0, 2000);
        int my_mem_socketfd = create_socket();
        begin_connect(my_mem_socketfd, link_mem_port, client_IP);
        FILE *save_mem = fopen(path_mem, "a+");
        while(recv(my_mem_socketfd, buffer, 2000, 0)) {
            fprintf(save_mem, "%s", buffer);
            memset(buffer, 0, 2000);
        }
        fclose(save_mem);
        close(my_mem_socketfd);
        master_log(client_IP, link_con_port, "memory", my_mem_socketfd);
        p("%s mem close done\n", client_IP);
    }

    // send_disk
    send(sockfd, send_disk, strlen(send_disk), 0);
    memset(buffer, 0, 2000);
    recv(sockfd, buffer, 2000, 0);
    if(stringtoint(buffer) == yes) {
        sleep(0.5);
        memset(buffer, 0, 2000);
        int my_disk_socketfd = create_socket();
        begin_connect(my_disk_socketfd, link_disk_port, client_IP);
        FILE *save_disk = fopen(path_disk, "a+");
        while(recv(my_disk_socketfd, buffer, 2000, 0)) {
            fprintf(save_disk, "%s", buffer);
            memset(buffer, 0, 2000);
        }
        fclose(save_disk);
        close(my_disk_socketfd);
        master_log(client_IP, link_con_port, "disk", my_disk_socketfd);
        p("%s disk close done\n", client_IP);
    }
    // send_sys
    send(sockfd, send_sys, strlen(send_sys), 0);
    memset(buffer, 0, 2000);
    recv(sockfd, buffer, 2000, 0);
    if(stringtoint(buffer) == yes) {
        sleep(0.5);
        memset(buffer, 0, 2000);
        int my_sys_socketfd = create_socket();
        begin_connect(my_sys_socketfd, link_sys_port, client_IP);
        FILE *save_sys = fopen(path_sys, "a+");
        while(recv(my_sys_socketfd, buffer, 2000, 0)) {
            fprintf(save_sys, "%s", buffer);
            memset(buffer, 0, 2000);
        }
        fclose(save_sys);
        close(my_sys_socketfd);
        master_log(client_IP, link_con_port, "system", my_sys_socketfd);
        p("%s sys close done\n", client_IP);
    }
    // send_user
    send(sockfd, send_user, strlen(send_user), 0);
    memset(buffer, 0, 2000);
    recv(sockfd, buffer, 2000, 0);
    if(stringtoint(buffer) == yes) {
        sleep(0.5);
        memset(buffer, 0, 2000);
        int my_user_socketfd = create_socket();
        begin_connect(my_user_socketfd, link_user_port, client_IP);
        FILE *save_user = fopen(path_user, "a+");
        while(recv(my_user_socketfd, buffer, 2000, 0)) {
            fprintf(save_user, "%s", buffer);
            memset(buffer, 0, 2000);
        }
        fclose(save_user);
        close(my_user_socketfd);
        master_log(client_IP, link_con_port, "user", my_user_socketfd);
        p("%s user close done\n", client_IP);
    }
    close(sockfd);
}
#endif

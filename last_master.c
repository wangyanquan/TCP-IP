/*************************************************************************
	> File Name: last_master.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月09日 星期五 18时56分13秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"

int main() {
    // 1 socket()
    int sockfd;
    sockfd = create_socket();
    // 2 connect()
    int port = 6666;
    char host[] = "192.168.0.114";
    begin_connect(sockfd, port, host);
    // 3 send();
    char *buffer = (char *)calloc(1000, sizeof(char));
    while(1) {
        scanf("%s", buffer);
        if (stringtoint(buffer) == 11) {
            send(sockfd, buffer, strlen(buffer), 0);
            memset(buffer, 0, 1000);
            recv(sockfd, buffer, 1000, 0);
            p("receive = %s\n", buffer);
            if(stringtoint(buffer) == yes) {
                sleep(0.3);
                memset(buffer, 0, 1000);
                int my_cpu_socketfd = create_socket();
                begin_connect(my_cpu_socketfd, link_cpu_port, host);
                FILE *save_cpu = fopen("/home/quan/linux/TCP项目/save_cpu", "w");
                while(recv(my_cpu_socketfd, buffer, 1000, 0)) {
                    fprintf(save_cpu, "%s", buffer);
                    memset(buffer, 0, 1000);
                }
                fclose(save_cpu);
                close(my_cpu_socketfd);
                p("close done\n");
            }
        }
        else if (stringtoint(buffer) == 12) {
            send(sockfd, buffer, strlen(buffer), 0);
            memset(buffer, 0, 1000);
            recv(sockfd, buffer, 1000, 0);
            p("receive = %s\n", buffer);
            if(stringtoint(buffer) == yes) {
                sleep(0.3);
                memset(buffer, 0, 1000);
                int my_mem_socketfd = create_socket();
                begin_connect(my_mem_socketfd, link_mem_port, host);
                FILE *save_mem = fopen("/home/quan/linux/TCP项目/save_memory", "w");
                while(recv(my_mem_socketfd, buffer, 1000, 0)) {
                    fprintf(save_mem, "%s", buffer);
                    memset(buffer, 0, 1000);
                }
                fclose(save_mem);
                close(my_mem_socketfd);
                p("close done\n");
            }
        }
        else if (stringtoint(buffer) == 13) {
            send(sockfd, buffer, strlen(buffer), 0);
            memset(buffer, 0, 1000);
            recv(sockfd, buffer, 1000, 0);
            p("receive = %s\n", buffer);
            if(stringtoint(buffer) == yes) {
                sleep(0.3);
                memset(buffer, 0, 1000);
                int my_disk_socketfd = create_socket();
                begin_connect(my_disk_socketfd, link_disk_port, host);
                FILE *save_disk = fopen("/home/quan/linux/TCP项目/save_disk", "w");
                while(recv(my_disk_socketfd, buffer, 1000, 0)) {
                    fprintf(save_disk, "%s", buffer);
                    memset(buffer, 0, 1000);
                }
                fclose(save_disk);
                close(my_disk_socketfd);
                p("close done\n");
            }
        }
        else if (stringtoint(buffer) == 0) {
            send(sockfd, buffer, strlen(buffer), 0);
            memset(buffer, 0, 1000);
            close(sockfd);
            break;
        }
    }
    return 0;
}

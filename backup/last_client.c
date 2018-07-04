/*************************************************************************
	> File Name: last_client.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月09日 星期五 19时03分00秒
 ************************************************************************/

#include<stdio.h>
#include "my.h"

int main(int argc, char **argv) {
    int PID, count = 0;
    for (int i = 0; i < 3; i++) {
        count++;
        PID = fork();
        if (PID == 0) break;
    }
    if (PID != 0) return 0;
    if (count == 1) {
        // 1 socket()
        int my_sockfd = create_socket();
        // 2 set_socket()
        set_socket(my_sockfd);
        // 3 bind()
        begin_bind(my_sockfd, share_con_port);
        // 4 listen()
        begin_listen(my_sockfd);
        // 5 accept()
        int rec_sockfd;
        struct sockaddr_in master_message;
        socklen_t len = sizeof(struct sockaddr_in);
        while(1) {
            rec_sockfd = begin_accept(my_sockfd, &master_message, &len);
            getpeername(rec_sockfd, (struct sockaddr *)&master_message, &len);
            char rec_addr[50] = {'\0'};
            int rec_port;
            inet_ntop(AF_INET, (void *)&master_message.sin_addr, rec_addr, 49);
            rec_port = ntohs(master_message.sin_port);
            p ("rec_port = %d\n", rec_port);
            p ("rec_addr = %s\n", rec_addr);
            // 接受字符串
            int rec_count;
            char *rec_buf = (char *) calloc (1000, sizeof(char));
            while(recv(rec_sockfd, rec_buf, 1000, 0)) {
                if(stringtoint(rec_buf) == 11) {
                    p("need cpu message\n");
                    send(rec_sockfd, "1", 1, 0);
                    p("send : 1\n");
                    int my_cpu_socketfd = create_socket();
                    set_socket(my_cpu_socketfd);
                    begin_bind(my_cpu_socketfd, share_cpu_port);
                    begin_listen(my_cpu_socketfd);
                    int rec_cpu_socketfd = begin_accept(my_cpu_socketfd, &master_message, &len);
                    memset(rec_buf, 0, 1000);
                    FILE *cpu_f = fopen("/home/quan/linux/TCP项目/cpu", "r");
                    flock(cpu_f -> _fileno, LOCK_EX);
                    sleep(0.3);
                    while(fgets(rec_buf, 1000, cpu_f)) {
                        send(rec_cpu_socketfd, rec_buf, strlen(rec_buf), 0);
                        memset(rec_buf, 0, 1000);
                    }
                    p("send done\n");
                    flock(cpu_f -> _fileno, LOCK_UN);
                    fclose(cpu_f);
                    FILE *del_cpu_f = fopen("/home/quan/linux/TCP项目/cpu", "w");
                    fclose(del_cpu_f);
                    close(rec_cpu_socketfd);
                    close(my_cpu_socketfd);
                    p("close done\n");
                }
                else if(stringtoint(rec_buf) == 12) {
                    p("need mem message\n");
                    send(rec_sockfd, "1", 1, 0);
                    p("send : 1\n");
                    int my_mem_socketfd = create_socket();
                    set_socket(my_mem_socketfd);
                    begin_bind(my_mem_socketfd, share_mem_port);
                    begin_listen(my_mem_socketfd);
                    int rec_mem_socketfd = begin_accept(my_mem_socketfd, &master_message, &len);
                    memset(rec_buf, 0, 1000);
                    FILE *mem_f = fopen("/home/quan/linux/TCP项目/memory", "r");
                    flock(mem_f -> _fileno, LOCK_EX);
                    sleep(0.3);
                    while(fgets(rec_buf, 1000, mem_f)) {
                        send(rec_mem_socketfd, rec_buf, strlen(rec_buf), 0);
                        memset(rec_buf, 0, 1000);
                    }
                    p("send done\n");
                    flock(mem_f -> _fileno, LOCK_UN);
                    fclose(mem_f);
                    FILE *del_mem_f = fopen("/home/quan/linux/TCP项目/memory", "w");
                    fclose(del_mem_f);
                    close(rec_mem_socketfd);
                    close(my_mem_socketfd);
                    p("close done\n");
                }
                else if(stringtoint(rec_buf) == 13) {
                    p("need disk message\n");
                    send(rec_sockfd, "1", 1, 0);
                    p("send : 1\n");
                    int my_disk_socketfd = create_socket();
                    set_socket(my_disk_socketfd);
                    begin_bind(my_disk_socketfd, share_disk_port);
                    begin_listen(my_disk_socketfd);
                    int rec_disk_socketfd = begin_accept(my_disk_socketfd, &master_message, &len);
                    memset(rec_buf, 0, 1000);
                    FILE *disk_f = fopen("/home/quan/linux/TCP项目/disk", "r");
                    flock(disk_f -> _fileno, LOCK_EX);
                    sleep(0.3);
                    while(fgets(rec_buf, 1000, disk_f)) {
                        send(rec_disk_socketfd, rec_buf, strlen(rec_buf), 0);
                        memset(rec_buf, 0, 1000);
                    }
                    p("send done\n");
                    flock(disk_f -> _fileno, LOCK_UN);
                    fclose(disk_f);
                    FILE *del_disk_f = fopen("/home/quan/linux/TCP项目/disk", "w");
                    fclose(del_disk_f);
                    close(rec_disk_socketfd);
                    close(my_disk_socketfd);
                    p("close done\n");
                }
                else if(stringtoint(rec_buf) == 0) {
                    p("need out\n");
                    close(my_sockfd);
                    close(rec_sockfd);
                    p("out done\n");
                    exit(0);
                }
            }
        }
    }
    else if (count == 2) {
        while(1) {
            int count = 0;
            char *buf_cpu = (char *) calloc (1000, sizeof(char));
            char *buf_mem = (char *) calloc (1000, sizeof(char));
            char *buf_disk = (char *) calloc (1000, sizeof(char));
            char *temp = (char *) calloc (50, sizeof(char));
            for (int i = 0; i < 12; i++) {
                sleep(5);
                FILE *f_cpu = popen("bash get_cpu.sh", "r");
                while(fgets(temp, sizeof(temp), f_cpu)) {
                    strcat(buf_cpu, temp);
                    memset(temp, 0, 50);
                }
                pclose(f_cpu);
             //   printf("buf_cpu = %s\n", buf_cpu);
                FILE *f_mem = popen("bash get_memory.sh", "r");
                while(fgets(temp, sizeof(temp), f_mem)) {
                    strcat(buf_mem, temp);
                    memset(temp, 0, 50);
                }
                pclose(f_mem);
               // printf("buf_mem = %s\n", buf_mem);
                FILE *f_disk = popen("bash get_disk.sh", "r");
                while(fgets(temp, sizeof(temp), f_disk)) {
                    strcat(buf_disk, temp);
                    memset(temp, 0, 50);
                }
                pclose(f_disk);
              //  printf("buf_disk = %s\n", buf_disk);
            }
          //  printf("buf_cpu = %s\n", buf_cpu);
          //  printf("buf_mem = %s\n", buf_mem);
          //  printf("buf_disk = %s\n", buf_disk);
            char *path_cpu = "/home/quan/linux/TCP项目/cpu";
            char *path_mem = "/home/quan/linux/TCP项目/memory";
            char *path_disk = "/home/quan/linux/TCP项目/disk";
            FILE *f_cpu = fopen(path_cpu, "a+");
            FILE *f_mem = fopen(path_mem, "a+");
            FILE *f_disk = fopen(path_disk, "a+");
            fprintf(f_cpu, "%s", buf_cpu);
            fprintf(f_mem, "%s", buf_mem);
            fprintf(f_disk, "%s", buf_disk);
            fclose(f_cpu);
            fclose(f_mem);
            fclose(f_disk);
            memset(buf_cpu, 0, sizeof(buf_cpu));
            memset(buf_mem, 0, sizeof(buf_mem));
            memset(buf_disk, 0, sizeof(buf_disk));
        }
    }
    else {
        while (1) {
            // send cpu
            FILE *f_cpu = popen("bash get_cpu.sh", "r");
            char *buf_cpu = (char *) calloc (200, sizeof (char));
            char *per_cpu = (char *) calloc (10, sizeof(char));
            fscanf(f_cpu, "%[^\n]s", buf_cpu);
              // p("fgets = %s\n", buf_cpu);
            pclose(f_cpu);
            sscanf(buf_cpu, "%s%s%s%s%s", per_cpu, per_cpu, per_cpu, per_cpu, per_cpu);
             //  p("per_cpu = %s\n", per_cpu);
            float per_cpu_float;
            sscanf(per_cpu, "%f", &per_cpu_float);
               // p("per_cpu_float = %f\n", per_cpu_float);
            if (per_cpu_float > 80) {
                // 1 socket()
                int my_cpu_socketfd = create_socket();
                // 2 connect()
                begin_connect(my_cpu_socketfd, link_waring_port, IP);
                // 3 send()
                send(my_cpu_socketfd, buf_cpu, strlen(buf_cpu), 0);
                memset(buf_cpu, 0, sizeof(buf_cpu));
                close(my_cpu_socketfd);
            }
            free(buf_cpu);
            free(per_cpu);
            
            // send mem
            FILE *f_mem = popen("bash get_memory.sh", "r");
            char *buf_mem = (char *) calloc (200, sizeof (char));
            char *per_mem = (char *) calloc (10, sizeof(char));
            fscanf(f_mem, "%[^\n]s", buf_mem);
            //   p("fgets = %s\n", buf_mem);
            pclose(f_mem);
            sscanf(buf_mem, "%s%s%s%s%s", per_mem, per_mem, per_mem, per_mem, per_mem);
            //   p("per_mem = %s\n", per_mem);
            float per_mem_float;
            sscanf(per_mem, "%f", &per_mem_float);
            //    p("per_mem_float = %f\n", per_mem_float);
            if (per_mem_float > 80) {
                // 1 socket()
                int my_mem_socketfd = create_socket();
                // 2 connect()
                begin_connect(my_mem_socketfd, link_waring_port, IP);
                // 3 send()
                send(my_mem_socketfd, buf_mem, strlen(buf_mem), 0);
                memset(buf_mem, 0, sizeof(buf_mem));
                close(my_mem_socketfd);
            }
            free(buf_mem);
            free(per_mem);
            
            // send disk
            FILE *f_disk = popen("bash get_disk.sh|tail -1", "r");
            char *buf_disk = (char *) calloc (200, sizeof (char));
            char *per_disk = (char *) calloc (10, sizeof(char));
            fscanf(f_disk, "%[^\n]s", buf_disk);
            //   p("fgets = %s\n", buf_disk);
            pclose(f_disk);
            sscanf(buf_disk, "%s%s%s%s%s%s", per_disk, per_disk, per_disk, per_disk, per_disk, per_disk);
            //   p("per_disk = %s\n", per_disk);
            float per_disk_float;
            sscanf(per_disk, "%f", &per_disk_float);
            //    p("per_disk_float = %f\n", per_disk_float);
            if (per_disk_float > 80) {
                // 1 socket()
                int my_disk_socketfd = create_socket();
                // 2 connect()
                begin_connect(my_disk_socketfd, link_waring_port, IP);
                // 3 send()
                send(my_disk_socketfd, buf_disk, strlen(buf_disk), 0);
                memset(buf_disk, 0, sizeof(buf_disk));
                close(my_disk_socketfd);
            }
            free(buf_disk);
            free(per_disk);
        }
    }
    return 0;
}

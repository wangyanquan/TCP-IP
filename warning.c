/*************************************************************************
	> File Name: waring.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 21时15分06秒
 ************************************************************************/

#include <stdio.h>
#include "new_my.h"
int main() {
    int PID, count=0;
    for (int i = 0; i < 1; i++) {
        count++;
        PID = fork();
        if (PID == 0) break;
    }
    if (PID != 0) return 0;
    if (count == 1) {    
        while (1) {
            // 1 socket() 
            int my_sockfd = create_socket();
            // 2 set_socket()
            set_socket(my_sockfd);
            // 3 bind()
            begin_bind(my_sockfd, share_warning_port);
            // 4 listen()
            begin_listen(my_sockfd);
            // 5 accept
            int rec_sockfd;
            struct sockaddr_in client_message;
            socklen_t len = sizeof(struct sockaddr_in);
            while (1) {
                rec_sockfd = begin_accept(my_sockfd, &client_message, &len);
                getpeername(rec_sockfd, (struct sockaddr *)&client_message, &len);
                char rec_addr[50] = {'\0'};
                int rec_port;
                inet_ntop(AF_INET, (void *)&client_message.sin_addr, rec_addr, 49);
                rec_port = ntohs(client_message.sin_port);
                p ("waring rec_port = %d\n", rec_port);
                p ("waring rec_addr = %s\n", rec_addr);
                //接收字符串
                char *rec_buf = (char *) calloc (2000, sizeof (char));
                FILE *f_warning = fopen("/home/quan/linux/TCP项目/warning/warning.log", "a+");
                while (recv(rec_sockfd, rec_buf, 2000, 0)) {
                    fprintf(f_warning, "%s", rec_buf);
                }
                fclose(f_warning);
                free(rec_buf);
            }
        }
    }
}

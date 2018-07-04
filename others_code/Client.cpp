
#include <stdio.h>
#include "my.h"
     
int socket_connect(int port, char* host) {
    int sockfd;
    struct sockaddr_in dest_addr;
    if (((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)) {
            perror("socket error");
            return -1;
    }
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr =inet_addr(host);
      
    if (connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
          perror("connect perror:");
          printf("connect error sockfd = %d!!\n", sockfd);
          fflush(stdout);
          return -1;
      }
      return sockfd;
  }
    
    
    
int main (){
    
    char host[20] = "192.168.1.82";
    int ret = socket_connect(6666, host);
    printf("ret : %d\n", ret);
    char buf[1024];
    while (scanf("%s", buf) != EOF) {
        send(ret, buf, strlen(buf), 0);
    }
      return 0;
  } 

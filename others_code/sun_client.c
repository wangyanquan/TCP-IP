#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "netdb.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "string.h"
#include "memory.h"
#include "signal.h"
#include "time.h"

#define MAXLINE 4096

int main(int argc, char** argv)
{
   int sockfd ;
   //1.socket 
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd < 0){
    printf("socket error!\n");
   }else {
    printf("socket OK!\n");
   }
   
   //2.blind
   struct sockaddr_in addr_in;
   memset(&addr_in,0,sizeof(addr_in));
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(1234);
   addr_in.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(sockfd,(struct sockaddr *)&addr_in,sizeof(addr_in)) < 0) {
      printf("blind error\n");
   }else {
      printf("blind OK\n");
   }

   //3.listen
   if (listen(sockfd,20) < 20){
    printf("listen OK\n");
   }else {
    printf("listen ERROR\n");
   }

   //4.accept
   while (1){
      struct sockaddr_in client_add;
      socklen_t l = sizeof(addr_in);
      int listen_soc = accept(sockfd,(struct sockaddr*) &client_add, &l);
       if (listen_soc < 0){
          printf("accept ERROR\n");
       }else {
          printf("accept OK\n");
       }

       char buff[50];
       recv(listen_soc,buff,20000,0);
       printf("flag : %s \n",buff);
       char str1[20] = "1";
       char str2[20] = "2";

       if (strcmp(buff,str1) == 0){
          int len =  recv(listen_soc,buff,20000,0);
          printf("STRING receive %d bits : %s \n",len,buff);
       }else if(strcmp(buff,str2) == 0) {
          recv(listen_soc,buff,20000,0);
          printf("severname : %s \n",buff);
          FILE *fp = fopen(buff, "w"); 
          if (fp == NULL){
            printf("FILE Cant OPEN \n");
          }
          int len;
          while (len = recv(listen_soc,buff,20000,0)){
             fprintf(fp,"%s",buff);
             printf("we receive %d bits : %s \n",len,buff);
           }
           printf("FILE TRANS OVER \n");
           fclose(fp);
       }else {
          recv(listen_soc,buff,20000,0);
          printf("SERVEr BASH : %s \n",buff);
          FILE *fp = fopen(buff, "w");
       }
       close(listen_soc);
   }
   close(sockfd);
  return 0;
}」


「孙喜洋🤓: #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "netdb.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "string.h"
#include "memory.h"
#include "signal.h"
#include "time.h"

#define MAXLINE 4096

int main(int argc, char** argv)
{
   int sockfd ;
   //1.socket 
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd < 0){
    printf("socket error!\n");
   }else {
    printf("socket OK!\n");
   }
   
   //2.blind
   struct sockaddr_in addr_in;
   memset(&addr_in,0,sizeof(addr_in));
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(1234);
   addr_in.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(sockfd,(struct sockaddr *)&addr_in,sizeof(addr_in)) < 0) {
      printf("blind error\n");
   }else {
      printf("blind OK\n");
   }

   //3.listen
   if (listen(sockfd,20) < 20){
    printf("listen OK\n");
   }else {
    printf("listen ERROR\n");
   }

   //4.accept
   while (1){
      struct sockaddr_in client_add;
      socklen_t l = sizeof(addr_in);
      int listen_soc = accept(sockfd,(struct sockaddr*) &client_add, &l);
       if (listen_soc < 0){
          printf("accept ERROR\n");
       }else {
          printf("accept OK\n");
       }

       char buff[50];
       recv(listen_soc,buff,20000,0);
       printf("flag : %s \n",buff);
       char str1[20] = "1";
       char str2[20] = "2";

       if (strcmp(buff,str1) == 0){
          int len =  recv(listen_soc,buff,20000,0);
          printf("STRING receive %d bits : %s \n",len,buff);
       }else if(strcmp(buff,str2) == 0) {
          recv(listen_soc,buff,20000,0);
          printf("severname : %s \n",buff);
          FILE *fp = fopen(buff, "w"); 
          if (fp == NULL){
            printf("FILE Cant OPEN \n");
          }
          int len;
          while (len = recv(listen_soc,buff,20000,0)){
             fprintf(fp,"%s",buff);
             printf("we receive %d bits : %s \n",len,buff);
           }
           printf("FILE TRANS OVER \n");
           fclose(fp);
       }else {
          recv(listen_soc,buff,20000,0);
          printf("SERVEr BASH : %s \n",buff);
          FILE *fp = fopen(buff, "w");
       }
       close(listen_soc);
   }
   close(sockfd);
  return 0;
}

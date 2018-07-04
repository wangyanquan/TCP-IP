/*************************************************************************
	> File Name: sun.server.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月06日 星期二 20时43分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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


#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h> 


int main(int argc, char** argv)
{
   int sockfd ;
   int port;
   char ip[55] = "192.168.1.141";
   //1.socket 
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd < 0){
    printf("socket error!\n");
   }else {
    printf("socket OK!\n");
   }

   //2.connect
   struct sockaddr_in addr_in;
   memset(&addr_in,0,sizeof(addr_in));
   addr_in.sin_family = AF_INET;
   addr_in.sin_port = htons(1234);

   /*if(inet_pton(AF_INET, ip, &addr_in.sin_addr) <= 0){
     printf("inet_pton error for %s\n",argv[1]);
     exit(0);
  }*/
   addr_in.sin_addr.s_addr = inet_addr(ip);
   
   if (connect(sockfd,(struct sockaddr *)&addr_in,sizeof(addr_in)) < 0){
      printf("connect error\n");
   }else {
      printf("connect OK!\n");
   }
   char mes[50];
   printf("1 : trans string  2 : trans file \n");
   char flag[50];
   char str1[50] = "1";
   char str2[50] = "2";
   scanf("%s",flag);
   printf("flag : %s\n", flag);
   send(sockfd,flag,sizeof(flag),0);
       if (strcmp(flag,str1) == 0){
           char str[105];
           printf("Please input yourstring : ");
           scanf("%s",str);
           send(sockfd,str,strlen(str),0);
           printf("send  : %s\n",str);
       }
       else if (strcmp(flag,str2) == 0){
           printf("Please input yourfilename in Sever : " );
           char severname[50];
           fflush(stdout);
           scanf("%s",severname);
           fflush(stdout);
           send(sockfd,severname,strlen(severname),0);
           char filename[50];
           printf("Please input yourfilename : ");
           scanf("%s",filename);
             FILE *fp = fopen(filename, "r"); 
             while (~fscanf(fp,"%s",mes)){
                send(sockfd,mes,strlen(mes),0);
                printf("send  : %s\n",mes);
            }
       }else {
          printf("Please input yourBash Comand : " );
          char com[50];
          fflush(stdout);
          scanf("%s",com);
          /*fflush(stdout);
          send(sockfd,com,strlen(com),0);
          system(com);*/
           FILE *fp = NULL;  
           while(1) {  
                fp = NULL;  
                fp = popen("ls", "r");  
                if(!fp) {  
                        perror("popen");  
                        exit(EXIT_FAILURE);  
                } 
                send(sockfd,fp,strlen(fp),0); 
              //  print_result(fp);  
                pclose(fp);  
                sleep(1);  
        }  
       }
   return 0;
}




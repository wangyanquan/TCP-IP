/*************************************************************************
	> File Name: pipei.c
	> Author: wangyanquan
	> Mail: 
	> Created Time: 2018年03月16日 星期五 18时25分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int get_num(char *load, char *str, char *ret) {
    FILE *fin = fopen(load, "r");
    char *read = (char *) calloc (200, sizeof (char));
    int len = strlen(str);
    while (~fscanf(fin, "%s", read)) {
        int flag = 0;
        int i = 0;
        for (i = 0; i < len; i++) {
            if (str[i] != read[i]) {
                break;
            }
        }
        if (i == len) {
            if (read[i] == '=') {
                char *receice = (char *) calloc(20, sizeof(char));
                sscanf(read + i,  "%s", receice);
            }
        }
        else {
            continue;
        }
    }
}
int main() {
        
    return 0;
}

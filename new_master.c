/*************************************************************************
	> File Name: new_master.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 19时22分04秒
 ************************************************************************/

#include<stdio.h>
#include "new_my.h"

int main() {
    int count = 0;
    int PID;
    for (int i = 0; i < 10; i++) {
        count++;
        PID = fork();
        if (PID == 0) break;
    }
    if (PID != 0) return 0;
    if (count == 1) {
        receive_message(pi1_host, _1_path_cpu, _1_path_mem, _1_path_disk, _1_path_sys, _1_path_user);    
    }
    else if (count == 2) {
        
        receive_message(pi2_host, _2_path_cpu, _2_path_mem, _2_path_disk, _2_path_sys, _2_path_user);    
    }
    else if (count == 3) {
        
        receive_message(pi3_host, _3_path_cpu, _3_path_mem, _3_path_disk, _3_path_sys, _3_path_user);    
    }
    else if (count == 4) {
        
        receive_message(pi4_host, _4_path_cpu, _4_path_mem, _4_path_disk, _4_path_sys, _4_path_user);    
    }
    else if (count == 5) {
        
        receive_message(pi5_host, _5_path_cpu, _5_path_mem, _5_path_disk, _5_path_sys, _5_path_user);    
    }
    else if (count == 6) {
        
        receive_message(pi6_host, _6_path_cpu, _6_path_mem, _6_path_disk, _6_path_sys, _6_path_user);    
    }
    else if (count == 7) {
        
        receive_message(pi7_host, _7_path_cpu, _7_path_mem, _7_path_disk, _7_path_sys, _7_path_user);    
    }
    else if (count == 8) {
        
        receive_message(pi8_host, _7_path_cpu, _7_path_mem, _7_path_disk, _7_path_sys, _7_path_user);    
    }
    else if (count == 9) {
        
        receive_message(pi9_host, _9_path_cpu, _9_path_mem, _9_path_disk, _9_path_sys, _9_path_user);    
    }
    else if (count == 10) {
        
        receive_message(pi10_host, _10_path_cpu, _10_path_mem, _10_path_disk, _10_path_sys, _10_path_user);    
    }
    return 0;
}

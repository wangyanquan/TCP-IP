#!/bin/bash
NowTime=`date +'%Y-%m-%d_%H:%M:%S'`
#系统用户数量
eval $(cat /etc/passwd | sort -nk 3 -t : |cut -d ':' -f 3|\
    awk 'BEGIN {count=0} {if ($1 >= 1000 && $1 < 65534) count++} END {printf("count=%d", count)}')
#echo "$count"

#活跃用户名
user_active=(`last|grep -v reboot | cut -d " " -f 1 | uniq|head -n 3`)

#具有root权限的用户
#eval $(sudo cat /etc/sudoers |grep -v '[#%]'|grep ALL|awk '{printf("user_root["NR"]=%s ",$1)} END{printf("user_root_count=%d", NR)}')


#登录用户名 tty
eval $(w|tail -n +3|awk '{printf("login_user["NR"]=%s login_tty["NR"]=%s ", $1, $2)} END {printf("login_user_count=%d ", NR)}')

echo "$NowTime $count ${user_active[0]} ${user_active[1]} ${user_active[2]}"
#root权限用户
#echo "$user_root_count"
#for (( i=1; i<=$user_root_count; i++ ))
#do
#    echo "${user_root[i]}"
#done

#echo "login_user_count=$login_user_count"
for (( i=1; i<=$login_user_count; i++ ))
do
    echo "${login_user[i]} ${login_tty[i]}"
done

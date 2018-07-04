#!/bin/bash
NowTime=`date +'%Y-%m-%d_%H:%M:%S'`
HostName=`hostname`
OSName=`cat /etc/issue`
CoreName=`uname -r`
eval $(cat /proc/uptime| awk -F. '{run_days=$1 / 86400;run_hour=($1 % 86400)/3600;run_minute=($1 % 3600)/60;run_second=$1 % 60;printf("run_days=%d;run_hour=%d;run_minute=%d;run_second=%d;", run_days, run_hour, run_minute, run_second)}')
Load=`uptime | cut -d ' ' -f 10-14`


#磁盘
eval $(df -m | grep "dev" | tail -n +2 |\
      awk 'BEGIN{sumsum=0; sumused=0;} \
        {printf("pername["NR"]=%s   persum["NR"]=%d perleft["NR"]=%d  percent["NR"]=%s ",$1,$2,$4,$5);\
           sumsum=sumsum+$2;sumleft=sumleft+$4}\
              END {printf("amt=%d sumsum=%d sumleft=%d",NR,sumsum,sumleft)}')
sumper=$[ (100-sumleft*100 /sumsum)  ]


#内存
Mes=(`free -m |head -n 2|tail -n 1 |awk '{printf("%d %d %d ",$2,$3,$7)}'`)
MemSum=${Mes[0]}
MemUse=${Mes[1]}
MemFree=${Mes[2]}
MemUsePrec=`echo "scale=4;($MemUse/$MemSum)*100" | bc`


#Cpu
LoadAvg=`cut -d " " -f 1-3 /proc/loadavg`
CpuTemp=`cat /sys/class/thermal/thermal_zone0/temp`
CpuTemp=`echo "scale=2;$CpuTemp/1000" | bc`
eval $(head -n 1 /proc/stat | awk -v sum1=0 -v idle1=0 \
    '{for (i=2;i<=8;i++) {sum1=sum1+$i} printf("sum1=%d;idle1=%d;", sum1,$5)}'
    )
sleep 0.5
eval $(head -n 1 /proc/stat | awk -v sum2=0 -v idle2=0 \
    '{for (i=2;i<=8;i++) {sum2=sum2+$i} printf("sum2=%d;idle2=%d;", sum2, $5)}'
    )
CpuUsedPerc=`echo "scale=4;(1-($idle1-$idle2)/($sum1-$sum2))*100" | bc`
CpuUsedPerc=`printf "%.2lf\n" $CpuUsedPerc`



DiskWarnLevel="normal"
if [[ `echo $sumper '>' 90 | bc -l` = 1 ]]; then 
    DiskWarnLevel="warning"
elif [[ `echo $sumper '>' 80 | bc -l` = 1 ]]; then
    DiskWarnLevel="note"
fi
#echo $DiskWarnLevel

MemWarnLevel="normal"
if [[ `echo $MemUsePrec '>' 80 | bc -l` = 1 ]]; then 
    MemWarnLevel="warning"
elif [[ `echo $MemUsePrec '>' 70 | bc -l` = 1 ]]; then
    MemWarnLevel="note"
fi
#echo $MemWarnLevel

CpuWarnLevel="normal"
if [[ `echo $CpuUsedPerc '>' 80 | bc -l` = 1 ]]; then 
    CpuWarnLevel="warning"
elif [[ `echo $CpuUsedPerc '>' 70 | bc -l` = 1 ]]; then
    CpuWarnLevel="note"
fi
#echo $CpuWarnLevel

echo "$NowTime $HostName $OSName $CoreName $run_days $run_hour $run_minute $run_second $Load $sumsum ${sumper}%\
    $MemSum ${MemUsePrec}% $CpuTemp $DiskWarnLevel $MemWarnLevel $CpuWarnLevel"

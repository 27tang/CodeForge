#!/bin/bash



read -r numberOfCases 
#echo wallabingbang\n
#echo $numberOfCases
#echo dingdong\n

nums=$((2*$numberOfCases))
for i in `seq 1 $nums`
  do
    read -r numPlates 
    
    total=0

    read -r prev
    for j in `seq 2 $numPlate`
    do
      read -r line
      plates=($line)
      for plate in $plates;
      do
        res=$(($curr - $prev))
        if [ $(($res > 0)) ]; then
          #((total=$total+ $curr - $prev))
          echo $res
        fi
      done
    done

  done



#!/bin/bash

read -r numberOfCases 
nums=$(($numberOfCases))

for i in `seq 1 $nums`
  do
    read -r numPlates
    #echo NUM PLATES
    #echo $numPlates 
    #echo ----------------
    total=0

    read -r line
    plates=($line)
    for ((i=1; i < $((${#plates[@]} )); i++))
    do
      diff=$((${plates[$(($i - 1))]}-${plates[$i]}))
      if [ $diff -ge 0 ]; then
        total=$(($total + $diff))
      fi
      #total=$(($total + plates[$i]
      #$echo $total
    done
   echo $total
   total=0 

  done



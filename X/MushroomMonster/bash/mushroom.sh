#!/bin/bash

read -r numberOfCases 
nums=$(($numberOfCases))

for j in `seq 1 $nums`
  do
    read -r numPlates
    total1=0
    total2=0
    maxDiff=0
    

    read -r line
    plates=($line)
    for ((i=1; i < $((${#plates[@]} )); i++))
    do
      diff=$((  ${plates[$(($i - 1))]}  -  ${plates[$i]} ))
      if [ $diff -ge 0 ]
      then
        total1=$(($total1 + $diff))
      fi
      if [ $diff -ge $maxDiff ]
      then
        maxDiff=$diff
      fi
    done
    
    for ((i=0; i < $(( ${#plates[@]} - 1 )); i++))
    do
      if [ $maxDiff -le ${plates[$i]} ]
      then
        total2=$(( $total2 + $maxDiff ))
        
      else
        total2=$(( $total2 + ${plates[$i]} ))
      fi
    done

   echo Case \#$j\: $total1 $total2

  done



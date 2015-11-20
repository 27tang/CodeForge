#!/bin/bash

cat "$1"
if [ -z $1 ]; then
  >&2 echo "not enough parameters" 
  exit 0
fi

input=$(cat $1)

eatItUp()
{
  while [ ! -z $1 ];
  do
    numOfCases=
  done
}

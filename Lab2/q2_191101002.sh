#! /bin/bash
#Author: Mustafa Aydogan

if [ "$1" != "" ]
then
  echo "No argument should be provided, exiting program." 
  exit 0
fi

echo "First integer:"
  read first


while [ "$first" != "exit" ]
do
  echo "Second integer:"
  read second
  if [ $first -lt $second ]
  then
    echo "The first integer is less than the second integer."
  elif [ $first -gt $second ]
  then
    echo "The first integer is greater than the second integer."
  else
    echo "The first integer is equal to the second integer."
  fi

  echo "First integer:"
  read first
done

echo "Exiting program."

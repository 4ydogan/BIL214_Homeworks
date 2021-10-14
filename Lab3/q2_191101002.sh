#! /bin/bash

input=""
output=""
shift_amount=0

case $1 in

  "-i")
  input=$2
  ;;

  "-o")
  output=$2
  ;;

  "-s")
  shift_amount=$2
  ;;
esac

case $3 in

  "-i")
  input=$4
  ;;

  "-o")
  output=$4
  ;;

  "-s")
  shift_amount=$4
  ;;
esac

case $5 in

  "-i")
  input=$6
  ;;

  "-o")
  output=$6
  ;;

  "-s")
  shift_amount=$6
  ;;
esac

k="$(( shift_amount ))"

read line < $input

new=""
lower="abcdefghijklmnopqrstuvwxyz"
upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
newlower="${lower:$k}${lower:0:k}"
newupper="${upper:$k}${upper:0:k}"

echo $line | tr $lower $newlower | tr $upper $newupper > $output

#!/bin/bash
#Author: Mustafa Aydogan

#args tanimlar ve assign edilir
input=0
output=0
shift=0

# ------------------------------------------------------------------ #

case $1 in
  "-i")
  input=$2
  ;;

  "-o")
  output=$2
  ;;

  "-s")
  shift=$2
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
  shift=$4
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
  shift=$6
  ;;
esac

# ------------------------------------------------------------------ #

#input dosyalarini array'e aktarır
readarray -d " " -t input_files <<< "$input"

#ilk satir icin bir dosyadan okur
read header < ${input_files[0]}
echo $header > $output


#ilk satiri ',' ile ayir
readarray -d "," -t arr_header <<< "$header"
select=1

#siralama icin index belirlenir
for (( i=0; i < ${#arr_header[@]}; i++ ))
do
    if [ "${arr_header[$i]}" == "$shift" ]
    then
    	select=$i
    fi
done    

#tum dosyalari ve satirlari okur ve output dosyasina yazar    
for i in $input
do
    while read -r line
    do
         echo $line >> $output
    done < <(tail -n +2 "$i")
done

echo "" >> $output #gerekli bir islem

#dosyanin satir sayisini hesaplar
lines=$(< $output wc -l)

#satirlari kendi arasinda siralar
for (( n=2; n < lines-1; n++ )) ; do
   for (( k=2; k < $lines-1; k++ )) ; do
   	
   	#satirlari alir
   	line1=$(sed "${k}q;d" < $output)
   	l1=$(echo $line1 | sed 's/, /|/g')
   	sed -i "${k}d" $output
  	line2=$(sed "${k}q;d" < $output)
  	l2=$(echo $line2 | sed 's/, /|/g')
   	sed -i "${k}d" $output
   	  	
	readarray -d "," -t arr1 <<< $l1
	readarray -d "," -t arr2 <<< $l2
	
	#eger buyukse satirlarin yeri degisir
	if [ "${arr1[$select]}" -gt "${arr2[$select]}" ]
  	then
    	    sed -i "${k}i $line1" $output
    	    sed -i "${k}i $line2" $output
    	else
    	    sed -i "${k}i $line2" $output
    	    sed -i "${k}i $line1" $output
    	fi
   done
done < $output

sed -i "${lines}d" $output #sondaki olsan bos satiri siler

# -----------------------end of the file--------------------------- #

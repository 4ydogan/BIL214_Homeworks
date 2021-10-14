#!/bin/bash
#Author: Mustafa Aydogan

#args tanimlar ve assign eder
input=0
output=0
to=0
very=0

# ------------------------------------------------------------------ #

case $1 in
  "-i")
  input=$2
  ;;

  "-o")
  output=$2
  ;;

  "-t")
  to=$2
  ;;
  
  "-v")
  very=$2
  ;;
esac

case $3 in
  "-i")
  input=$4
  ;;

  "-o")
  output=$4
  ;;

  "-t")
  to=$4
  ;;
  
  "-v")
  very=$4
  ;;
esac

case $5 in
  "-i")
  input=$6
  ;;

  "-o")
  output=$6
  ;;

  "-t")
  to=$6
  ;;
  
  "-v")
  very=$6
  ;;
esac

case $7 in
  "-i")
  input=$8
  ;;

  "-o")
  output=$8
  ;;

  "-t")
  to=$8
  ;;
  
  "-v")
  very=$8
  ;;
esac

# ------------------------------------------------------------------ #

#input dosyalarini array'e aktarır
readarray -d " " -t input_files <<< "$input"

#ilk satir icin bir dosyadan okur
read header < ${input_files[0]}  

#ilk satiri ',' ile ayir
readarray -d "," -t arr_header <<< "$header"
select=1

#Authors indexini bulur
for (( i=0; i < ${#arr_header[@]}; i++ ))
do
    if [ "${arr_header[$i]}" == "Authors" ]
    then
    	select=$i
    fi
done  

#dosyayi temizler
rm $to
touch $to

#author için unique bir key tanımlar
unique="1"

#butun dosyalardan okur
for i in $input
do
    while read -r line
    do	
    	#dosyanin içindeki tüm satirlari okur
    	line1=$(echo $line | sed 's/, /|/g' | sed 's/"//g')
    	readarray -d "," -t arr1 <<< $line1
	readarray -d "|" -t authors <<< ${arr1[$select]}
	#authors'lari array' aktarir
	
	#authors daha onceden eklenmis mi diye kontrol eder
	#eger eklenmemis ise ekler ve unique artirir
	for (( n=0; n < ${#authors[@]}; n++ )) ; do
	    author=$(echo "${authors[$n]}" | tr -d '\n')
	    count=$(grep "$author" $to | wc -l)
	    if [ $count == 0 -a "$author" != "" ]
	    then
	       echo "\"$author\",$unique" >> $to
	       unique=$( expr $unique + 1)
	    fi
	done
    done < <(tail -n +2 "$i")
done 

# ------------------------------------------------------------------ #
#ikinci kisim

#bir dictionary tanimlar
declare -A dictionary

#tum satirlari okur ve dictionary'e aktarir
while read -r line
do	
    line=$(echo $line | sed 's/"//g')
    readarray -d "," -t arr1 <<< $line
    element1=$(echo "${arr1[0]}" | tr -d "\n")
    element2=$(echo "${arr1[1]}" | tr -d "\n")
    dictionary["$element2"]="$element1"
done < $to

#ilk satiri dosyaya yazar
read header < ${input_files[0]}
echo $header > $output

#dosyanin satir sayisini hesaplar
lines=$(< $to wc -l)

#input dosyalarini array'e aktarir
readarray -d " " -t input_files <<< "$input"

#tum dosyalari okur ve hedef dosyaya yazar
for i in $input
do
    while read -r line
    do
    	echo $line >> $output

    done < <(tail -n +2 "$i")
done

#auhors icindeki isimler ile unique key'leri degistirir
for ((i=1; i<=lines; i++)) ; do
    sed -i "s/${dictionary[$i]}/$i/g" "$output"
done

# ------------------------------------------------------------------ #

#dosyayi temizler
rm $very
touch $very

#satir sayisini hesaplar
lines=$(< $to wc -l)

line=""

#ilk satiri olusturur
for (( k=1; k<=lines; k++ )) ; do
    line="$line,$k"
done

#ilk satiri dosyaya yazar
echo $line >> $very

#loop ile satirlari olusturur
for (( n=1; n<=lines; n++ )) ; do
    line="$n"
    
    #birlikte bulunduklari satir sayisini hesaplar
    for (( k=1; k<=lines; k++ )) ; do
    	count=$(grep -o "\".*$n, .*$k.*\"" $output | wc -l)
	add=$(grep -o "\".*$k, .*$n.*\"" $output | wc -l)
	count=$(expr $count + $add)

	#matrisin diagonali hesaplanir
	if [ $k == $n ] 
	then
	    count=$(grep -o "\".*$n.*\"" $output | wc -l)
	fi
	
	#line duzenlenir
	line="$line,$count"
    done
    
    #line dosyaya yazilir
    echo $line >> $very   
done

# -----------------------end of the file--------------------------- #


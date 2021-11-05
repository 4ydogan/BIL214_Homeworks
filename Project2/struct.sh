#!/bin/bash
#Author: Mustafa Aydogan

grep "\"*\":" $1
count=0
message=""


while read -r line
do	
	for (( i=0; i<${#line}; i++ )); do
		if [[ "${line:$i:1}" == "{" ]]; then
			count=$((count+1))
			
		fi

		if [[ "${line:$i:1}" == "}" ]]; then
			echo "${line:$i:1}"
			count=$((count-1))
		fi

	#echo $count


	done
done < $1

echo $line

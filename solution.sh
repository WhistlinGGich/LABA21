#!/bin/bash

# Аргументы: 1-файл, 2-строки, 3-префикс
FILE=$1
LINES=$2
PREFIX=$3

count=0
file_num=1

while read line; do
    outfile="${PREFIX}${file_num}"
    echo "$line" >> "$outfile"
    
    count=$((count + 1))

    if [ $count -eq $LINES ]; then
        file_num=$((file_num + 1))
        count=0
    fi
done < "$FILE"

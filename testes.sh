#!/usr/bin/env sh

dir_input="./in/"
dir_output="./out/"
num_casos=$(find $dir_input -type f | wc -l)


for i in $(seq 1 "$num_casos"); do
    echo "Comparando caso $i"
    if diff <(./main < "$dir_input/$i.in") "$dir_output/$i.out"; then
        echo "OK"
    else
        echo "ERROR"
    fi
done

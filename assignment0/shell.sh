#!/bin/bash

for file in `ls ./test`
do
    echo $file
    rm -r $file
    mkdir $file
    i=1
    while [ $i -le 10 ]
    do
        for file in `ls ./test`
        do
            echo ./ifs -input test/$file -points 10000 -iters $i -size 100 -output $file/$i.tga;
            ./ifs -input test/$file -points 10000 -iters $i -size 100 -output $file/$i.tga
        done
        let i++
    done
done
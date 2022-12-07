#!/bin/bash

files=""
for FILE in $1/*.h 
do
    files+=" ${FILE}"
done
for FILE in $1/*.c 
do
    files+=" ${FILE}"
done

./lib/a.out $files

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

# SOURCES="a b c d e"
# DESTINATIONS=""

# for src in $SOURCES
# do
#     echo Input destination to associate to the source $src:
#     read dest
#     DESTINATIONS+=" ${dest}"
# done
# echo $DESTINATIONS
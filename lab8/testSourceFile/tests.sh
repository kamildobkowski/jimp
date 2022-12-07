#!/bin/bash
files=""
for FILE in $1/*.c do
    files+=("$FILE")
done
for FILE in $1/*.h do 
	files=$file $FILE
done
echo $files
#!/bin/bash
read -p "Podaj nazwe pliku z folderu: $1: " fileName
files=""
for FILE in $fileName
do
    files+=" $1/${FILE}"
done
echo Program uruchamia sie przy pomocy polecenia:
echo ./lib/a.out $files
read -p "Naciśnij enter..." nul
./lib/a.out $files
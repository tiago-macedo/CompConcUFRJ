#!/bin/bash
N=20
i=0

echo "" > result

while [ $i -le $N ]
do
	./4 >> result
	echo "========" >> result
	i=$(( i+1 ))
done

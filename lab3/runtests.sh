#!/bin/bash

echo "" > output

for threadnum in 2 4
do
	for dim in 1000 100000 10000000 1000000000
	do
		echo "=======================" >> output
		echo "threads:	$threadnum" >> output
		echo "dimension:	$dim" >> output
		echo "" >> output
		echo "Tentativa 1:" >> output 
		./pi $dim $threadnum >> output
		echo "" >> output
		echo "Tentativa 2:" >> output
		./pi $dim $threadnum >> output
		echo "" >> output
		echo "Tentativa 3:" >> output
		./pi $dim $threadnum >> output
		echo "" >> output
		echo "Tentativa 4:" >> output
		./pi $dim $threadnum >> output
		echo "" >> output
		echo "Tentativa 5:" >> output
		./pi $dim $threadnum >> output
		echo "" >> output
	echo "" >> output
	done
done

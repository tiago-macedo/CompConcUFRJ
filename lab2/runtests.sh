#!/bin/bash

echo "" > output

for threadnum in 1 2 4
do
	for dim in 500 1000 2000
	do
		echo -e "=======================" >> output
		echo -e "threads:	$threadnum" >> output
		echo -e "dimension:	$dim" >> output
		echo -e "" >> output
		echo -e "Tentativa 1:" >> output
		./matrix $dim $threadnum >> output
		echo -e "Tentativa 2:" >> output
		./matrix $dim $threadnum >> output
		echo -e "Tentativa 3:" >> output
		./matrix $dim $threadnum >> output
		echo -e "Tentativa 4:" >> output
		./matrix $dim $threadnum >> output
		echo -e "Tentativa 5:" >> output
		./matrix $dim $threadnum >> output
	echo -e "" >> output
	done
done

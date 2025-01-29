#!/bin/bash

#  Check if an  argument is  passed
if [[ -z $1 ]]; then
	echo "Invalid; should be written in this format--  ./testDescribe.sh testsetfile.txt"  >&2
	exit 1  # indicating an error occured

else
	while IFS= read -r stem; do # treats the backslah in any of the paths as it should be treated and removes  trailing spaces too
		if [[ ! -e "$stem" ]]; then # Checks if the stem does not exis in the test set file
			echo "${stem}: No test description"
		else
			cat "$stem"
		fi
	done < "$1"
fi





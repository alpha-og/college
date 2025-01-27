#!/bin/bash

# Problem Number: 7
# Description: Read an integer N, a string word and a filename via command line. If word occurs more than N times in the file, remove all its occurrences in the file.
#
# Athul Anoop
#

if [[ $"$#" -ne 3 ]]; then
	echo "Usage: $0 N word file"
	exit 1
fi

N=$1
word=$2
file=$3

if [[ -z "$N" || -z "$word" || -z "$file" ]]; then
	echo "Arguments cannot be empty"
	exit 1
fi

count=$(grep -c "$word" "$file")

if [[ "$count" -gt "$N" ]]; then
	sed -i "" "s/$word//g" "$file"
fi

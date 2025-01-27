#!/bin/bash
# Problem Number: 5
# Description Print all prime numbers in a range.
# ------------------------------------------------------------------------------
# Athul Anoop

if [ $# -ne 2 ]; then
	echo "Usage: $0 start end"
	exit 1
fi

start=$1
end=$2

is_prime() {
	local n=$1
	is_prime=true
	for i in $(seq 2 "$(echo "sqrt($n)" | bc -l)"); do
		if [ "$(echo "$n % $i" | bc)" -eq 0 ]; then
			is_prime=false
			break
		fi
	done
	echo $is_prime
}

for i in $(seq "$start" "$end"); do
	if [[ "$(is_prime "$i")" == true ]]; then
		echo "$i"
	fi
done

#!/bin/bash
# Problem Number: 8
# Description:
# You have a file s4csb1.txt with the following format: AdmnNo,Name,Address,PhoneNo,Email.
# Now create a command recedit which is to be invoked as:
# recedit op ID
#
# Here op is one among the operations add,search,update,delete and ID is an admission number.
# The command behaviour is summarized below:
# • raise an error if sufficient number of arguments are not supplied.
#
# • to add a new student with the given ID, get the other pertinent details and create a new row
# for the student in the file s4csb1.txt. If such a student already exists, raise an error.
# • if the operation is search, the pertinent details should be printed if such a student exists or
# raise an error otherwise.
# • if the operation is update, get the details and update the student record.
# • if the operation is delete, remove the student record.
#
# Athul Anoop

if [ $# -lt 2 ]; then
	echo "Usage: recedit op ID"
	exit 1
fi

op=$1
id=$2

search() {
	while read -r line; do
		if [[ "$(echo "$line" | cut -d',' -f1)" == "$1" ]]; then
			echo "$line"
		fi
	done <"s4csb2.txt"
}

case $op in
"add")
	if [[ $# -ne 6 ]]; then
		echo "Usage: recedit add ID Name Address PhoneNo Email"
		exit 1
	else
		existing=$(search "$id")
		if [[ -z "$existing" ]]; then
			echo "$id, $3, $4, $5, $6" >>"s4csb2.txt"
		else
			echo "Student already exists"
		fi
	fi
	;;
"search")
	if [[ $# -ne 2 ]]; then
		echo "Usage: recedit search ID"
		exit 1
	else
		existing=$(search "$id")
		if [[ -z "$existing" ]]; then
			echo "Student does not exist"
		else
			echo "$existing"
		fi
	fi
	;;
"update")
	if [[ $# -ne 6 ]]; then
		echo "Usage: recedit update ID Name Address PhoneNo Email"
		exit 1
	else
		existing=$(search "$id")
		if [[ -z "$existing" ]]; then
			echo "Student does not exist"
		else
			sed -i "" "s/$existing/$id, $3, $4, $5, $6/" s4csb2.txt
		fi
	fi
	;;
"delete")
	if [[ "$#" -ne 2 ]]; then
		echo "Usage: recedit delete ID"
		exit 1
	else
		existing=$(search "$id")
		if [[ -z "$existing" ]]; then
			echo "Student does not exist"
		else
			sed -i "" "/$existing/d" "s4csb2.txt"
		fi
	fi
	;;
*)
	echo "Invalid operation"
	exit 1
	;;
esac

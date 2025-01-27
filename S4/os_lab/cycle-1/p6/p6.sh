#!/bin/bash

# Problem Number: 6
# Description: Write a menu driven program to convert a positive decimal number to binary, octal or hexadecimal based on the user’s choice. Each of the conversions should be implemented using separate functions.
#
# Athul Anoop

display_menu() {
	echo "1. Decimal to Binary"
	echo "2. Decimal to Octal"
	echo "3. Decimal to Hexadecimal"
	echo "4. Display Menu"
	echo "5. Exit"
}

decimal_to_binary() {
	read -rp "Enter a decimal number: " number
	echo "$(echo "obase=2;$1" | bc)"
}

decimal_to_octal() {
	read -rp "Enter a decimal number: " number
	echo "$(echo "obase=8;$1" | bc)"
}

decimal_to_hexadecimal() {
	read -rp "Enter a decimal number: " number
	echo "$(echo "obase=16;$1" | bc)"
}
handle_choice() {
	case "$1" in
	1)
		decimal_to_binary "$2"
		;;
	2)
		decimal_to_octal "$2"
		;;
	3)
		decimal_to_hexadecimal "$2"
		;;
	4)
		display_menu
		;;
	5)
		exit 0
		;;
	*)
		echo "Invalid choice"
		;;
	esac
}

display_menu
while true; do
	read -rp "Enter your choice: " choice
	handle_choice "$choice" "$number"
done

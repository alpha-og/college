#!/bin/bash

display_menu() {
	echo "---- Scientific Calculator ----"
	echo "1. Sine"
	echo "2. Cosine"
	echo "3. Tangent"
	echo "4. Power"
	echo "5. Square root"
	echo "6. Exit"
	echo "7. Menu"
}

read_radians() {
	read -p "Angle in radians: " angle
	echo "$angle"
}

handle_choice() {
	case $1 in
	1)
		echo "Sine of $angle (radians) is $(echo "s($(read_radians))" | bc -l)"
		;;
	2)
		echo "Cosine of $angle (radians) is $(echo "c($(read_radians))" | bc -l)"
		;;
	3)
		angle=$(read_radians)
		echo "Tangent of $angle (radians) is $(echo "s($angle)/c($angle)" | bc -l)"
		;;
	4)
		read -rp "Base: " base
		read -rp "Exponent: " exponent
		echo "$base^$exponent is $(echo "$base^$exponent" | bc -l)"
		;;
	5)
		read -rp "Value: " value
		echo "Square root of $value is $(echo "sqrt($value)" | bc -l)"
		;;
	6)
		exit
		;;
	7)
		display_menu
		;;
	*)
		echo "Invalid choice"
		;;
	esac
}

display_menu
while true; do
	read -rp "Choice: " choice
	handle_choice "$choice"
done

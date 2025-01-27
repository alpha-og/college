#! /usr/bin/env bash

command_template="$(cat ./command.tex)"
page_template="$(cat ./page.tex)"
img_template="\includegraphics[width=\linewidth]{%img%}"

gen_cmds_path="./gen/cmds/"
if ! [[ -d "$gen_cmds_path" ]]; then
	mkdir -p "$gen_cmds_path"
fi

gen_doc_path="./gen/doc/"
if ! [[ -d "$gen_doc_path" ]]; then
	mkdir -p "$gen_doc_path"
fi

cmds=("ps" "pstree" "strace" "gdb" "strings" "objdump" "nm" "file" "od" "xxd" "fuser" "top" "awk"
	"cal" "ls" "chmod" "chown" "chgrp" "mkdir" "rmdir" "locate" "nftw" "touch" "cat" "more"
	"less" "cp" "mv" "rm" "grep" "tail" "head" "find" "sort" "stty" "sed" "uniq" "du" "df" "man"
	"help" "pr" "tr" "diff" "wc" "bc" "gzip" "history" "groups" "cut")

declare -A usages
usages=(["bc"]="bc"
	["cal"]="cal;cal -j;cal -m 3"
	["cat"]="cat test.txt;cat -b test.txt;cat -E test.txt"
	["chmod"]="chmod +x test.sh;chmod +r test.sh;chmod +w test.sh"
	["cp"]="cp test.txt dest/"
	["cut"]="cut --characters=3 testMod.txt"
	["df"]="df;df -h"
	["diff"]="diff test.txt testMod.txt"
	["du"]="du;du -sh .;du -b"
	["file"]="file test.c;file --extensions test.c;file --mime-encoding test.c"
	["find"]="find world.c"
	["fuser"]="fuser -l"
	["awk"]="gawk -F: '{print $1}' /etc/passwd"
	["gdb"]="gdb ./a.out"
	["grep"]="man grep | grep description"
	["groups"]="groups"
	["gzip"]="gzip test.txt"
	["head"]="head test.txt;head test.txt -n 4;head test.txt -c 10"
	["help"]="help"
	["history"]="history"
	["less"]="less test.txt"
	["locate"]="locate gedit"
	["ls"]="ls;ls -a;ls -l"
	["man"]="man man;man -k debugger;man -f smail"
	["mkdir"]="mkdir test/;mkdir -p test/nested1/nested2/"
	["more"]="more test.txt"
	["mv"]="mv src/test.txt ."
	["nm"]="nm -g"
	["objdump"]="objdump -f ./a.out;objdump -S ./a.out"
	["od"]="od test.c;od -a test.c;od -o test.c"
	["pr"]="pr test.txt;pr test.txt -d;pr test.txt -n"
	["ps"]="ps;ps axjf;ps axms"
	["pstree"]="pstree;pstree -c;pstree -p"
	["rm"]="rm test.txt"
	["rmdir"]="rmdir test/nested1/nested2/"
	["sed"]="sed 's/a/b/g' test.txt"
	["sort"]="sort test.txt;sort -r test.txt"
	["strace"]="strace gedit"
	["strings"]="strings test.c"
	["stty"]="stty;stty -a"
	["tail"]="tail test.txt;tail test.txt -n 4;tail test.txt -c 10"
	["top"]="top"
	["touch"]="touch test.txt"
	["tr"]="tr abc xyz;tr -c abc xyz"
	["uniq"]="uniq test.txt;uniq test.txt -c;uniq test.txt -d"
	["wc"]="wc test.txt;wc test.txt -c;wc test.txt -l;wc test.txt -L"
	["xxd"]="xxd test.c;xxd -i test.c;xxd -e test.c"
)

declare -A purposes=(["pstree"]="display a tree of processes"
	["gdb"]="the GNU Debugger"
	["help"]="display information about builtin commands"
	["strace"]="trace system calls and signals"
)

echo "commands: ${#cmds[@]}"
echo "completed: ${#usages[@]}"

# Generate commands
echo "Generating commands..."
count=1
for i in "${cmds[@]}"; do
	purpose="$(man "$i" | sed -n "4p" | cut -d"–" -f2-)"
	if ! [[ "$purpose" ]] && ! [[ "${purposes["$i"]}" ]]; then
		echo "Manpage for $i does not have a purpose and could not be found in the list of purposes."
		read -rp "Enter purpose for $i: " purpose
	elif ! [[ "$purpose" ]]; then
		echo "Found purpose for $i in the list of purposes. Using it."
		purpose="${purposes["$i"]}"
	fi
	imgs=()
	for img in assets/"$i"-*; do
		imgs+=("${img_template//%img%/$img}")
	done
	usage="$(echo "${usages["$i"]}" | tr ';' '\n')"
	imgs_expanded="$(echo "${imgs[@]}" | tr ' ' '\n')"
	filled_template="$(echo "$command_template" | sed "s|%name%|$i|; s|%purpose%|$purpose|")"
	filled_template="${filled_template//%count%/$count}"
	if [[ "$imgs_expanded" ]]; then
		filled_template="${filled_template//%imgs%/$imgs_expanded}"
	fi
	if [[ "$usage" ]]; then
		filled_template="${filled_template//%usage%/$usage}"
	fi
	echo "$filled_template" >"$gen_cmds_path/$count-$i.tex"
	count=$((count + 1))
done

# Generate final document

echo "Generating final document..."

filled_page_template="${page_template//%commands%/$(cat $(find "$gen_cmds_path"/* | sort --version-sort))}"
echo "$filled_page_template" >"$gen_doc_path/final.tex"

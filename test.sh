#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
NC=$'\033[0m'
YELLOW=$'\033[0;33m'

exe() {
	echo ${GREEN}"\$ $@"${NC} ; "$@" ;
}

echo ${RED}"================== $1 test ================="${NC}

if [ "$1" = "-h" ]; then
	echo "bash test.sh \
[-h | simple | argument | echo | return_value | double | single \
| export | unset | cd | pwd | relative | environment | redirection \
| pipes | crazy]"
elif [ "$1" = "simple" ]; then
	exe /bin/ls
	exe /bin/date
	exe /bin/bash
elif [ "$1" = "argument" ]; then
	exe /bin/ls ../minishell
	exe /bin/echo hello world
	exe /bin/pwd
	exe /bin/expr 1 + 1
elif [ "$1" = "echo" ]; then
	exe echo hello world
	exe echo -n hello world no nl
	exe echo
elif [ "$1" = "return_value" ]; then
	exe /bin/ls ../minishell
	echo ${GREEN}'$ echo $?'${NC} $?
	exe /bin/pwd
	echo ${GREEN}'$ echo $?'${NC} $?
	exe /bin/mkdir testfolder
	echo ${GREEN}'$ echo $?'${NC} $?
	exe /bin/ls filedoesntexist
	echo ${GREEN}'$ echo $?'${NC} $?
	rm -rf ./testfolder
elif [ "$1" = "double" ]; then
	echo ${GREEN}"$ echo \"cat minishell.c | cat > testfile\""${NC}
	echo "cat minishell.c | cat > testfile"
	echo ${GREEN}"$ echo \"hello world\"" "\" world\""${NC}
	echo "hello world" " world"
	echo ${GREEN}"$ echo \"\"hello world\"\""${NC}
	echo ""hello world""
elif [ "$1" = "single" ]; then
	echo ${GREEN}"$ date '+%D'"${NC}
	date '+%D'
	echo ${GREEN}"$ '/bin/ls ../minishell >> lol'"${NC}
	'/bin/ls ../minishell >> lol'
	echo ${GREEN}"$ cat lol"${NC}
	cat lol
	rm lol
	echo ${GREEN}"$ /bin/echo 'hello world | world hello'"${NC}
	/bin/echo 'hello world | world hello'
	echo ${GREEN}"$ echo 'hi this < is minishell'"${NC}
	echo 'hi this < is minishell'
	echo ${GREEN}"$ echo 'mini' '|' 'shell'"${NC}
	echo 'mini' '|' 'shell'
elif [ "$1" = "env" ]; then
	exe env
elif [ "$1" = "export" ]; then
	exe export new=new_one
	exe env
	exe export new=new_one2
	exe env
	exe export new2=new_two new3=new_three
	exe env
elif [ "$1" = "unset" ]; then
	exe unset new
	exe env
	exe unset new2 new3
	exe env
elif [ "$1" = "cd" ]; then
	exe cd ..
	exe /bin/ls
	exe cd ./minishell
	exe /bin/ls
elif [ "$1" = "pwd" ]; then
	exe pwd
	exe cd ..
	exe pwd
	exe cd ./minishell
	exe pwd
elif [ "$1" = "relative" ]; then
	exe mkdir ./testfolder
	exe cp /bin/echo ./testfolder
	exe ./testfolder/echo hello world
	exe mkdir ../testfolderoutside
	exe cp ./testfolder/echo ../testfolderoutside
	exe ../testfolderoutside/echo i am at outside
	
	exe rm -rf ./testfolder
	exe rm -rf ../testfolderoutside
elif [ "$1" = "environment" ]; then
	exe	ls
	exe date
	exe wc srcs/minishell.c
	exe unset PATH
	exe ls
	exe date
	exe wc srcs/minishell.c
	exe export PATH=/bin
	exe ls
	exe date
	exe wc srcs/minishell.c
	exe export PATH=/bin:/usr/bin
	exe ls
	exe date
	exe wc srcs/minishell.c
elif [ "$1" = "redirection" ]; then
	echo ${YELLOW}'truncate/create `file_one` and write `this is file_one` inside it'${NC}
	echo ${GREEN}'echo this is file_one > file_one'${NC}
	echo this is file_one > file_one
	echo ${GREEN}'< file_one cat'${NC}
	< file_one cat
	echo
	
	echo ${YELLOW}'truncate/create `file_one file_two` and write `this is file_two` to `file_two` skipping `file_one`'${NC}
	echo ${GREEN}'echo this is file_two > file_one > file_two'${NC}
	echo this is file_two > file_one > file_two
	echo ${GREEN} '< file_one cat'${NC}
	< file_one cat
	echo ${GREEN} '< file_two cat'${NC}
	< file_two cat
	echo
	
	echo ${YELLOW}'truncate/create `file_three` and write `this is file_three` inside it'${NC}
	echo ${GREEN}'> file_three echo this is file_three'${NC}
	> file_three echo this is file_three
	echo ${GREEN}'cat < file_three'${NC}
	cat < file_three
	echo 
	
	echo ${YELLOW}'append `file_three 2nd line` into `file_three`'${NC}
	echo ${GREEN}'>> file_three echo file_three 2nd line'${NC}
	>> file_three echo file_three 2nd line
	echo ${GREEN}'cat < file_three'${NC}
	cat < file_three
	echo
	
	echo ${YELLOW}'heredoc and expand env var, truncate/create `file_four` and write heredoc content into it'${NC}
	echo -e ${GREEN}'<< end cat > file_four\n' '$PATH\n' 'hello world\n' 'this is from heredoc'${NC}
	<< end cat > file_four
$PATH
hello world
this is from heredoc
end
	echo ${GREEN}'cat < file_four'${NC}
	cat < file_four
	
	exe rm file_one file_two file_three file_four
elif [ "$1" = "pipes" ]; then
	echo ${GREEN}'> file_one echo this is file_one'${NC}
	> file_one echo this is file_one ;
	echo ${GREEN}'>> file_one echo 2nd line in file_one'${NC}
	>> file_one echo '2nd line in file one'
	echo ${YELLOW}'show `file_one` content and pipe them into `grep` command to get string with substr `2nd` and pipe the output to `cat` command and write into `file_two`'${NC}
	echo ${GREEN}'cat file_one | grep 2nd | cat > file_two'${NC}
	cat file_one | grep 2nd | cat > file_two
	echo ${GREEN}'cat file_two'${NC}
	cat file_two
	echo
	
	echo ${YELLOW}'cat `file_two` content and write them into `file_one` then cat the `file_one` content'${NC}
	echo ${GREEN}'< file_two cat > file_one | < file_one cat'${NC}
	< file_two cat > file_one | < file_one cat
	echo
	
	echo ${YELLOW}'invalid file error then grep which outputs nothing and finally echo hello'${NC}
	echo ${GREEN}'ls filedoesntexist | grep bla | echo hello'${NC}
	ls filedoesntexist | grep bla | echo hello
	echo
	
	echo ${YELLOW}'heredoc and write some content and pipe the `cat` command output to `grep` command and grep munki which the the string with substr munki'${NC}
	echo -e ${GREEN}'<< end cat | grep munki\n' '$PATH\n' 'hello world\n' 'this is from heredoc'${NC}
	<< end cat | grep munki
$PATH
hello world
this is from heredoc
end
	exe rm file_one
	exe rm file_two
elif [ "$1" = "crazy" ]; then
	echo ${GREEN}'cat | cat | ls'${NC}
	cat | cat | ls
	echo ${GREEN}echo \'hello world\' \'welcome\' \"to my minishell\"${NC}
	echo 'hello world' 'welcome' "to my minishell"
	exe hfdsfjkslj
elif [ "$1" = "env_var" ]; then
	exe export hello="hello_world"
	echo ${GREEN}'echo $hello'${NC}
	echo $hello
	echo ${GREEN}'echo "$hello"'${NC}	
	echo "$hello"
	echo ${GREEN}'echo' ''\''$USER'\'''${NC}
	echo '$USER'
	echo ${GREEN}echo "\""'$USER'"\""${NC}
	echo "$USER"
	echo ${GREEN}echo "\"""'"'$USER'"'""\""${NC}
	echo "'$USER'"
	echo ${GREEN}echo "'"'"$USER"'"'"${NC}
	echo '"$USER"'
fi


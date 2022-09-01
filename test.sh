#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
NC=$'\033[0m'

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
	exe echo $?
	exe /bin/pwd
	exe echo $?
	exe /bin/mkdir testfolder
	exe echo $?
	exe /bin/ls filedoesntexist
	exe echo $?
elif [ "$1" = "double" ]; then
	exe echo "cat minishell.c | cat > testfile"
	exe echo "hello world" " world"
	exe echo ""hello world""
elif [ "$1" = "single" ]; then
	exe date '+%D'
	exe '/bin/ls ../minishell >> lol'
	exe /bin/echo 'hello world | world hello'
	exe echo 'hi this < is minishell'
	exe echo 'mini' '|' 'shell'
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
	echo ${GREEN}'echo this is file_one > file_one'${NC}
	echo this is file_one > file_one
	echo ${GREEN}'< file_one cat'${NC}
	< file_one cat
	echo
	
	echo ${GREEN}'echo this is file_two > file_one > file_two'${NC}
	echo this is file_two > file_one > file_two
	echo ${GREEN} '< file_one cat'${NC}
	< file_one cat
	echo ${GREEN} '< file_two cat'${NC}
	< file_two cat
	echo
	
	echo ${GREEN}'> file_three echo this is file_three'${NC}
	> file_three echo this is file_three
	echo ${GREEN}'cat < file_three'${NC}
	cat < file_three
	echo ${GREEN}'>> file_three echo file_three 2nd line'${NC}
	>> file_three echo file_three 2nd line
	echo ${GREEN}'cat < file_three'${NC}
	cat < file_three
	
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
	echo ${GREEN}'cat file_one | grep 2nd | cat > file_two'${NC}
	cat file_one | grep 2nd | cat > file_two
	echo ${GREEN}'cat file_two'${NC}
	cat file_two
	
	echo ${GREEN}'< file_two cat > file_one | < file_one cat'${NC}
	< file_two cat > file_one | < file_one cat
	
	echo ${GREEN}'ls filedoesntexist | grep bla | echo hello'${NC}
	ls filedoesntexist | grep bla | echo hello
	
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
	echo ${GREEN}\'hello world\' \'welcome\' \"to my minishell\"${NC}
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


# **Minishell**

## **About**
Minishell is the first project that requires 2 team members to complete in the 42 Core Programme. The main subject of this project is to replicate a shell with some exceptions. The main goal is to have a good understanding of processes, how bash works, signals handling, synchronisation in C Programming language.

---

## **Installation & Usage**
### **Requirements** (Used in development)
- Apple clang version 12.0.0
- GNU Make 3.81

---

### **Start**
1. Clone repo
   ```
	git clone https://github.com/hiromasa0629/minishell.git
   ```
2. cd and make
   ```
    cd minishell
    make
   ```
3. Run
   ```
   ./minishell
   ```

---

## **Subject**
- Not interpret unclosed quotes or unspecified special characters like \ or ;.
- Not use more than one global variable, think about it and be ready to explain why you do it.
- Show a prompt when waiting for a new command.
- Have a working History.
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
- It must implement the builtins:
  - **echo** with option -n
  - **cd** with only a relative or absolute path
  - **pwd** with no options
  - **export** with no options
  - **unset** with no options
  - **env** with no options or arguments
  - **exit** with no options
- **'** inhibit all interpretation of a sequance of characters.
- **"** inhibit all interpretation of a sequence of characters except for $.
- Redirections:
  - < should redirect input.
  - \> should redirect output.
  - "<<" read input from the currect source until a line containing only the delimiter is seen. It doesn't need to update history!
  - ">>" should redirect output with append mode.
- Pipes **|** The output of each command in the pipeline is connected via a pipe to the input of the next command.
- Environment variables ($ followed by characters) should expand to their values.
- $? should expand to the exit status of the most recently executed foregraound pipeline.
- ctrl-C ctrl-D ctrl-\ should work like in bash
- When interactive:
  - **ctrl-C** print a new prompt on a newline.
  - **ctrl-D** exit the shell.
  - **ctrl-\\** do nothing.
- Allow functions:
  - > readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history, printf,
malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, unlink, execve, dup,
dup2, pipe, opendir, readdir, closedir, strerror,
perror, isatty, ttyname, ttyslot, ioctl, getenv,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum,
tgetstr, tgoto, tputs

---

# **Evaluation**

**Running test.sh**
```
bash test.sh -h
```

### **Simple Command & global**

```bash
bash test.sh simple
/bin/ls
/bin/date
/bin/bash
```
>`g_status` is the only global variables I used which is a struct that records the exit status for each cmd and to determine whether or not to prompt a new readline

### **Arguments & history**
```bash
bash test.sh argument

/bin/ls ../minishell
/bin/echo hello world
/bin/pwd
/bin/expr 1 + 1
```

### **echo**
```bash
bash test.sh echo

echo hello world
echo -n hello world no nl
echo
```

### **exit**
```bash
exit
exit 2
exit abc
exit 2 1
exit abc 1
exit 1 abc
```

![Exit1](/images/exit1.png)
![Exit2](/images/exit2.png)
![Exit3](/images/exit3.png)
![Exit4](/images/exit4.png)

### **Return value of a process**
```bash
bash test.sh return_value

/bin/ls ../minishell
echo $?
/bin/pwd
echo $?
/bin/mkdir testfolder
echo $?
/bin/ls filedoesntexist
echo $?
```

### **Signals**
- **ctrl-c** should show a new line with new prompt
- **ctrl-\\** should not do anything
- **ctrl-d** exit minishell
- **ctrl-c** new prompt even you have wrote some stuff
- **ctrl-d** not do anything after you have wrote some stuff
- **ctrl-\\** not do anything after you have wrote some stuff
- **ctrl-c** after `cat`
- **ctrl-\\** after `cat`
- **ctrl-d** after `cat`

### **Double Quotes**
```bash
bash test.sh double

echo "cat minishell.c | cat > testfile"
echo "hello world" "world"
echo ""hello world""
```

### **Single Quotes**
```bash
bash test.sh single

/bin/date '+%D'
/bin/ls '../minishell >> lol'
/bin/echo 'hello world | world hello'
echo 'hi this < is minishell'
echo 'mini' '|' 'shell'
```

### **env**
```bash
bash test.sh env

env
```

### **export**
```bash
bash test.sh export

export new=new_one
env
export new=new_one2 # replace
env
export new2=new_two new3=new_three
env
```

### **unset**
```bash
bash test.sh unset

unset new
env
unset new2 new3
env
```

### **cd**
```bash
bash test.sh cd

cd ..
/bin/ls
cd ./minishell
/bin/ls
```

### **pwd**
```bash
bash test.sh pwd

pwd
cd ..
pwd
cd ./minishell
pwd
```

### **Relative Path**
```bash
bash test.sh relative

mkdir ./testfolder # if testfolder is not exist
cp /bin/echo ./testfolder
./testfolder/echo hello world
mkdir ../testfolderoutside # if testfolderoutside is not exist
cp ./testfolder/echo ../testfolderoutside
../testfolderoutside/echo i am at outside
```

### **Environment Path**
```bash
bash test.sh environment

ls
date
wc srcs/minishell.c
unset PATH
ls
date
wc srcs/minishell.c
export PATH=/bin
ls
date
wc srcs/minishell.c
export PATH=/bin:/usr/bin
ls
date
wc srcs/minishell.c
```

### **Redirection**
```bash
bash test.sh redirection

echo this is file_one > file_one
< file_one cat

echo this is file_two > file_one > file_two
< file_one cat
< file_two cat

> file_three echo this is file_three
cat < file_three
>> file_three echo file_three 2nd line
cat < file_three

<< end cat > file_four
$PATH
hello world
this is from heredoc
end
cat < file_four

rm file_one file_two file_three file_four
```

### **Pipes**
```bash
bash test.sh pipes

> file_one echo this is file_one
>> file_one echo 2nd line in file one
cat file_one | grep 2nd | cat > file_two
cat file_two

< file_two cat > file_one | < file_one cat

ls filedoesntexist | grep bla | echo hello

<< end cat | grep munki
$PATH
hello world
this is from heredoc
end

rm file_one
rm file_two
```

### **Go crazy and history**
```bash
bash test.sh crazy

cat | cat | ls
echo 'hello world' 'welcome' "to my minishell"
cmdsthatdontexist
```

### **Environment Variables**
```bash
bash test.sh crazy

export hello=hello_world
echo $hello
echo "$hello"
echo '$USER'
echo "$USER"
echo "'$USER'" # Bonus
echo '"$USER"' # Bonus
```

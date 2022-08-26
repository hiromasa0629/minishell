# **Minishell**

## **About**
Minishell is the first project that requires 2 team members to complete in the 42 Core Programme. The main subject of this project is to replicate a shell with some exceptions. The main goal is to have a good understanding of processes, how bash works, signals handling, synchronisation in C Programming language.

## **Installation & Usage**
### **Requirements** (Used in development)
- Apple clang version 12.0.0
- GNU Make 3.81

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

## Subject
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
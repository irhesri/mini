# Minishell

**Minishell** is a small command-line interpreter written in C language that is designed to mimic the behavior of the popular Unix shell, **Bash**. 
It provides a basic command-line interface to users that allow users to execute basic commands and handle simple I/O operations.
___
## Requirements:
* gcc
* make
* readline

  ➜ Requirements installation for Debian distributions:
``` shell
sudo apt-get install gcc make libreadline8 libreadline-dev
```
## Installation
``` shell
git clone https://github.com/irhesri/mini.git
cd mini
make
```

## Usage
* Start The executable:
``` shell
./minishell
```
Once the program is running you can start using it by entering the commands you want to run.
 
## Features
* The program display a prompt waiting for a new command

  ### ➜ Builtins:
    The builtins do the same work as the ones of bash:
    * **echo** : with option -n
    * **cd** : with only a relative or absolute path
    * **pwd** : with no options
    * **export** : with no options
    * **unset** : with no options
    * **env** : with no options or arguments
    * **exit** : with no options

  ### ➜ Commands other than builtins:
    * The program runs the commands by launching the right executable based on the PATH variable or by using a relative or an absolute path

  ### ➜ Redirections:
    * **<** : redirect input
    * **<<** `delimiter` : should be given a delimiter, it reads the input until a line containing the delimiter is seen
    * **>** : redirect output in truncate mode
    * **>>** : redirect output in append mode

  ### ➜ Interactive mode:
    * <kbd> ctrl </kbd> + <kbd> C </kbd> : displays a new prompt on a new line
    * <kbd> ctrl </kbd> + <kbd> D </kbd> : exits the shell
    * <kbd> ctrl </kbd> + <kbd> \ </kbd> : does nothing 

  ### ➜ History:
    * <kbd> ↑ </kbd> (up) and <kbd> ↓ </kbd> (down) arrows : go through the command history

  ### ➜ Others:
    * **|** (pipes) : </b> The output of each command in the pipeline is the input of the next command via a pipe
    * **$**`environment variable name` : it get expanded to its value
    * **$?** : get expanded to the exit status of the most recently executed foreground pipeline

    > Note: The program does not interpret unclosed quotes or "\\" (backslash) or ";" (semicolon).

## Restrictions:
* Only the next functions are allowed:
  >readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
* Not use more than one global variable. 

## Conclusion:
***Minishell*** is a small but useful project that provides a basic set of functionalities and commands similar to the bash shell. And developing it was an enriching learning experience where we were able to understand the core concepts of the command-line interfaces and the underlying system mechanisms that enable them to work by implementing them in a real-world project. Moreover, working on this project we gained practical knowledge about ***multiprocessing*** (creating child processes), ***executing system commands***, ***handling signals***, ***files manipulating***, implementing features such as ***piping*** and ***redirections***, and some ***shell functionalities***.
Overall, Minishell was an incredibly rewarding experience that deepened our knowledge and skills in ***system programming*** and ***command-line interfaces***.


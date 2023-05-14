# Minishell

## Requirements:
<ul>
  <li> gcc </li>
    <li> make </li>
    <li> readline </li>
</ul>

➜ Requirements installation for Debian distributions:
```
sudo apt-get install gcc make libreadline8 libreadline-dev
```
## Installation
```
git clone https://github.com/irhesri/mini.git
cd mini
make
```

## Usage
➜ Start The executable:
```
./minishell
```
Once the program is running you can start using it by entering the commands you want to run.
## Features
➜ The program display a prompt waiting for a new command
### Builtins:
➜ The builtins do the same work as the ones of bash
<ul>
  <li> <b> echo : </b> with option -n </li>
    <li> <b> cd : </b> with only a relative or absolute path </li>
    <li> <b> pwd : </b> with no options </li>
    <li> <b> export : </b> with no options </li>
    <li> <b> unset : </b> with no options </li>
    <li> <b> env : </b> with no options or arguments </li>
    <li> <b> exit : </b> with no options </li>
</ul>

### Commands other than builtins:
<ul>
  <li> The program runs the commands by launching the right executable based on the PATH variable or by using a
relative or an absolute path </li>
</ul>

### Redirections:
<ul>
  <li> <b> < : </b> redirect input </li>
  <li> <b> << [<i>delimiter</i>] : </b> should be given a delimiter, it reads the input until a line containing the
delimiter is seen </li>
    <li> <b> > : </b>  redirect output in truncate mode </li>
    <li> <b> >> : </b> redirect output in append mode </li>
</ul>

### Interactive mode:
<ul>
  <li> <kbd> ctrl </kbd> + <kbd> C </kbd> : displays a new prompt on a new line </li>
    <li> <kbd> ctrl </kbd> + <kbd> D </kbd> : exits the shell </li>
    <li> <kbd> ctrl </kbd> + <kbd> \ </kbd> : does nothing </li>
</ul>

### History:
<ul>
  <li> <kbd> &#8593 </kbd> (up) and <kbd> &#8595 </kbd> (down) arrows : go through the command history </li>
</ul>

### Others:
<ul>
  <li> <b> | (pipes) : </b> The output of each command in the pipeline is the input of the next command via a pipe </li>
    <li> <b> $[<i>environment variable name</i>] : </b> it get expanded to its value </li>
    <li> <b> $? : </b> get expanded to the exit status of the most recently executed foreground pipeline </li>
</ul>

> Note: The program does not interpret unclosed quotes or "\\" (backslash) or ";" (semicolon).

## Restrictions:
<ul>
  <li> Only the next functions are allowed: </li>
</ul>

>readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

<ul>
  <li> Not use more than one global variable. </li>
</ul>

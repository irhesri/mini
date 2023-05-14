# Minishell

## Requirements
### Requirements for Linux

<ul>
  <li> make </li>
  <li> gcc </li>
  <li> package xorg </li>
  <li> package libxext-dev </li>
  <li> package libbsd-dev </li>
</ul>

Requirements installation for Debian Distributions:
```
➜ sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```
### Requirements for Mac

<ul>
  <li> Xquartz </li>
</ul>

Requirements installation:
```
➜ Brew install Xquartz
➜ reboot
➜ xeyes
```

## Installation
```
➜ git clone https://github.com/irhesri/mini.git
➜ cd mini
➜ make
```

## Usage
Start The executable:
```
➜ ./minishell
```
Once you do that You can 
### Features
#### Builtins:
<ul>
  <li> <b> echo </b> with option -n </li>
    <li> <b> cd </b> with only a relative or absolute path </li>
    <li> <b> pwd </b> </li>
    <li> <b>  </b> </li>
</ul>

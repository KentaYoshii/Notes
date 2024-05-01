# Shell Script
- Shell is like a container that serves as an interface between the user and OS
- To view
    - `echo $0`
    - /etc/passwd contains the default shell for each user
- Shell Script
    - An executable file containing multiple shell commands that are executed sequentially
    - Can contain
        - shell (#!/bin/bash)
        - comments (#)
        - commands (echo, cp, etc.)
        - statements (if, while, etc.)
        - variables 
        ```sh
        a=kenta
        echo "Hello World to $a"
        ```
    - It should have executable perm
    

## Types of Linux Shells
- `cat /etc/shells` will list all the available shells
- GUI-based
    - Gnome
    - KDE
- CLI-based
    - sh
        - bourne shell
    - bash
        - enhanced sh (bourne again shell)
    - csh and tcsh
    - ksh

## Basic Shell Scripts
- $? 
    - stores the output of last command
        - 0 -> ok status
- &>name (basically 1>name 2>name)
- Variable
    ```sh
    a=hostname
    echo Hello $a # print: Hello hostname
    a=`hostname`
    echo Hello $a # print: Hello <hostname of the system>
    ```
- Input and Output 
    - `read <var_name>`
        - read user input and store it in var_name
        - can be used by $var_name

- If-then
    ```sh
    if [ $count -eq 100 ]
    then 
        echo Count is 100
    else 
        echo Count is not 100
    fi

    if [ -e /home/error.txt ] # check if file exists
    ```
- For loops
    ```sh
    for i in 1 2 3 4 5
    do 
    echo $i
    done
    ```
- Do While
    ```sh
    while [ condition ] 
    do 
        command1
        command2
        command3
    done
    ```
- Case
    ```sh
    case $variable in 
    a) command1;;
    b) command2;;
    c) command3;;
    *) command4;;
    esac
    ```

## Aliases
- Popular command that is used to cut down on lengthy and repetitive commands
    ```sh
    alias ls="ls -al" # if no error then alias is created
    ```
    - Only remain through session 
- User Alias 
    - applies only to a specified user profile
    - `/home/user/.bashrc`
- Global Alias
    - applies to all users in the system
    - `/etc/bashrc`

## Shell History
- `history` command
    - show all the commands you have run
    - each past command will have id associated with it
    - you can run past command by
        - `!<number>`
- /home/username/.bash_history stores all the past commands
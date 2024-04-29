# Linux Fundamentals
- Command Syntax
    ```
    command option(s) argument(s)
    ```

## File Permissions
- Types
    - read (r), write (w), execute (x)
- Levels
    - user, group, other
- Command to change permission 
    - `chmod`
    ```
    chmod g-w <filename> // remove write from group
    chmod a-r <filename> // remove read from all
    ```
- x on directory means you can `cd` into the directory

## Access Control List (ACL)
- It provides an additional, more flexible permission mechanism for fs
    - Allows you to give permissions for any user or group to any disc resource
- `setfacl` and `getfacl` 
    ```
    setfacl -m u:user:rwx <file path> // add perm for user
    ```
    - \+ sign at the of the permission means there's ACL associated with the resource

## Help commands
- `whatis <command>` 
    - short explanation of a command
- `<command> --help`
    - medium explanation of a command
- `man <command>` 
    - full explanation of a command

## Adding text to a file
- `vi`
    - via editor
- `echo <sometext> [> | >>] <file>`
- redirect command output
    - `ls > hello`

## Input and Output
- stdin (fd 0)
    - use `<` when feeding file content 
        - `cat < hello`
- stdout (fd 1)
    - default output for command
    - command output can be routed using `>`
- stderr (fd 2)
    - Any error from running a command is written here
    - `ls /etc 2> log` 
        - routes error message to log file

## Tee
- `tee` is used to store and display the output of a command at the same time
    - `echo "hello world" | tee <filename>`

## Pipes
- Used by the shell to connect the output of one command to the input of another command
- `command1 [arg] | command2 [arg]`

## File Display Commands
- `cat`
    - print the whole content
- `more`
    - print one page at a time
- `less`
    - same as `more` but more finer control
        - i.e., can view one line at a time
- `head`
    - can view the first N lines
- `tail`
    - can view the last N lines

## Compare Files
- `diff`
    - comparison is done line by line
- `cmp`
    - comparison is done byte by byte

## File Compression
- `tar`
    - used to combine multiple files into a single `.tar` file
    - not compressed
- `gzip` 
    - used to compress a file 
- `gzip -d` or `gunzip` 
    - used to un-compress a file

## File Truncation
- `truncate` to shrink or extend a file
    - if shrink, the overflowing bytes are thrown out
    - if extend, the empty bytes are padded with @

## Combining and Splitting Files
- Combine
    - `cat file1 file2 file3 > file4`
- Split
    - `split -l <number> <originalfile> <dest>`
        - split originalfile so that each destaa destab,... contains number line each

## Text Processor Command
- `cut`
    - CLI utility that allows you to cut parts of lines from specified files or piped data and print the result to stdout
    ```sh
    cut -c1 filename # grab the first character for each line
    cut -c1,3,5 filename # grab the 1,3, and 5th char for each line
    cut -c1-3 filename # grab 1-3 chars for each line
    cut -d: -f 6 /etc/passwd # use : as delimitter and grab the 6th element for each line
    ls -l | cut -c2-4 # grab the user perm
    ```
- `wc`
    - Reads stdin or list of files and generates __newline__ count, __word__ count and __byte__ count
    ```sh
    wc <filename> # prints: [number of lines] [number of words] [number of bytes] 
    wc -l <filename> # prints the number of lines
    ls -l | wc -l # prints the number of files in current dir
    grep <keyword> | wc -l # number of lines with keyword
    ```
- `awk`
    - Used to extract fields from a file or form an output
    ```sh
    awk `{print $1}` file # give the first column
    awk '/keyword/ {print}' file # give the line that contains keyword
    ```
- `grep`/`egrep`
    - Processes text line by line and prints any lines which match a specified pattern
    ```sh
    grep keyword file # give me lines that contain keyword
    -c # flag that gives you matching count
    -i # turn off case-sensitivity
    -n # display matching line with line numbers
    -v # display all lines without the keyword
    egrep -i "keyword1|keyword2" file # egrep for two keywrods
    ```
- `sort`
    - sorts the content in alphabetical order
    ```sh
    sort <filename> # sort by first letter
    sort -k2 <filename> # sort by second column
    ```
- `uniq`
    - filters out the __repeated__ or dupliate lines
    - uniq always requires sort first!
    
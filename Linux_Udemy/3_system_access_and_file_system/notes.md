# 3 System Access and File System
- Root is the most powerful acc that can do anything to system configuration files
- Linux is a case-sensitive system
- Linux kernel is not an OS
    - A small software within Linux OS that takes commands and pass them to system HW
## Access
- console
    - direct access to OS 
        - HDMI, VGA, etc.
- remote
    - connect OS remotely over the network
    - you need the IP address to connect
    - run `ssh -l <username> <IP addr>` on the host terminal to connect to guest machine
        - IP addr can be obtained via `ifconfig` or `ip addr`
    
## Command Prompt
- [username@hostname]# prompt symbol
    - \# means root 
    - \$ is any other user

## Filesystem
- OS stores files and directories in an organized way
- ext3, ext4, NTFS, etc.
- Each fs has its own way of doing this
- Linux 
    - __/boot__
        - Contains file that is used by the boot loader
        - OS finds this first upon start (hardcoded)
    - __/root__ 
        - Root user home directory
        - Distinct from /
    - __/dev__
        - System devices 
            - Disk, cdrom, speakers, etc.
    - __/etc__
        - Configuration files
    - __/bin__ -> __/usr/bin__
        - Everyday user commands (i.e., ls)
    - __/sbin__ -> __/usr/sbin__
        - System/FS commands
    - __/opt__ 
        - Optional add-on applications 
    - __/proc__
        - Running processes 
        - In-memory 
        - Empty upon reset
    - __/lib__ -> __/usr/lib__
        - C programming library files needed by commands and apps
    - __/tmp__ 
        - Directory for temporary files
    - __/home__ 
        - Directory for user
    - __/var__
        - System logs
    - __/run__
        - System daemons that start very early to store temporary runtime files 
            - like PID files
    - __/mnt__
        - To mount external filesystem (NFS)
    - __/media__
        - For cdrom mounts

## Navigating Filesystem
- `su`
    - switch user 
    - use to change to other user
        - for root, `su -`
- `cd`, `ls`, etc.
## Linux File or Directory 
- `ls -l`
- If type (first col) starts with 
    - `d` == directory
    - `l` == link
    - `-` == regular file
    - `c` == special/device file
    - `s` == socket
    - `p` == named pipe
    - `b` == block device
- Second column is the _number of links_

## Changing password
- `passwd userid`

## Paths
- Absolute path always starts with a `/` (root)
- Relative path does not start with a `/`

## Finding Files and Directories
- `find <start search dir> -name <name of the file>`
    - Iterates over a filesystem to locate files
- `locate <file name>`
    - Uses a prebuilt database/cache
        - to update `updatedb` (need to be root)
        - by default it runs every once in a while
    - Faster but could be inaccurate

## Wildcards
- A character that can be used as a substitute for any of a class of characters in a search
    - `*` represents zero or more chars
        - `ls -l abc*`
        - `rm abcd*`
    - `?` represents a single character
    - `[]` represents a range of characters

## Soft Links and Hard Links
- __inode__
    - Pointer or number of a file on the hard disk
    
![](Screenshot%202024-04-29%20at%207.50.10.png)
- __soft link__
    - Link will be removed if file is removed or renamed
    - `ln -s <src> [dest]`
- __hard link__
    - Deleting, renmaing, or moving the original file will not affect the hard link
    - `ln <src> [dest]`
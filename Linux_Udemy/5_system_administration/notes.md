# Linux System Administration

## Text Editor
- Linux comes with various editors
- `vi` is built-in to every distro

## sed 
- `sed` command
    - Stream editor for filtering and transforming text
    ```sh
    sed -i 's/Kenny/Lenny/g' # -i to save to file, s for substitute, Kenny with Lenny, globaly
    sed '/Seinfeld/d' # delete a line that matches keyword
    sed '1d' # delete the first line
    sed '1,2d' # delete the first two lines 
    ```

## System Utility Commands
- `date`
    - tells you date and time
- `uptime`
    - tells you system uptime, number of users logged in, and load average
- `hostname`
    - tells you the system name
- `which`
    - tells you the location of the command
- `cal`
    - gives you calendar
- `bc` (binary calculator)
    - gives you a calculator

## User Account Management
- `useradd <name>` to create a new user
    - `id <name>` to verify 
    - `userdel -r <name>` to delete a user
- `groupadd <name>` to create a new group
    - `/etc/group` to verify
    - `groupdel <name>` to delete a group
- `usermod` modifies a user account
    - `usermod -G <groupname> <username>` to add a username to groupname
- `/etc/passwd`
    - new user information is added
- `/etc/shadow`
    - contains encrypted password
- `useradd -g <groupname> -s <shell> -c <description> -m -d <home directory> <username>`
    - all in one
- `passwd <username>` to set a password
- `/etc/login.defs` contains various information about account management
- `chage` command lets you set various parameters for user passwd

## Swithing Users
- `su` to switch users
- `sudo` to run different commands that only root can run
- `visudo` to edit `/etc/sudoers`

## Talking to Users
- `wall` to broadcast messages
- `write <username>` write to a specific user

## Account Authentication
- Local 
    - Local accounts created via useradd, etc.
- Domain
    - Authenticate via a server which keeps track of valid accounts
- Directory Services
    - Active Directory 
        - Owned by Microsoft
        - Account authenticated against Active Directory Server
    - Identity Manager (IDM)
        - Linux version of Active Directory
    - WinBIND
        - Used in Linux to communicate with Windows
        - Allows Window Active Directory Users to login to Linux machine
    - OpenLDAP
        - Lightweight Active Directory Protocol (LDAP)
        - open-source version of IDM used for Unix/Linux

## Monitor
- `who` 
    - tells you information about who is logged in to the system
- `last`
    - tells you every user that logged in 
- `pinky`
    - print user information
- `id`
    - print user information (gid, uid, etc.)

## Processes and Jobs
- Terms 
    - Process
        - Spawned for each application
        - can be 1 application to many
    - Threads
        - Process can have multiple threads
    - Job
        - Run a process at a scheduled time (scheduled by a scheduler)
    - Daemon 
        - Process that runs until interrupted
- `systemctl`
    - Tool to control system services
    ```sh
    systemctl start|stop|restart|status servicename.servie
    systemctl enable servicename.service # run on boot
    systemctl list-units --all # list all services
    ```
- `ps`
    - Displays all the currently running processes in the system
        - PID, TTY, TIME, CMD
        - `-e` flag to display all procs
        - `-f` flag to see in ful format
        - `-u <username>` show all procs by username
- `top`
    - Displays the Linux pros and provides a real-time view of the running system
        - It will enter interactive mode

- `kill`
    - kills the process by name or PID
    - Types
        - `-1` restart
        - `-2` interrupt (Ctrl+C)
        - `-9` force kill
        - `-15` graceful kill
- `crontab` 
    - used to schedule services
    - entry format
        ```sh
        minute hour day month <command to execute>
        ```
    ```sh
    crontab -e # edit the crontab
    crontab -l # list the entries
    ```
- `at.`
    - like crontab but only once
    - at HH:MM PM
        - this will open a editor
        - type in the command you want to run
        - Ctrl+D
- Cron Jobs
    - Out-of-the-box, Linux comes with 4 different types of cronjobs
        - Hourly, Daily, Weekly, and Monthly
    - All the above crons are setup in `/etc/cron._`
        - Simply place the scripts that you want to be executed under each directory


## Control Keys
- CTRL-u 
    - erase everything you've typed on CLI
- CTRL-c 
    - stop/kill a command
- CTRL-z
    - suspend a command (put the proc in the bg)
- CTRL-d 
    - exit from an interactive program

## Terminal Commands
- `clear`
    - clear your screen
- `exit`
    - exit out of the shell, terminal or a user session
- `script`
    - stores terminal activities in a log file 

## Special Permissions
- These bits only work on C executables
- `setuid`
    - a bit thattells Linux to run a prog with the EUID of the UID of the file
- `setgid`
    - a bit that tells Linux to run a prog with the EGID of the GID of the file
- `sticky` bit
    - a bit set on files/directories that allows only the owner or root to delete them
    - assigned to the last bit of permissions

## Process Management
- When you run process on your terminal, it will not give your prompt back (this is called the _foreground_ process)
- `Ctrl+z`
    - suspend the foreground process
- `bg`
    - put the recently suspended process in the background
- `fg`
    - put the recently suspended process in the foreground
- `&` 
    - run a program in the background to begin with
- `pkill`
    - kill a process by name
- `jobs`
    - list child processes under terminal shell
- `nice -n <prio> command`
    - set process priority and run
    - scale goes from -20 to 19 (the lower the number, more priority that task gets)

## System Monitoring
- `top`
    - Provides info about running processes
- `df`
    - Provides info about disk partition and memory usage
- `dmesg`
    - Provides
- `iostat`
    - Provides CPU statistics and input/output statistics for devices and partitions.
- `netstat`
    - Provides network connections, routing tables, interface
    statistics, masquerade connections, and multicast memberships
- `free`
    - Provides info about amount of free and used memory in the system

## System Maintenance Command
- `shutdown`
- `init 0-6`
- `reboot`
    - reboots the computer
- `halt`
    - shuts down the computer right away

## Log Monitoring
- `/var/log` is the log directory
    - boot 
    - chronyd 
    - cron
    - maillog
    - secure
    - messages 
    - httpd
    - ...
# Networking

## Network 
- `ifconfig`
    - tells you interface information
    - `ifup` or `ifdown` to bring up/down your interface
- Network Interface Card (NIC)
    - Comes installed 
    - `ethtool <intf name>` to view information about it
- NIC Bonding
    - Aggregation or combination of multiple NIC into a single bond interface
        - To provide high availability and redundancy 
- Network Manager
    - Provides set of tools designed specifically to make it easier to manage network on Linux
    - `nmcli`
        - network manager command line interface
    - `nmtui`
        - networm manager text user interface
- Dowloading Stuff
    - `wget`
        - tool for manually dowloading files from the web
        - `wget <loc_filename>`
    - `yum`
        - package management utility for installing, updating, and managing software packages on RPM-based distro
## File Transfers
- Secure Copy Protocol  
    - Secure version of FTP 
    - Transfer files from A to B
    - Default port is 22 (same as SSH!)
        - piggyback on SSH
    - `scp <filename> <username>@<ip>:<destination>`
- Remote Synchronization
    - `rsync` is a utility for efficiently transferring and syncing files within the same computer or to a remote computer 
    - Mostly used to backup the files/dirs

## System Updates
- `yum` (CentOS), `apt-get` (other distros)
    - installs a package pre-defined in your Linux system
        - dependenies as well
        - all package comes with command
    - `update` will upgrade all installed packages on the system to their latest available versions
- `rpm` (Red hat Package Manager)
    - used when you already have a package downloaded in your system
        - so installation only
    - `rpm -qa` returns all the installed packages     

## DNS
- Purpose   
    - Converts Hostname to IP address (_A_ record)
    - IP to Hostname (_PTR_ record)
    - Hostname to Hostname (_CNAME_ record)
- Hostname/IP lookup
    - `nslookup`
        - old utility 
        - `nslookup <domain name>`
    - `dig`
        - `dig <domain name>`

## SSH without password
- ssh-keygen on client machine
- ssh-copy-id <username>@<server_addr>
- then login

## Container
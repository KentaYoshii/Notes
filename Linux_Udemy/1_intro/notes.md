# Intro to Linux
## Operating System
- System software that manages computer HW and SW resources and provides common services for computer programs
- Many different types
    - Desktop OS
        - Microsoft Windows, macOS, Linux Ubuntu
    - Server OS
        - Linux CentOS, Red Hat 
    - Mobile OS
        - Android, iOS, Windows Mobile
    - Embedded OS
    - Real-Time OS

## Linux
- Linux
    - Free and open-source operating system
    - Popular for stability, security, and flexibility
        - can be modified and distributed by anyone ("distributions")
        - each distribution has its own use case
    - Widely used in _servers_ and _cloud computing_
- History
    - Before Linux, __Unix__ existed
        - Not freely available
    - GNU Project
        - Aim to create free UNIX like system
    - Birth of __Linux__
        - Android is based on Linux kernel!
## Linux v.s. Unix
- Origin
    - Unix
        - 1970s
    - Linux
        - 1990s
- OS Distribution
    - Unix
        - Solaris, HP-UX, AIX...
    - Linux
        - Red Hat, CentOS, Fedora, Kali, Ubuntu
- Cost
    - Unix
        - Generally requires a paid license
    - Linux 
        - Free to use, modify and distribute
- Community and Development
    - Unix
        - Dev and updates are controlled by the owing org
            - Solaris == Oracle
    - Linux
        - Maintained by global community of devs

## Linux Flavors
- Linux flavors
    - == Linux distributions
- Distributions
    - Ubuntu
        - Distro based on Debian
        - Provides user friendly experience
    - Debian
        - Distro known for stability and provides foundation for many other distros
    - Fedora
        - Known for cutting-edge features and innovations
    - Red Hat Enterprise Linux (RHEL)
        - Designed for businesses and enterprises
    - CentOS
        - Free and open-source clone of RHEL
    - Arch Linux
        - Distro known for simplicity and customization
    - openSUSE
    - Linux Mint
        - Distro based on Ubuntu and comes with built-in tools to play media
    - Gentoo
    - Slackware
        - Distro designed for simplicity
    - Alpine Linux
        - Distro designed for security, simplicity, and resource efficiency
    - Kali Linux
        - Distro designed for forensics and penetrating test

## Linux v.s. Windows
- Price
    - Linux
        - Free
            - RedHat is not free
    - Windows 
        - Not free
- Software
    - Linux
        - Mostly enterprise level softwares
    - Windows
        - Much larger selection of softwares
- Security
    - Linux 
        - Very secure
    - Windows
        - Somewhat secure
            - Because it is used when accessing the internet

## Inside Linux
- Kernel
    - The core of the Unix system
    - Loaded at system boot and is memory-resident control program
    - Functions 
        - Managing machine's memory and allocation
        - Scheduing the work done by the CPU
        - Transfering of data
        ...
- Shell
    - Command Interpreter
    - Takes in a command and passes it to the OS kernel to be acted upon
    - Several shells are usually available, each with its own strenghs and weaknesses
        - Bourne shell (_sh_)
        - Bourne Again Shell (_bash_)
        - ...
    - Each shell also includes itsown programming language
- Utilities
    - Unix provides several hundred utility programs (or commands) that can be grouped to perform more complex tasks

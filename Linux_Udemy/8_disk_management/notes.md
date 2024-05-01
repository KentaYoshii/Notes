# Disk Management and Run Levels

## Computer Boot Process
- Plug in your omputer
- Electricity powers CPU
- Bootstrap Proess
    1. CPU goes to BIOS (Basic Input/Output Setting)
    2. CPU starts and pulls instructions from BIOS software stored in ROM
    3. BIOS also consults CMOS (which is powered by battery) for additional instructions
    4. BIOS then does POST (Power-On Self-Test)
        - check every hardware device to make sure they are healthy
    5. BIOS goes to MBR (Master boot record)
        - this contains information about where GRUB is located so it can be loaded in RAM

- Linux Boot Proess
    - BIOS
    - MBR
        - Contains informaiton for GRUB
    - Grand Unified Bootloader executes Kernel (GRUB)
        - Load the Kernel
    - Kernel loads required drivers and start the first OS proess (_systemd_)
    - Systemd (PID=1) starts all the required processes
        - Read /etc/systemd/system/default.target to bring the system to correct run-evel (0 through 6)

## Computer Storage
- Storage Types
    - Local 
        - RAM, HDD, SSD, etc.
    - DAS (Direct Attached Storage)
        - CD/DVD, USB, external disks
    - SAN (Storage Area Network)
        - Storage attached through fiber cable
    - NAS (Network Attached Storage)
        - Storage attached over network 
        - NFS, Samba
- Logical Volume Management (LVM)
    - An abstraction layer between physical storage devices and the file system
    - Allows you to combine multiple physial disks together
- Swap Space
    - Used when RAM is full. 
    - Located on hard drives
    - Inative pages in memory are moved to the swap space
    - Can be extended (by creating a file on disk and dedicating it to be used as swap space) or shrinked
- SATA and SAS
    - Both uses serial communication 
        - 1 cable and two highways that go in each direction between the motherboard and disk
        - more compact
    - Serial Advanced Technology Attachment (SATA)
        - Less expensive and more suited for desktop
    - Serial Attached SCSI (SAS)
        - Faster and more reliable
        - More expensive and more suited for server
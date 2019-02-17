# **Introduction to kernel** #

## **2.2 Introduction to System Concepts** ##


### **2.2.1 Overview of File subsystem** ###

### **Data February 17 2019** ###
1. Every File has a single Inode Entry, but multiple file can contain reference to that single Inode. Each Name reference to an Inode is Called *link*.

2. The Kernel contains 3 data structures to mangae files.
    -   **Inode Table:** Contains Information Related to file data
    -   **File Table** Contains Information related to offset for next read or write by any user. also contains the information related to required permission for accessing the file (Global Datastructure)
        - **TODO:** Read same file with two different users and check if file offset remains same for each user after the other user have modified the offset.
    -   **User File Descriptor Table:** Contains information about all open files by a single process. This structure is allocated per process. The call to **open()** or **read()** returns a **file descriptor** that serves as an index in this table.

3.  The size of logical block is *homogeneous* across a single file system but may very under different file systems.

4.  A large logical block size is fast for I/O(example, a 1024 block size is twice faster then 512 bytes logicl block size), but it also increase disk fragmentation. which results in inefficent use of disk space.

5. The File system structure is as follow   
    |------boot-block------|------->|-------super-block-------| ---------> |-------inode-block-------| -------    
        ------------> |-----data-block-------|

-   **Boot Block:** Contains code for booting up the system, mostly this code is written in asm. Of all the file systems one must contain the Boot code for system to successfully bootup
-   **Super Block:** This contains the information related to that file system, like number of blocks in file system, number of data , inode blocks, where to find free space etc.

Example(code excerpt taken from xv-6, fs.h)
```
struct superblock {
  uint size;         // Size of file system image (blocks)
  uint nblocks;      // Number of data blocks
  uint ninodes;      // Number of inodes.
  uint nlog;         // Number of log blocks
  uint logstart;     // Block number of first log block
  uint inodestart;   // Block number of first inode block
  uint bmapstart;    // Block number of first free map block
};
```

-   **Inode Block:** Contains on-disk inode-list. the kernal references Inodes by index into the inode list. one of the Inode is the root of the File system. this inode is used to access the directory structure of the file-system after a successful mount call.

Example(from xv-6, fs.h)

```// On-disk inode structure
struct dinode {
  short type;           // File type
  short major;          // Major device number (T_DEV only)
  short minor;          // Minor device number (T_DEV only)
  short nlink;          // Number of links to inode in file system
  uint size;            // Size of file (bytes)
  uint addrs[NDIRECT+1];   // Data block addresses
};
```
-   **Data Block:** Used to store the actual file data. a single data block can belong to one and only one file in file system.

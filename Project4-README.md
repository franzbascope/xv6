# Project 4

## Group members

- Franz Bascope Jordan (U07511108)
- Abdullah Al Monsur (U85640940)

### Part 1 lseek implementation

We implemented lseek by:

1. Use argdfd to fetch the struct file
2. Lock the inode.
3. Increment the file offset by the given parameter.
4. Unllock the inode.

- I created the program **test_lseek.c** to prove its working correctly, for more information and screenshots check the folder **project4/lseek**

### Part 2 adding support for symbolic links

We implemented symbolic links by:

1. Creating a sys_symlink system call , here we create an inode and write the target path in its data.
2. We modified the open system call to be able to follow symlinks and do this recursiverly for 10 times before returning an error result.
3. We added a flag NO_FOLLOW in the case we want to see the content of the symlink itself
4. All this functionalities are executed and tested in program **test_symlink.c** , we added screenshots in **project4/symbolic_links**

### Part 3 adding support for large files

This is how we implemented double-indirect block:

1. We modified the number of direct links to 10 , leaving space for 1 indirect link and 2 double-indirect links.
2. We modified addrs in file.h and file.c to be direct links +3 , for a total of 13 links.
3. We defined a constant NDOUBLEINDIRECT which is the size of NINDIRECT * NINDIRECT
4. We modified bmap to handle two double indirect links with the following steps:
    - We reduce bn by NINDIRECT size to get the desired block number.
    - We read the first double indirect block, if not present we allocate it
    - We find the first and second level index.
        - Second level index is block number / amount of indirect links that fit in a block.
        - First level index is the remainder of block number with the max number of indirect links
    - We read the second level and allocate if necessary.
    - We read the first level and allocate if necessary.
    - We return addr
    - We do the same forthe second double indirect block whe block number is greater than NDOUBLEINDIRECT.
5. The program to test this is **test_largefiles.c**, screenshots and diagram are in folder **project4/large_files_support**

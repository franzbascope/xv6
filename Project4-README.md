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

### Part 4 extent based file system

- Test program: **test_extent.c**
- Stat program: **stat.c** e.g `stat test_extent.txt`
- Screenshots: ./project4/extrent_based_file_system 

This is how we implemented extent based file system.

1. We took the approach of using 3-bytes for the block address and 1-byte for the length of the extent , we use 6 extents and the remaining slots we use them as bitmap to know if the extent has already finished. e.g when cannot allocate more consecutive blocks in that extent.
2. We modify bmap to treat T_EXENT files
    - We iterate over the NEXTENTS, which is 6.
    - if the block number is greather than 255, our 1-byte for length , we set block number to 0 and change to the next extent.
    - we get the current the current block address and current length using shift operations over ip->addr[i]
    - if block number is greater than the current extent length , we try to allocate, if it is not we simply return the extent block_address + block number + 1;
        - we allocate a new block , and increase the current extent size.
        - if we could not allocate a consecutive block , we mark the extent as finished and we change to the next one.
        - if the current extent is not created, create it.

**Proof our extent based fille system works correctly.**

1. To do this we created a program test_extent.c that you can write and does the following things:
    - Creates a file test_extent.txt using the O_EXTENT flag and writes 300 blocks to it (This will demonstrate that after finishing 1 extent we go to the next one correctly)
    - Create a second file named extent2 using normal direct pointers and writes 10 blocks to this (The purpose of this is so our previous file: test_extent.txt cannot allocate consecutive anymore)
    - We open test_extent.txt call lseek to the end of file , and write 300 blocks to it. (This shows , how we are changing extents when we could not allocate consecutive and still work)
    - We print information for test_extent , printing its extents, please check screnshots for results.
    - In the results we can see each extent block address and length are correct.
2. We created the program stat.c that prints information about the file and its pointers, to use it call `stat test_extent.txt` 

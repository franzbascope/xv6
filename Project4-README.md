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

I created the program test_lseek to prove its working correctly, for more information and screenshots check the folder project4/lseek

### Part 2 adding support for symbolic links

We implemented symbolic links by:

1. Creating a sys_symlink system call , here we create an inode and write the target path in its data.
2. We modified the open system call to be able to follow symlinks and do this recursiverly for 10 times before returning an error result.
3. We added a flag NO_FOLLOW in the case we want to see the content of the symlink itself
4. All this functionalities are executed and tested in program test_symlink.c , we added screenshots in project4/symbolic_links


# Project 4

## Group members

- Franz Bascope Jordan (U07511108)
- Abdullah Al Monsur (U85640940)

### lseek implementation

I implemented lseek by:

1. Use argdfd to fetch the struct file
2. Lock the inode.
3. Increment the file offset by the given parameter.
4. Unllock the inode.

I created the program test_lseek to prove its working correctly, for more information and screenshots check the folder project4/lseek


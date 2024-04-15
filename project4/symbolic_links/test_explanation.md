In this test we do the following steps:
1. Create a file at test_folder/file.txt with content: Hello, World!
2. Create symlink "symbolic_link" that targets "test_folder/file.txt"
3. We read symlink and verify it shows the content from "test_folder/file.txt"
4. 
    - We create a hard link symbolic_link2 that points to symbolic_link,
    - We open the file with the O_NOFOLLOW flag to get the actual symlink content.
    - We print the result and it shows the target path , which proves the NOFOLLOW flag is working
    - This also proves that symbolic_link was used and not its target, by this not affecting the behavior of the link call.
5. We unlink symbolic_link, and check if test_folder/file.txt still exists,this proves that the unlink sys call does not follow the sym link.

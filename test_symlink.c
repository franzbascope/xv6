#include "types.h"
#include "user.h"
#include "fcntl.h"
int main()
{
    // create directory
    mkdir("/test_folder");

    // create target file
    int fd = open("/test_folder/file.txt", O_CREATE | O_RDWR);
    write(fd, "Hello, World!\0", 14);
    close(fd);

    // read file test_folder/file.txt and print its content
    fd = open("/test_folder/file.txt", O_RDONLY);
    char buffer[512];
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf(1, "1. Created file at /test_folder/file.txt\n");
    printf(1, "/test_folder/file.tx content: %s\n", buffer);
    printf(1, "-------------- \n");

    // create symbolic link
    const char *target = "/test_folder/file.txt";
    const char *linkpath = "/symbolic_link";
    symlink(target, linkpath);
    // open symbolic link
    int linkfd = open(linkpath, O_RDONLY);
    // read symbolic link
    char linkbuffer[512];
    int linkn = read(linkfd, linkbuffer, sizeof(linkbuffer));
    linkbuffer[linkn] = '\0';
    printf(1, "2. Created symbolic link at /symbolic_link pointing to /test_folder/file.txt\n");
    printf(1, "/symbolic_link content: %s\n", linkbuffer);
    // compare buffer with link buffer
    if (strcmp(buffer, linkbuffer) == 0)
    {
        printf(1, "Content of /test_folder/file.txt and /symbolic_link are the same\n");
    }
    else
    {
        printf(1, "Content of /test_folder/file.txt and /symbolic_link are different\n");
    }
    printf(1, "-------------- \n");
    char hard_link_buffer[512];
    printf(1, "3. Creating hard link for symbolic link\n");
    link("/symbolic_link", "/symbolic_link2");
    fd = open("symbolic_link2", O_NOFOLLOW | O_RDONLY);
    n = read(fd, hard_link_buffer, sizeof(hard_link_buffer));
    hard_link_buffer[n] = '\0';
    close(fd);
    printf(1, "/symbolic_link2 O_NOFOLLOW content =  %s\n", hard_link_buffer);
    if (strcmp(target, hard_link_buffer) == 0)
    {
        printf(1, "Hard link created successfully without following symlink \n");
    }
    printf(1, "-------------- \n");
    // Delete symbolic link
    printf(1, "4. Deleting symbolic link\n");
    unlink(linkpath);
    // verify /test_folder/file.txt still exists
    fd = open("/test_folder/file.txt", O_RDONLY);
    if (fd > 0)
    {
        printf(1, "Symbolic link deletion did not delete the target file\n");
    }

    exit();
}

#include "types.h"
#include "user.h"
#include "fcntl.h"
int main()
{
    // create directory
    mkdir("/test_folder");

    // create target file
    int fd = open("/test_folder/file.txt", O_CREATE | O_RDWR);
    write(fd, "Hello, World!", 14);
    close(fd);

    // read file test_folder/file.txt and print its content
    fd = open("/test_folder/file.txt", O_RDONLY);
    char buffer[512];
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf(1, "File content: %s\n", buffer);

    // create symbolic link
    const char *target = "/test_folder/file.txt";
    const char *linkpath = "/symbolic_link";
    int result = symlink(target, linkpath);
    printf(1, "Process %d\n", result);
    exit();
}

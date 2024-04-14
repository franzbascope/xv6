#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  int fd;
  char buffer[512];

  // Open a new file for writing
  fd = open("testfile", O_CREATE | O_RDWR);
  if (fd < 0)
  {
    printf(1, "Failed to create file\n");
    exit();
  }

  // Write some content to the file
  if (write(fd, "Hello, World!\n", 14) != 14)
  {
    printf(1, "Write error\n");
    exit();
  }

  // Close and reopen the file for reading
  close(fd);
  fd = open("testfile", O_RDONLY);
  custom_lseek(fd, 4);
  if (fd < 0)
  {
    printf(1, "Failed to open file\n");
    exit();
  }

  // Read the content of the file
  int n = read(fd, buffer, sizeof(buffer));
  if (n < 0)
  {
    printf(1, "Read error\n");
    exit();
  }

  // Print the content of the file
  printf(1, "%s", buffer);

  // Close the file
  close(fd);

  exit();
}
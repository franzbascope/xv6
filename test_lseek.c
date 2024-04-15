#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  int fd;
  char buffer[512];

  // Open a new file for writing
  printf(1, "Opening file testfile\n");
  fd = open("testfile", O_CREATE | O_RDWR);
  if (fd < 0)
  {
    printf(1, "Failed to create file\n");
    exit();
  }

  // Write some content to the file
  printf(1, "Writing 'Hello, World!' to file\n");

  if (write(fd, "Hello, World!", 14) != 14)
  {
    printf(1, "Write error\n");
    exit();
  }

  // Close and reopen the file for reading
  close(fd);
  printf(1, "Open test file to read\n");
  fd = open("testfile", O_RDONLY);
  printf(1, "Calling lseek with value: %d\n", 4);
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
  // Null-terminate the buffer to treat it as a string
  buffer[n] = '\0';
  char *expectedResult = "o, World!";
  printf(1, "Should print:  '%s'\n", expectedResult);
  // Print the content of the file
  printf(1, "Actual result:  '%s'\n", buffer);
  // compare buffer with expected result
  if (strcmp(buffer, expectedResult) == 0)
  {
    printf(1, "File content matches the string\n");
  }
  else
  {
    printf(1, "File content does not match the string\n");
  }

  // Close the file
  close(fd);

  exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BLOCK_SIZE 512
#define NUM_BLOCKS 32910

int main(int argc, char *argv[])
{
  int i;
  int fd;

  // Open the file for writing
  fd = open("output.txt", O_CREATE | O_RDWR);
  if (fd < 0)
  {
    printf(1, "Error opening file\n");
    exit();
  }
  printf(1, "Writing %d blocks to file\n", NUM_BLOCKS);
  // Write 16,523 blocks to the file
  for (i = 0; i < NUM_BLOCKS; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'A', BLOCK_SIZE);
    int write_return = write(fd, buffer, BLOCK_SIZE);
    if (write_return != BLOCK_SIZE)
    {
      printf(1, "Error writing to file, write return: %d\n", write_return);
      close(fd);
      exit();
    }
  }

  // Close the file
  close(fd);
  // chech the file size of output.txt and print it
  struct stat st;
  if (stat("output.txt", &st) < 0)
  {
    printf(1, "Error stating file\n");
    exit();
  }
  printf(1, "File size: %d\n", st.size);

  exit();
}

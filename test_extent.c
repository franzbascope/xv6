#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BLOCK_SIZE 512
#define NUM_BLOCKS 10

int main(int argc, char *argv[])
{
  int i;
  int fd;

  printf(1, "Writing %d blocks to file extent using O_EXTENT\n", NUM_BLOCKS);
  fd = open("extent", O_CREATE | O_EXTENT | O_RDWR);
  for (i = 0; i < NUM_BLOCKS; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'A', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);

  fd = open("extent2", O_CREATE | O_RDWR);
  printf(1, "Create file extent2 and write blocks to it\n");
  for (i = 0; i < 10; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'B', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);

  printf(1, "Appending a message to file extent original\n");
  fd = open("extent", O_RDWR);
  printf(1, "Called lseek with value %d\n", NUM_BLOCKS * BLOCK_SIZE);
  custom_lseek(fd, NUM_BLOCKS * BLOCK_SIZE);
  for (i = 0; i < NUM_BLOCKS; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'C', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);

  // chech the file size of output.txt and print it
  struct stat st;
  if (stat("extent", &st) < 0)
  {
    printf(1, "Error stating file\n");
    exit();
  }
  printf(1, "File size: %d\n", st.size);

  exit();
}

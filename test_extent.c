#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
  int i;
  int fd;
  uint first_block_write = 300;
  char* fileName = "test_extent.txt";
  printf(1, "Writing %d blocks with character A to file %s using O_EXTENT\n", first_block_write, fileName);
  fd = open(fileName, O_CREATE | O_EXTENT | O_RDWR);
  for (i = 0; i < first_block_write; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'A', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);

  uint second_block_write = 10; 
  fd = open("extent2", O_CREATE | O_RDWR);
  printf(1, "Create file extent2 using direct pointers and writing %d blocks with `B`\n",second_block_write);
  for (i = 0; i < second_block_write; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'B', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);



  uint third_block_write = 300;
  fd = open(fileName, O_RDWR);
  printf(1, "Called lseek with value %d\n", first_block_write * BLOCK_SIZE);
  custom_lseek(fd, first_block_write * BLOCK_SIZE);
  printf(1, "Appending %d blocks to original file %s\n",third_block_write, fileName);
  for (i = 0; i < third_block_write; i++)
  {
    char buffer[BLOCK_SIZE];
    memset(buffer, 'C', BLOCK_SIZE);
    write(fd, buffer, BLOCK_SIZE);
  }
  close(fd);

  // chech the file size of output.txt and print it
  struct stat st;
  if (stat(fileName, &st) < 0)
  {
    printf(1, "Error stating file\n");
    exit();
  }
  printf(1, "Printing information about file: %s\n", fileName);
  printf(1, "File size: %d\n", st.size);
  printf(1, "File type: %d\n", st.type);
  uint nxextent = 6;
  for (i = 0; i < nxextent; i++)
  {
    uint extent_length = st.addrs[i] & 0xFF;      // get the last byte
    uint block_address = st.addrs[i] >> 8;        // get the first three bytes
    printf(1, "Extent %d: block address: %d, extent length: %d\n", i, block_address, extent_length);
  }

  exit();
}

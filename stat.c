#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

void runStat(const char *fileName)
{
  struct stat st;
  if (stat(fileName, &st) < 0)
  {
    printf(1, "Error stating file\n");
    exit();
  }
  printf(1, "Printing information about %s file\n", fileName);
  printf(1, "File size: %d\n", st.size);
  printf(1, "File type: %d\n", st.type);
  if (st.type == T_EXTENT)
  {
    printf(1, "Printing information about file extents\n");
    uint nxextent = 6;
    for (int i = 0; i < nxextent; i++)
    {
      uint extent_length = st.addrs[i] & 0xFF; // get the last byte
      uint extent_position = st.addrs[i] >> 8; // get the first 3 bytes
      printf(1, "Extent %d: position %d, length %d\n", i, extent_position, extent_length);
    }
  }
  else
  {
    printf(1, "File is a normal direct pointer file\n");
    printf(1, "Printing direct pointers\n");
    for (int i = 0; i < 12; i++)
    {
      printf(1, "Direct pointer %d: %d\n", i, st.addrs[i]);
    }
  }
}

int main(int argc, char *argv[])
{
  int i;

  if (argc <= 1)
  {
    exit();
  }

  for (i = 1; i < argc; i++)
  {
    runStat(argv[i]);
  }
  exit();
}

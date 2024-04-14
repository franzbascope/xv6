#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
test_lseek(int fd)
{
  // print fd
    printf(1, "fd: %d\n", fd);
    custom_lseek(fd, 0);
}

int
main(int argc, char *argv[])
{
  int fd, i;

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    test_lseek(fd);
    close(fd);
  }
  exit();
}

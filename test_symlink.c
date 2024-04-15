#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    const char *target = "/path/to/target/file";
    const char *linkpath = "/path/to/link";
    int result = symlink(target, linkpath);
    printf(1, "Process %d\n", result);
    exit();
}

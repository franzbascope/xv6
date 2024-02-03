#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int
main(int argc, char *argv[])
{
    int time;

    if (argc < 2)
    {
        printf(1, "Error. Include a time!\n");
    }
    else
    {
        time = atoi(argv[1]);
        sleep(time);
    }
    exit();
}

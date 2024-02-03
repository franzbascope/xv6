#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
 
int
find(char *folder, char *name, int tFlag, int iFlag, int pFlag, int f, int in){
    int fd;
    char buf[512];
    struct stat st;
    struct dirent de;

    printf(1,"%s\n",folder);
    printf(1,"%s\n",name);


    if((fd = open(folder, 0)) < 0){
        printf(2, "cannot open %s\n", folder);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf(2, "cannot stat %s\n", folder);
        close(fd);
        return;
    }

    if (st.type == T_DIR)
    {
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(stat(buf, &st) < 0)
            {
                printf(1, "ls: cannot stat %s\n", buf);
                continue;
            }
            switch (st.type)
            {
            case T_FILE:
                printf(1, "%s\n", buf);
                break;
            case T_DIR:
                printf(1, "%s\n", buf);
                break;
            }
        }
    }
    
}

int 
main(int argc, char *argv[]) {
    char folder[512];
    char name[512];
    int tFlag = 0;
    int iFlag = 0;
    int pFlag = 0;
    int f = 0;
    int in = 0;

    strcpy(folder, argv[1]);
    strcpy(name, argv[3]);

    if (strcmp(argv[2], "-name"))
    {
        if (strcmp(argv[4], "-type") == 0)
        {
            tFlag = 1;
            int f = open(argv[5], 0);
        }
        else if (strcmp(argv[4], "-inum") == 0)
        {
            iFlag = 1;
            int in = open(argv[5], 0);
        }
        else if (strcmp(argv[4], "-printi") == 0)
        {
            pFlag = 1;
        }
    }
    
    find(folder, name, tFlag, iFlag, pFlag, f, in);

    exit();
 }
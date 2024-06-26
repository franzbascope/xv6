#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

/*Function to format a string
Pulled from ls.c*/
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return name, ended with a null character
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
  return buf;
}

/*Function to recursively search for the required file
Pulled from ls.c excepted from the last part
The last part checks if the current object is a folder or a file
if it is a file, checks if it is the one we are lookign for
if it is a folder it opens the next level off search*/
void
auxiliar(char *path, char *buf, int size_of_buf, int fd, struct stat st, char *name, int tFlag, int iFlag, int pFlag, char *t, int in)
{
    if (tFlag == 1)
    {
        if (strcmp(t,"-f")==0)
        {
            char *p;
            struct dirent de;
            struct stat stbelow;

            if(strlen(path) + 1 + DIRSIZ + 1 > size_of_buf)
            {
                printf(1,"ls: path too long\n");
                return;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de))
            {
                if(de.inum == 0)
                continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) < 0){
                printf(1,"ls: cannot stat %s\n", buf);
                continue;
                }
                if (st.type == T_DIR) {
                    //Check to see if the folder is not the current or parent
                if (strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) 
                {
                    int fdbelow = open(buf, 0);
                    if(fstat(fd, &stbelow) < 0){
                    printf(1, "ls: cannot stat %s\n", path);
                    close(fd);
                    return;
                    }
                    // Recursive call to search for the file in a new level
                    auxiliar(buf, buf, size_of_buf, fdbelow, stbelow, name, tFlag, iFlag, pFlag, t, in);
                    close(fdbelow);
                }
                } 
                else if (st.type == T_FILE) 
                {
                    if (strcmp(fmtname(buf), name) == 0) 
                    {
                        printf(1,"%s\n", buf);
                    }
                }
            }
        }
        else if (strcmp(t, "-d"))
        {
            char *p;
            struct dirent de;
            struct stat stbelow;

            if(strlen(path) + 1 + DIRSIZ + 1 > size_of_buf)
            {
                printf(1,"ls: path too long\n");
                return;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de))
            {
                if(de.inum == 0)
                continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) < 0)
                {
                printf(1,"ls: cannot stat %s\n", buf);
                continue;
                }
                if (st.type == T_DIR) 
                {
                    if (strcmp(fmtname(buf), name) == 0)
                    {
                        printf(1,"%s\n", buf);
                    }
                    
                    //Check to see if the folder is not the current or parent
                    if (strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) 
                    {
                        int fdbelow = open(buf, 0);
                        if(fstat(fd, &stbelow) < 0){
                        printf(1, "ls: cannot stat %s\n", path);
                        close(fd);
                        return;
                        }
                        // Recursive call to search for the file in a new level
                        auxiliar(buf, buf, size_of_buf, fdbelow, stbelow, name, tFlag, iFlag, pFlag, t, in);
                        close(fdbelow);
                    }
                }
            }
            
            
        }
    }
    else if (iFlag == 1)
    {
        char *p;
        struct dirent de;
        struct stat stbelow;

        if(strlen(path) + 1 + DIRSIZ + 1 > size_of_buf)
        {
            printf(1,"ls: path too long\n");
            return;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
            continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
            printf(1,"ls: cannot stat %s\n", buf);
            continue;
            }
            if (st.type == T_DIR) {
                //Check to see if the folder is not the current or parent
                if (strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) 
                {
                    int fdbelow = open(buf, 0);
                    if(fstat(fd, &stbelow) < 0){
                    printf(1, "ls: cannot stat %s\n", path);
                    close(fd);
                    return;
                    }
                    // Recursive call to search for the file in a new level
                    auxiliar(buf, buf, size_of_buf, fdbelow, stbelow, name, tFlag, iFlag, pFlag, t, in);
                    close(fdbelow);
                }
            } 
            else if (st.type == T_FILE) 
            {
                if (strcmp(fmtname(buf), name) == 0 && st.ino == in) 
                {
                    printf(1,"%s\n", buf);
                }
            }
        }
    }
    else if (pFlag == 1)
    {
        char *p;
        struct dirent de;
        struct stat stbelow;

        if(strlen(path) + 1 + DIRSIZ + 1 > size_of_buf)
        {
            printf(1,"ls: path too long\n");
            return;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
            continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
            printf(1,"ls: cannot stat %s\n", buf);
            continue;
            }
            if (st.type == T_DIR) {
                //Check to see if the folder is not the current or parent
                if (strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) 
                {
                    int fdbelow = open(buf, 0);
                    if(fstat(fd, &stbelow) < 0){
                    printf(1, "ls: cannot stat %s\n", path);
                    close(fd);
                    return;
                    }
                    // Recursive call to search for the file in a new level
                    auxiliar(buf, buf, size_of_buf, fdbelow, stbelow, name, tFlag, iFlag, pFlag, t, in);
                    close(fdbelow);
                }
            } 
            else if (st.type == T_FILE) 
            {
                if (strcmp(fmtname(buf), name) == 0) 
                {
                    printf(1,"%d    %s\n", st.ino, buf);
                }
            }
        }
    }
    else
    {
        char *p;
        struct dirent de;
        struct stat stbelow;

        if(strlen(path) + 1 + DIRSIZ + 1 > size_of_buf)
        {
            printf(1,"ls: path too long\n");
            return;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
            continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
            printf(1,"ls: cannot stat %s\n", buf);
            continue;
            }
            if (st.type == T_DIR) {
                //Check to see if the folder is not the current or parent
                if (strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) 
                {
                    int fdbelow = open(buf, 0);
                    if(fstat(fd, &stbelow) < 0){
                    printf(1, "ls: cannot stat %s\n", path);
                    close(fd);
                    return;
                    }
                    // Recursive call to search for the file in a new level
                    auxiliar(buf, buf, size_of_buf, fdbelow, stbelow, name, tFlag, iFlag, pFlag, t, in);
                    close(fdbelow);
                }
            } 
            else if (st.type == T_FILE) 
            {
                if (strcmp(fmtname(buf), name) == 0) 
                {
                    printf(1,"%s\n", buf);
                }
            }
        }
    }
}

void
find(char *folder, char *name, int tFlag, int iFlag, int pFlag, char *t, int in)
{
  char buf[512];
  int fd;
  struct stat st;

  if((fd = open(folder, 0)) < 0){
    printf(2, "ls: cannot open %s\n", folder);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", folder);
    close(fd);
    return;
  }

  switch(st.type)
  {
    case T_DIR:
        auxiliar(folder, buf, sizeof(buf), fd, st, name, tFlag, iFlag, pFlag, t, in);
        
  }
  close(fd);
}

/*Main Function, calls the find with required arguments
folder to start
file to search
flags for functionality (Still need implementation)*/
int
main(int argc, char *argv[])
{
    int tFlag = 0;
    int iFlag = 0;
    int pFlag = 0;
    char t[10];
    int in = 0;

    if (argc == 4)
    {
        find(argv[1], argv[3], tFlag, iFlag, pFlag, t, in);
    }
    else if (argc > 4)
    {
        if (strcmp(argv[4], "-type") == 0)
        {
            tFlag = 1;
            strcpy(t,argv[5]);
            find(argv[1], argv[3], tFlag, iFlag, pFlag, t, in);
        }
        else if (strcmp(argv[4], "-inum") == 0)
        {
            iFlag = 1;
            in = atoi(argv[5]);
            find(argv[1], argv[3], tFlag, iFlag, pFlag, t, in);
        }
        else if (strcmp(argv[4], "-printi") == 0)
        {
            pFlag = 1;
            find(argv[1], argv[3], tFlag, iFlag, pFlag, t, in);
        }
    }
    exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"

char buf1[512];
char buf2[512];

int
uniq(int fd, int cFlag, int uFlag, int wFlag, int width){
    int n;
    int lines = 0;
    int count = 0;
    int equal;
    int prev_equal = 0;
    int counter;
    int size = 0;
    int stop = 0;
    char curr[512];
    char next[512];
    int occ=1;

    while ((n = read(fd, buf1, sizeof(buf1))) > 0)
    {
        for (int k = 0; buf1[k] != '\0'; k++)
        {
            if (buf1[k] == '\n')
            {
                lines++;
            }
            
        }
        if (cFlag==1)
        {  
            for (int l = 0; l < lines-1; l++)
            {
                for (int i = 0; buf1[i+size] != '\n'; i++)
                {
                    if (buf1[i+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    
                    curr[i] = buf1[i+size];
                    count++;
                }

                if (stop == 1)
                {
                    break;
                }
                

                count++;
                size = count;

                for (int j = 0; buf1[j+size] != '\n'; j++)
                {
                    if (buf1[j+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    next[j] = buf1[j+size];
                }
                
                counter = 0;
                equal = 0;
                for (int l = 0;  curr[l] != '\0'; l++)
                {
                    counter++;
                    if (curr[l] == next[l])
                    {
                        equal++;
                    }
                }

                if (counter == equal)
                {
                    occ+=1; //incrementing occurances
                }
                else
                {
                    printf(1, "(%d) %s\n", occ, curr);
                    occ=1;
                }               
            }
            printf(1, "(%d) %s\n", occ, next);
        }
        else if(uFlag==1)
        {
	    printf(1, "uflag on");
        int occ=0;
            for (int l = 0; l < lines-1; l++)
            {
                
                for (int i = 0; buf1[i+size] != '\n'; i++)
                {
                    if (buf1[i+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    
                    curr[i] = buf1[i+size];
                    count++;
                }

                if (stop == 1)
                {
                    break;
                }
                

                count++;
                size = count;
                for (int l1=l+1; lines; l1++)
                {
                    stop=0;
                    for (int j = 0; buf1[j+size] != '\n'; j++)
                    {
                        if (buf1[j+size] == '\0')
                        {
                            stop = 1;
                            break;
                        }
                        next[j] = buf1[j+size];
                    }
                    if (stop == 1)
                    {
                        continue;
                    }
                    counter = 0;
                    equal = 0;
                    for (int l = 0;  curr[l] != '\0'; l++)
                    {
                        counter++;
                        if (curr[l] == next[l])
                        {
                            equal++;
                        }
                    }

                    if (counter == equal)
                    {
                        occ++;
                    }
                } 
		        if (occ<1)
		        {
		            printf(1, "%s\n", curr);
		        }
		        occ=0;
            }
        }
        else if(wFlag==1)
        {
            for (int l = 0; l < lines-1; l++)
            {
                for (int i = 0; buf1[i+size] != '\n'; i++)
                {
                    if (buf1[i+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    
                    curr[i] = buf1[i+size];
                    count++;
                }

                if (stop == 1)
                {
                    break;
                }
                

                count++;
                size = count;

                for (int j = 0; buf1[j+size] != '\n'; j++)
                {
                    if (buf1[j+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    next[j] = buf1[j+size];
                }
                
                counter = 0;
                equal = 0;
                for (int l = 0;  curr[l] != '\0'; l++)
                {
                    counter++;
                    if (curr[l] == next[l])
                    {
                        equal++;
                    }
                }

                if (equal>=width)
                {
                    if (prev_equal != 1)
                    {
                        printf(1, "%s\n", next);    
                    }
                    prev_equal = 1;
                }
                else
                {
                    if (prev_equal != 1)
                    {
                        printf(1, "%s\n", curr);
                        printf(1, "%s\n", next);
                    }
                    
                    prev_equal = 0;
                }

                
            }
        }
        else
        {
            for (int l = 0; l < lines-1; l++)
            {
                for (int i = 0; buf1[i+size] != '\n'; i++)
                {
                    if (buf1[i+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    
                    curr[i] = buf1[i+size];
                    count++;
                }

                if (stop == 1)
                {
                    break;
                }
                

                count++;
                size = count;

                for (int j = 0; buf1[j+size] != '\n'; j++)
                {
                    if (buf1[j+size] == '\0')
                    {
                        stop = 1;
                        break;
                    }
                    next[j] = buf1[j+size];
                }
                
                counter = 0;
                equal = 0;
                for (int l = 0;  curr[l] != '\0'; l++)
                {
                    counter++;
                    if (curr[l] == next[l])
                    {
                        equal++;
                    }
                }

                if (counter == equal)
                {
                    if (prev_equal != 1)
                    {
                        printf(1, "%s\n", next);    
                    }
                    prev_equal = 1;
                }
                else
                {
                    if (prev_equal != 1)
                    {
                        printf(1, "%s\n", curr);
                        printf(1, "%s\n", next);
                    }
                    
                    prev_equal = 0;
                }

                
            }
        }
        
    }
    
    return 0;
}

int 
main(int argc, char *argv[]) 
{
    int cFlag = 0;
    int uFlag = 0;
    int wFlag = 0;
    int width = 0;

    if (strcmp(argv[1], "-c") == 0)
    {
        cFlag = 1;
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        uFlag = 1;
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        wFlag = 1;
        width = atoi(argv[2]);
    }
    
    if (argc == 2)
    {
        int fd = open(argv[1], 0);
        uniq(fd, cFlag, uFlag, wFlag, width);
    }
    
    if (wFlag == 0)
    {
        int fd = open(argv[2], 0);
        uniq(fd, cFlag, uFlag, wFlag, width);
    }
    else
    {
        int fd = open(argv[3], 0);
        uniq(fd, cFlag, uFlag, wFlag, width);
        close(fd);
    }
    
    

    exit();
}

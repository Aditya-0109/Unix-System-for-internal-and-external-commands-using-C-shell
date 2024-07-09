#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int LsSer(char const *arg, char const *sneak, char const *peek)
{
    struct dirent *dir;
    int snk = 0;
    int lir = 0;
    if (sneak)
    {
        if (!strcmp("-a", sneak))
            snk = 1;
        else if (!strcmp("-1", sneak))
            lir = 1;
        else
        {
            printf("clackalack: invalid option\nuse either -a or -1\n");
            return -1;
        }
        if (peek)
        {
            if (!strcmp("-a", peek))
                snk = 1;
            else if (!strcmp("-1", peek))
                lir = 1;
            else
            {
                printf("clackalack: invalid option\nuse either -a or -1\n");
                return -1;
            }
        }
    }
    DIR *here = opendir(arg);
    if (!here)
    {
        perror("clacklack");
        return -1;
    }
    dir = readdir(here);
    if (here)
    {
        if (snk)
            while (dir)
            {
                printf("%s", dir->d_name);
                dir = readdir(here);
                if (lir)
                    printf("\n");
                else
                    printf("\t");
            }
        else
            while (dir)
            {
                if ((dir->d_name)[0] != '.')
                {
                    printf("%s", dir->d_name);
                    if (lir)
                        printf("\n");
                    else
                        printf("\t");
                }
                dir = readdir(here);
            }
    }
    closedir(here);
    if (!lir)
        printf("\n");

    return 0;
}

int main(int argc, char const *argv[])
{
    LsSer(argv[1], argv[2], argv[3]);
}
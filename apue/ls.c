#include "apue.h"
#include <dirent.h>

int
main(int argc, char *argv[])
{
    DIR             *dp;
    struct dirent   *dirp;

    if (argc != 2)
        err_quit("usage: ls directory_name");

    if ((dp = opendir(argv[1])) == NULL)
        err_sys("car`t open %s", argv[1]);

    while ((dirp = readdir(dp)) != NULL)
        printf ("%s  %d\n", dirp->d_name, dirp->d_type);

    closedir(dp);

    exit(0);
}
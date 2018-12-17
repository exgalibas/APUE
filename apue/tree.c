#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "apue.h"

#define DEPTH 2   // 默认的深度

int tree(char *);

unsigned static maxDepth;  // 真实深度

int
main(int argc, char *argv[])
{
    char * file;
    if (argc < 2) {
        err_quit("usage: tree directory_name");
    } else if (argc == 2) {
        file = argv[1];
        maxDepth = DEPTH;
    } else {
        file = argv[2];
        maxDepth = (unsigned) atoi(argv[1]);
    }

    tree(file);
}

int
tree(char *dir)
{
    static int depth = 0;
    char *tempDir;  //备份路径
    size_t length;

    // 已达到层次
    if (depth >= maxDepth) {
        return 0;
    }

    DIR             *dp;
    struct dirent   *dirp;

    if ((dp = opendir(dir)) == NULL)
        err_sys("car`t open %s", *dir);

    length = strlen(dir) + 1;
    tempDir = (char *) malloc(length);
    memcpy(tempDir, dir, length);

    while ((dirp = readdir(dp)) != NULL) {

        // 打印结构
        for (int i = 0; i < depth; i++) {
            printf("|");
            printf("    ");
        }
        printf ("|--- %s\n", dirp->d_name);
        if (dirp->d_type == DT_DIR &&
            strcmp(dirp->d_name, ".") != 0 &&
            strcmp(dirp->d_name, "..")) {
            depth++;
            strcat(dir, "/");
            strcat(dir, dirp->d_name);
            tree(dir);
            memcpy(dir, tempDir, length);
            depth--;
        }
    }

    free(tempDir);
    closedir(dp);
    return 0;
}
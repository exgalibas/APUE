#include <fcntl.h>
#include <stdbool.h>
#include "apue.h"
#define NUM 10

long tail(char *, long);

int
main(int argc, char* argv[])
{
    bool follow;
    char * file;
    long seek = 0;

    if (argc < 2) {
        err_quit("usage: tail n/-f file_name");
    }

    if (argc == 3) {
        follow = strcmp(argv[1], "-f") == 0 ? true : false;
        file = argv[2];
    } else {
        follow = false;
        file = argv[1];
    }

    while(true) {
        seek = tail(file, seek);
        if (follow == false) {
            break;
        }
        sleep(1);
    }

    return 0;
}

long
tail(char *file, long seek)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        err_sys("car`t open %s", *file);
    }

    char buf[1024];
    long pos = -1;
    int count = 0;
    int ch;

    while (count <= NUM) {

        fseek(fp, pos, SEEK_END);
        if (ftell(fp) < (SEEK_SET+seek)) {
           // fseek(fp, seek, SEEK_SET);
            return seek;
        } else if (ftell(fp) == (SEEK_SET+seek)) {
            break;
        }

        pos -= 1;
        ch = fgetc(fp);
        if (ch == '\n') {
            count += 1;
        }
    }

    while (feof(fp) != 1) {
        fread(buf, sizeof(char), 1024, fp);
        printf("%s",buf);
        fflush(fp);
    }

    pos = ftell(fp);
    fclose(fp);
    return pos;
}
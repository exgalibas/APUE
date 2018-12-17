#include <sys/types.h>
#include <signal.h>
#include "apue.h"

int
main(int argc, char *argv[]) {
    int sig = SIGTERM; // 平滑杀死

    argc--;
    argv++;

    if (argc == 0) {
        err_quit("usage: kill -n pid");
    }else if (argc >= 2 && argv[0][0] == '-') {
        sig = atoi(argv[0] + 1);
        argc--;
        argv++;
    }

    while (argc > 0) {
        int pid = atoi(argv[0]);
        int err = kill(pid, sig);
        if (err < 0) {
            err_sys("car`t kill -%d %d", sig, pid);
        }

        argc--;
        argv++;
    }

    return 0;
}
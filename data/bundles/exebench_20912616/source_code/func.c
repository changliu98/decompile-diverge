#include <dirent.h>

#include <errno.h>

#include <math.h>

#include <signal.h>

#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

static inline int dupfd(int from, int *to) {
    if (from == -1) {
        *to = -1;
        return 1;
    } else {
        *to = dup(from);
        return (*to != -1);
    }
}

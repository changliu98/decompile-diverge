#include <assert.h>

#include <dirent.h>

#include <errno.h>

#include <limits.h>

#include <stdarg.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/stat.h>

#include <unistd.h>

int substitute(char *data, char from, char to)
{
    char *c = NULL;

    c = data;
    while((c = strchr(c, from)) != NULL) {
        *(c++) = to;
    }

    return 1;
}

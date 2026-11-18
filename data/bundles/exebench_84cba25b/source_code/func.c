#include <stdio.h>

#include <errno.h>

#include <unistd.h>

#include <stdlib.h>

#include <stdarg.h>

#include <signal.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

char *base91(char *p, int i)
{
        *p++ = (i/91) + 33;
        *p++ = i % 91 + 33;

        return p;
}

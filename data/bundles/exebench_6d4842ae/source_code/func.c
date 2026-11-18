#include <stdio.h>

#include <signal.h>

#include <sys/types.h>

void
load_and_store(unsigned long *p, unsigned long val)
{
    *p += val;
}

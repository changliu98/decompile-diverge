#include <stdio.h>

#include <time.h>

#include <errno.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/times.h>

#include <sys/utsname.h>

#include <string.h>

void c_sysconf_(int *name, int *val, int *err){
    *val = sysconf(*name);
    *err = errno;
}

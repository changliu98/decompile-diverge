#include <errno.h>

#include <stdlib.h>

#include <sys/resource.h>

#include <unistd.h>

int get_priority(long pid, int *priority)
{
    *priority = getpriority(PRIO_PROCESS, pid);
    return errno;
}

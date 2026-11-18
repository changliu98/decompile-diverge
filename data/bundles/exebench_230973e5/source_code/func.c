#include <stdarg.h>

#include <sys/socket.h>

#include <stdio.h>

#include <unistd.h>

#include <syslog.h>

#include <time.h>

#include <signal.h>

#include <string.h>

#include <pthread.h>

#include <errno.h>

#include <fcntl.h>

static inline void a_store(volatile int *p, int x)
{
 __asm__( "movl %1, %0" : "=m"(*p) : "r"(x) : "memory" );
}

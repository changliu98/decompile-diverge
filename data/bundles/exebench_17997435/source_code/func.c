#include <unistd.h>

#include <assert.h>

#include <pthread.h>

#include <stdlib.h>

#include <stdio.h>

#include <signal.h>

#include <sys/errno.h>

#include <sched.h>

#include <linux/sched.h>

#include <sys/mman.h>

#include <string.h>

#include <malloc.h>

#include <sys/syscall.h>

static __inline__ int trylock (volatile int* lock) {
    char oldval;
    __asm__ __volatile__
        (
         "xchgb %b0,%1"
         :"=q" (oldval),
          "=m" (*lock)
         :"0" (1)
         : "memory");
    return oldval == 0;
}

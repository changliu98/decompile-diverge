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

static __inline__ void spin_unlock (volatile int* lock) {
 __asm__ __volatile__
        ("movb $0,%0"
         :"=m" (*lock) : : "memory");
}

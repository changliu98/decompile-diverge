#include <stdint.h>

static inline void a_inc(volatile int *p)
{
 __asm__ __volatile__(
  "lock ; incl %0"
  : "=m"(*p) : "m"(*p) : "memory" );
}

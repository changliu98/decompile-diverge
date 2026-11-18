#include <stdint.h>

static inline int a_swap(volatile int *p, int v)
{
 __asm__ __volatile__(
  "xchg %0, %1"
  : "=r"(v), "=m"(*p) : "0"(v) : "memory" );
 return v;
}

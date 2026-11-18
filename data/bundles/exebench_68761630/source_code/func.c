#include <stdint.h>

static inline void a_or(volatile int *p, int v)
{
 __asm__ __volatile__(
  "lock ; or %1, %0"
  : "=m"(*p) : "r"(v) : "memory" );
}

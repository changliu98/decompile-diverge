#include <stdint.h>

static inline void a_inc(volatile int *x)
{
 ++*x;
}

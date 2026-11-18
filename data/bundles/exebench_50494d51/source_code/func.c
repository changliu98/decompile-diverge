#include <stdint.h>

static inline void set_bit(int nr, volatile unsigned long *addr)
{
 *(addr + ((nr) / ((int)((sizeof(long) * 8))))) |= (1UL << ((nr) % ((int)((sizeof(long) * 8)))));
}

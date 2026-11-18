#include <stdint.h>

static inline void change_bit(int nr, volatile unsigned long *addr)
{
 *(addr + ((nr) / ((int)((sizeof(long) * 8))))) ^= (1UL << ((nr) % ((int)((sizeof(long) * 8)))));
}

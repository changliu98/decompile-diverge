#include <stdlib.h>

#include <string.h>

static inline void clear_bit(int nr, unsigned long *addr)
{
    ((addr))[(nr)/(sizeof(unsigned long) * 8)] &= ~(1UL << ((nr) % (sizeof(unsigned long) * 8)));
}

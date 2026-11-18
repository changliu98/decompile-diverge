#include <sys/types.h>

#include <stdint.h>

static inline int test_and_change_bit(long nr, volatile unsigned long *addr)
{
 do { char c; asm volatile ("" "btc" " %2, " "%0" "; set" "c" " %1" : "+m" (*addr), "=qm" (c) : "Ir" (nr) : "memory"); return c != 0; } while (0);
}

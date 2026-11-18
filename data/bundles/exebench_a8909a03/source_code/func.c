#include <linux/string.h>

static inline void put_user_quad(unsigned long val,long * addr)
{
 *addr = val;
}

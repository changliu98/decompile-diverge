#include <linux/string.h>

static inline void put_user_long(unsigned long val,int * addr)
{
 *addr = val;
}

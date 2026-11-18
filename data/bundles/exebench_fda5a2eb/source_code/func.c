#include <linux/string.h>

static inline void put_user_word(short val,short * addr)
{
 *addr = val;
}

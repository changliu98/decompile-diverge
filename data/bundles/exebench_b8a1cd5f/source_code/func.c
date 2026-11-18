#include <errno.h>

int atomic32_decrement(int *dest)
{
 int r;


 r = __sync_sub_and_fetch(dest, 1U);






 return r;

}

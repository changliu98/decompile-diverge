#include <math.h>               /* for sqrt(),log(),exp(),pow(),cos() */

static double HTS_rnd(unsigned long *next)
{
   double r;

   *next = *next * 1103515245L + 12345;
   r = (*next / 65536L) % 32768L;

   return (r / 32767);
}

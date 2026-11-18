#include <math.h>          /* maths functions */

#include <stdio.h>         /* for error messages. TBD: remove this */

#include <stdlib.h>        /* for malloc/free */

void splini(double *xa, double *ya, double *y2a, int n, double x, double *y)
{







 double yi = 0;
 int klo = 0;
 int khi = 1;
 double xx, h, a, b, a2, b2;
 while ((x > xa[klo]) && (khi < n))
 {
  xx = x;
  if (khi < (n - 1))
  {
   if (x < xa[khi])
    xx = x;
   else
    xx = xa[khi];
  }
  h = xa[khi] - xa[klo];
  a = (xa[khi] - xx) / h;
  b = (xx - xa[klo]) / h;
  a2 = a * a;
  b2 = b * b;
  yi += ((1.0 - a2) * ya[klo] / 2.0 + b2 * ya[khi] / 2.0
    + ((-(1.0 + a2 * a2) / 4.0 + a2 / 2.0) * y2a[klo]
      + (b2 * b2 / 4.0 - b2 / 2.0) * y2a[khi]) * h * h / 6.0) * h;
  klo++;
  khi++;
 }
 *y = yi;
}

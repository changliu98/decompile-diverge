#include <stdio.h>   /* for NULL */

#include <stdlib.h>  /* for malloc/free */

#include <string.h>  /* for memcpy */

#include <math.h>    /* for fabs and sqrt */

void GivensApply(double c, double s, double *z_1, double *z_2)
{
 double w;

 w = (*z_1)*c + (*z_2)*s;
 *z_2 = -(*z_1)*s + (*z_2)*c;
 *z_1 = w;
}

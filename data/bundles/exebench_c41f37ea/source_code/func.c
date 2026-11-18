#include <math.h>

#include <string.h> /* memcpy */

static
void MultMat(const double a[9],const double b[9],double c[9]) {
  int i,j;
  for (i=0;i<3;i++) {
    for (j=0;j<3;j++) {
      c[i*3+j] = a[i*3]*b[j] + a[i*3+1]*b[3+j] + a[i*3+2]*b[6+j];
    }
  }
}

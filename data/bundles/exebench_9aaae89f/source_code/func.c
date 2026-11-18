#include <math.h>

#include <stdlib.h>

void pick(int* np, int* nr) {




 ++(*nr);
 if (*nr >= 768) {
  ++(*np);
  *nr = 0;
 }
 if (*np >= 180) *np = 0;

}

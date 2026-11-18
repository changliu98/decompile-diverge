#include <string.h>

static void computesizes (int nums[], int ntotal, int *narray, int *nhash) {
  int i;
  int a = nums[0];
  int na = a;
  int n = (na == 0) ? -1 : 0;
  for (i = 1; a < *narray && *narray >= (1<<(i-1)); i++) {
    if (nums[i] > 0) {
      a += nums[i];
      if (a >= (1<<(i-1))) {
        n = i;
        na = a;
      }
    }
  }
  ;
  *nhash = ntotal - na;
  *narray = (n == -1) ? 0 : (1<<(n));
  ;
}



#include <math.h>

#include <assert.h>



int func0(int n) {
  if (n == 0) {
    return 1;
  }
  if ((n & (n + 1)) == 0) {
    return n;
  }
  int pos = (int)(log2((~n) & -(~n)) + 1);
  return ((1 << (pos - 1)) | n);
}

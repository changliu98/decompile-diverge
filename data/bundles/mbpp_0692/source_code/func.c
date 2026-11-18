

#include <assert.h>



int func0(int N) {
  if (N >= 10) {
    return 0;
  }
  int fac = 1;
  for (int i = 1; i <= N; i++) {
    fac = (fac * i) % 100;
  }
  return fac;
}

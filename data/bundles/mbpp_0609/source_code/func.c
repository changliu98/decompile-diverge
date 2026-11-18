

#include <assert.h>



int func0(int A, int B, int N) {
  int x = (B - 1 > N) ? B - 1 : N;
  return (A * x) / B;
}

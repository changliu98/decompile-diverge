

#include <assert.h>



int func0(int n, int r, int p) {
  if (r > n - r) r = n - r;
  int C[r + 1];
  for (int i = 0; i <= r; i++) C[i] = 0;
  C[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = (i < r ? i : r); j > 0; j--) {
      C[j] = (C[j] + C[j - 1]) % p;
    }
  }
  return C[r];
}

#include <assert.h>



int func0(int a[], int n, int m) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = (a[i] / m + (a[i] % m != 0));
  }
  int result = -1, maxx = -1;
  for (i = n - 1; i >= 0; i--) {
    if (maxx < a[i]) {
      maxx = a[i];
      result = i;
    }
  }
  return result + 1;
}

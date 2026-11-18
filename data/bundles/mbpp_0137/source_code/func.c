

#include <assert.h>

#include <math.h>



double func0(int nums[], int n) {
  int n1 = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] == 0) {
      n1++;
    }
  }
  double ratio = ((double)n1 / n);
  ratio = round(ratio * 100) / 100.0;
  return ratio;
}

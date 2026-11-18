#include <assert.h>

#include <math.h>



double func0(int N, int Sum) {
  double ans = (double)Sum / (double)N;
  return round(ans * 100) / 100;
}

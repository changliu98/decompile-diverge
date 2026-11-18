

#include <stdbool.h>

#include <assert.h>



bool func0(int set[], int n, int sum) {
  if (sum == 0) return true;
  if (n == 0) return false;
  if (set[n - 1] > sum) return func0(set, n - 1, sum);
  return func0(set, n - 1, sum) || func0(set, n - 1, sum - set[n - 1]);
}

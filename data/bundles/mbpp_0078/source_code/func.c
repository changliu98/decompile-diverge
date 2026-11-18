#include <stdio.h>

#include <assert.h>



int func0(int n) {
  if (n % 2 != 0) {
    return (n + 1) / 2;
  }
  int count = 0;
  for (int i = 0; i < 32; i++) {
    count += (n >> i) & 1;
  }
  int ans = n / 2;
  if (count % 2 != 0) {
    ans += 1;
  }
  return ans;
}



#include <stdio.h>

#include <assert.h>



int func0(int N) {
  int B_Number = 0;
  int cnt = 0;
  while (N != 0) {
    int rem = N % 2;
    int c = 1;
    for (int i = 0; i < cnt; i++) {
      c *= 10;
    }
    B_Number += rem * c;
    N /= 2;
    cnt++;
  }
  return B_Number;
}

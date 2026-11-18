

#include <stdio.h>

#include <math.h>

#include <assert.h>



int func0(int n) {
  n = n + 1;
  return n + (int)(log2(n + log2(n)));
}

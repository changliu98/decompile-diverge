#include <stdlib.h>

#include <stdio.h>

#include <assert.h>



int func0(int n1, int n2) {
  int distance = abs(n1 - n2);
  int sum = 0;
  while (distance > 0) {
    sum += distance % 10;
    distance /= 10;
  }
  return sum;
}

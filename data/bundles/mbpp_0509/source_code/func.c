

#include <assert.h>

#include <stdio.h>



int func0(int n) {
  if (n % 2 == 0) {
    printf("Invalid Input\n");
    return -1;
  }
  int sm = 0;
  int count = 0;
  while (n >= 1) {
    count++;
    sm += n;
    n -= 2;
  }
  return sm / count;
}

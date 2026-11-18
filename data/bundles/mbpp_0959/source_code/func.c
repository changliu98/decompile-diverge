

#include <stdio.h>

#include <assert.h>



double func0(int lst[], int len) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += lst[i];
  }
  return (double)sum / len;
}

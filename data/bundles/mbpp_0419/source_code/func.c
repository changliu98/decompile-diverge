

#include <assert.h>

#include <math.h>



int func0(double list1[], int length) {
  int i;
  int sum = 0;
  for (i = 0; i < length; i++) {
    sum += round(list1[i]);
  }
  return sum * length;
}

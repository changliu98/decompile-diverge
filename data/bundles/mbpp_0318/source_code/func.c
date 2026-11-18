

#include <assert.h>



int func0(int s) {
  int maxvalue = 0;
  int i, j, k;
  for (i = 1; i < s - 1; i++) {
    for (j = 1; j < s; j++) {
      k = s - i - j;
      if (i * j * k > maxvalue) {
        maxvalue = i * j * k;
      }
    }
  }
  return maxvalue;
}



#include <assert.h>



int func0(int a, int b) {
  int low = a < b ? a : b;
  int high = a > b ? a : b;
  if (low == 0) {
    return high;
  } else if (low == 1) {
    return 1;
  } else {
    return func0(low, high % low);
  }
}

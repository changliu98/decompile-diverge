

#include <assert.h>



int func0(int n) {
  int res = 0;
  for (int i = n; i > 0; i--) {
    if ((i & (i - 1)) == 0) {
      res = i;
      break;
    }
  }
  return res;
}



#include <assert.h>



double func0(int n) {
  if (n < 2) {
    return 1;
  } else {
    return 1.0 / n + func0(n - 1);
  }
}

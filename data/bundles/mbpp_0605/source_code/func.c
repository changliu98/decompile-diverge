

#include <assert.h>

#include <stdbool.h>



bool func0(int num) {
  if (num >= 1) {
    for (int i = 2; i <= num / 2; i++) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

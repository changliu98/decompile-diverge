

#include <assert.h>

#include <stdbool.h>



bool func0(int x) {
  int parity = 0;
  while (x != 0) {
    x = x & (x - 1);
    parity++;
  }
  return (parity % 2 == 0);
}



#include <assert.h>



int func0(int a, int b, int c) {
  int directrix = c - ((b * b) + 1) * 4 * a;
  return directrix;
}

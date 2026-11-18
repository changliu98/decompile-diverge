

#include <assert.h>



int set_middle_bits(int n) {

    n |= n >> 1;

    n |= n >> 2;

    n |= n >> 4;

    n |= n >> 8;

    n |= n >> 16;

    return (n >> 1) ^ 1;

}



int func0(int n) {
  if (n == 1) {
    return 1;
  }
  return n ^ set_middle_bits(n);
}

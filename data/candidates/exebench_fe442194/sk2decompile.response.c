void inplace_swap(int *x, int *y) {
  *y = *y ^ *x;
  *x = *x ^ *y;
  *y = *x ^ *y;
}
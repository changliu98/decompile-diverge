void f(int *x, int *y) {
  if (*x > *y) {
    *x /= 2;
    *y *= 2;
  } else {
    *x *= 2;
    *y /= 2;
  }
}
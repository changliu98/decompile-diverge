void f(int *x, int y) {
  if (*x > y) {
    h(x, *x);
    return;
  }
  *x = *x - y;
}
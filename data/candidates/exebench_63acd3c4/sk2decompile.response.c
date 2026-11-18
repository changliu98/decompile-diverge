void func3(int x, int *y) {
  if (x > 0) {
    *y = *y + 1;
  } else {
    *y = *y - 1;
  }
}
void descending2(int *x, int *y) {
  int temp;
  temp = *x;
  if (*x < *y) {
    *x = *y;
    *y = temp;
  }
}
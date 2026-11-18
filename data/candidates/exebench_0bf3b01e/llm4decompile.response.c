void DoAdjust(int *x, int *y, int dx, int dy, int cols, int rows)
{
  *x = *x - 1;
  *y = *y - 1;
  *x = *x + dx;
  if (*x < 0) {
    *x = cols - *x;
    *y = *y - *x / cols;
    *x = cols - *x % cols;
  }
  *y = *y + *x / cols;
  *x = *x % cols;
  *y = *y + dy;
  *x = *x + 1;
  *y = *y + 1;
}
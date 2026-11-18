void move(int *x, int *y, int dx, int dy, int cols, int rows)
{
  --*x;
  --*y;
  *x += dx;
  if (*x < 0) {
    *x = (cols - *x);
    *y -= *x / cols;
    *x = (cols - *x % cols);
  }
  *y += *x / cols;
  *x = *x % cols;
  *y += dy;
  ++*x;
  ++*y;
}
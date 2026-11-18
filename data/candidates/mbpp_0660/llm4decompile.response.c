int func0(int l1, int r1, int l2, int r2, int *x, int *y)
{
  int x1;
  int y1;

  if (l1 == l2) {
    x1 = -1;
  } else if (l1 < l2) {
    x1 = l1;
  } else {
    x1 = l2;
  }
  *x = x1;

  if (r1 == r2) {
    y1 = -1;
  } else if (r1 > r2) {
    y1 = r1;
  } else {
    y1 = r2;
  }
  *y = y1;

  return 0;
}
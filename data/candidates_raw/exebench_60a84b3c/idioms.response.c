static int in_rect(int *x1, int *y1, int *x2, int *y2, int x, int y, int x2_, int y2_)
{
  if (*x1 < x) *x1 = x;
  if (*y1 < y) *y1 = y;
  if (*x1 >= x2_) *x1 = x2_-1;
  if (*y1 >= y2_) *y1 = y2_-1;
  if (*x2 < x) *x2 = x + 1;
  if (*y2 < y) *y2 = y + 1;
  if (*x2 > x2_) *x2 = x2_;
  if (*y2 > y2_) *y2 = y2_;
  return *x2 > *x ? *y2 > *y : 0;
}
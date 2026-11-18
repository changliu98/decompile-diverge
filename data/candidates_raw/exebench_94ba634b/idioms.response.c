void get_block(int *y, int *x)
{
  int y1 = *y;
  int x1 = *x;
  int y2 = (y1 < 95) ? 112 : 176;
  int x2 = (y1 & 1) ? (x1 < 95) ? 32 : 31 : (x1 < 95) ? 126 : 127;
  *y = (y1 + 1) / 2 + y2;
  *x += x2;
}
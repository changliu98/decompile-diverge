void __cdecl DoAdjust(int *x, int *y, int dx_0, int dy, int cols, int rows)
{
  --*x;
  --*y;
  *x += dx_0;
  if ( *x < 0 )
  {
    *x = cols - *x;
    *y -= *x / cols;
    *x = cols - *x % cols;
  }
  *y += *x / cols;
  *x %= cols;
  *y += dy;
  ++*x;
  ++*y;
}
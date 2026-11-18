static void DoAdjust
 (
  int *x, int *y,
  int dx, int dy,
  int cols, int rows
 )
{
    ((void)0);

    *x -= 1;
    *y -= 1;

    *x += dx;
    if( *x < 0 ) {
        *x = -*x + cols;
        *y -= *x / cols;
        *x = cols - (*x % cols);
    }
    *y += *x / cols;
    *x %= cols;
    *y += dy;

    *x += 1;
    *y += 1;
}
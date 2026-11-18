void __cdecl decode6(long v, long width, long height, long *x, long *y)
{
  long maxcol; // [rsp+0h] [rbp-48h]
  long col; // [rsp+8h] [rbp-40h]
  long D; // [rsp+10h] [rbp-38h]

  D = 6LL;
  col = v / (6 * height);
  maxcol = (width - 4) / 6;
  if ( col >= maxcol )
  {
    col = (width - 4) / 6;
    D = width - 6 * maxcol;
  }
  *x = (v - 6 * height * col) % D + 6 * col;
  *y = height - 1 - (v - 6 * height * col) / D;
}
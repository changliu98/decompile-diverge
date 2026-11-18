void __cdecl decode6(long v, long width, long height, long *x, long *y)
{
  long block_width = 6;
  long col = v / (6 * height);
  long maxcol = (width - 4) / 6;

  if (col >= maxcol)
  {
    col = maxcol;
    block_width = width - 6 * maxcol;
  }

  long offset = v - 6 * height * col;
  *x = (offset % block_width) + 6 * col;
  *y = height - 1 - (offset / block_width);
}
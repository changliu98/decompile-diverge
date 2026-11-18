void decode6(long i, long width, long height, long *x, long *y)
{
  long D = 6;
  long col = i / (height * D);
  long maxcol = (width - 4) / D;
  if (col >= maxcol) {
    col = maxcol;
    D = width - col * D;
  }
  *x = col * D + (i - col * height * D) % D;
  *y = height - 1 - (i - col * height * D) / D;
}
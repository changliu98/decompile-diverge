int CalcOffsetAndShift(int x, int y, unsigned long *offset, unsigned long *shift)
{
  if (x > 84 || y >= 48)
    return -1;
  if (offset == ((void *)0) || shift == ((void *)0))
    return -1;
  *offset = (y / 8) * 84 + x;
  *shift = y % 8;
  return 0;
}
void decode_dir(int d, int *x, int *y)
{
  *x = d & 0xff - 2;
  *y = (d >> 8) & 0xff - 2;
}
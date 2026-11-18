int byte_row_gbk1(int c)
{
  if (c < 129 || c > 255)
    return -1;
  return c - 129;
}
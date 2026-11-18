static unsigned long d2_get_col(char *buf, unsigned long buflen, unsigned long pos, unsigned long *col_len)
{
  if (col_len)
    *col_len = 1;
  return 1;
}